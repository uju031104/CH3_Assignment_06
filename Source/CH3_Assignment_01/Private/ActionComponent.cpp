#include "ActionComponent.h"
#include "Cube.h"

UActionComponent::UActionComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

	SelectedAction = EAction::Idle;
	TeleportTime = 1.0f;
	InitializeActionMap();
	//ActorToSpawn = ACube::StaticClass();


}

void UActionComponent::InitializeActionMap()
{
	if (ActionMap.Num() > 0) return;

	ActionMap.Add(EAction::Idle, FActionInfo());
	ActionMap.Add(EAction::UpDown, FActionInfo());
	ActionMap.Add(EAction::LeftRight, FActionInfo());
	ActionMap.Add(EAction::Scale, FActionInfo());
	ActionMap.Add(EAction::Rotate, FActionInfo());
	ActionMap.Add(EAction::Disappear, FActionInfo());
}

void UActionComponent::BeginPlay()
{
	Super::BeginPlay();

	InitialLocation = GetOwner()->GetActorLocation();
	
	RegisterActions();
	StartAction();

	//SpawnMultipleActors();
}

void UActionComponent::RegisterActions()
{
	if (ActionMap.Contains(EAction::Idle))
	{
		ActionMap[EAction::Idle].ActionDelegate.BindUObject(this, &UActionComponent::ExecuteIdle);
	}
	if (ActionMap.Contains(EAction::UpDown))
	{
		ActionMap[EAction::UpDown].ActionDelegate.BindUObject(this, &UActionComponent::ExecuteUpDown);
	}
	if (ActionMap.Contains(EAction::LeftRight))
	{
		ActionMap[EAction::LeftRight].ActionDelegate.BindUObject(this, &UActionComponent::ExecuteLeftRight);
	}
	if (ActionMap.Contains(EAction::Scale))
	{
		ActionMap[EAction::Scale].ActionDelegate.BindUObject(this, &UActionComponent::ExecuteScale);
	}
	if (ActionMap.Contains(EAction::Rotate))
	{
		ActionMap[EAction::Rotate].ActionDelegate.BindUObject(this, &UActionComponent::ExecuteRotate);
	}
	if (ActionMap.Contains(EAction::Disappear))
	{
		ActionMap[EAction::Disappear].ActionDelegate.BindUObject(this, &UActionComponent::ExecuteDisappear);
	}
}

void UActionComponent::StartAction()
{
	GetWorld()->GetTimerManager().ClearTimer(ActionTimerHandle);

	if (ActionMap.Contains(SelectedAction))
	{
		float Duration = ActionMap[SelectedAction].Duration;

		if (!IsComponentTickEnabled())
		{
			this->SetComponentTickEnabled(true);
		}

		if (Duration > 0.0f)
		{
			GetWorld()->GetTimerManager().SetTimer(ActionTimerHandle, this, &UActionComponent::StopAction, Duration, false);
		}
	}
	else if (SelectedAction == EAction::Teloport)
	{
		Teleport();
	}
}
void UActionComponent::StopAction()
{
	this->SetComponentTickEnabled(false);
}

void UActionComponent::ExecuteIdle(float DeltaTime) {}

void UActionComponent::ExecuteUpDown(float DeltaTime)
{
	if (!IsValid(GetOwner()))
	{
		return;
	}
	float WorldTime = GetWorld()->GetTimeSeconds();
	float Range = FMath::Sin(WorldTime * ActionMap[EAction::UpDown].Speed);
	FVector ActorLocation = InitialLocation;
	ActorLocation.Z += Range * ActionMap[EAction::UpDown].Value;
	GetOwner()->SetActorLocation(ActorLocation);

}

void UActionComponent::ExecuteLeftRight(float DeltaTime)
{
	if (!IsValid(GetOwner()))
	{
		return;
	}
	float WorldTime = GetWorld()->GetTimeSeconds();
	float Range = FMath::Sin(WorldTime * ActionMap[EAction::LeftRight].Speed);
	FVector ActorLocation = InitialLocation;
	ActorLocation.Y += Range * ActionMap[EAction::LeftRight].Value;
	GetOwner()->SetActorLocation(ActorLocation);

}

void UActionComponent::ExecuteScale(float DeltaTime)
{
	if (!IsValid(GetOwner()))
	{
		return;
	}
	float WorldTime = GetWorld()->GetTimeSeconds();
	float Range = FMath::Sin(WorldTime * ActionMap[EAction::Scale].Speed);
	GetOwner()->SetActorScale3D(FVector(1.0f + (Range + 1) * 0.5f * ActionMap[EAction::Scale].Value));

}

void UActionComponent::ExecuteRotate(float DeltaTime)
{
	if (!IsValid(GetOwner()))
	{
		return;
	}
	GetOwner()->AddActorLocalRotation(FRotator(0, DeltaTime * ActionMap[EAction::Rotate].Speed, 0));

}

void UActionComponent::ExecuteDisappear(float DeltaTime)
{
	if (!IsValid(GetOwner()))
	{
		return;
	}

	if (ElapsedTime == 0.0f)
	{
		StartScale = GetOwner()->GetActorScale3D();
	}

	ElapsedTime += DeltaTime;

	float Alpha = FMath::Clamp(ElapsedTime / ActionMap[EAction::Disappear].Duration, 0.0f, 1.0f);

	FVector NewScale = FMath::Lerp(StartScale, FVector::ZeroVector, Alpha);
	GetOwner()->SetActorScale3D(NewScale);

	if (Alpha >= 1.0f)
	{
		GetOwner()->Destroy();
	}
}

void UActionComponent::Teleport()
{
	StopAction(); // tick()을 안쓰기 때문
	GetWorld()->GetTimerManager().SetTimer(
		ActionTimerHandle,
		[this]()
		{
			if (IsValid(GetOwner()))
			{
				FVector RandomOffset(
					FMath::RandRange(-100.0f, 100.0f),
					FMath::RandRange(-100.0f, 100.0f),
					FMath::RandRange(-100.0f, 100.0f)
				);

				GetOwner()->SetActorLocation(InitialLocation + RandomOffset);
			}
		},
		TeleportTime,
		true
	);
}



void UActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ActionMap[SelectedAction].ActionDelegate.Execute(DeltaTime);

}

