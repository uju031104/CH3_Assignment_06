#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActionComponent.generated.h"

// 델리게이트 선언
DECLARE_DELEGATE_OneParam(FActionDelegate, float);

UENUM(BlueprintType)
enum class EAction : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	UpDown UMETA(DisplayName = "UpDown"),
	LeftRight UMETA(DisplayName = "LeftRight"),
	Scale UMETA(DisplayName = "Scale"),
	Rotate UMETA(DisplayName = "Rotate"),
	Disappear UMETA(DisplayName = "Disappear"),
	Teloport UMETA(DisplayName = "Teloport")
};

USTRUCT(BlueprintType)
struct FActionInfo
{
	GENERATED_BODY()

	FActionDelegate ActionDelegate;

	UPROPERTY(EditAnywhere)
	float Value = 0.0f;
	UPROPERTY(EditAnywhere)
	float Speed = 0.0f;
	UPROPERTY(EditAnywhere)
	float Duration = 0.0f;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CH3_ASSIGNMENT_01_API UActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UActionComponent();
	void InitializeActionMap();

	UPROPERTY(EditAnywhere, Category = "ActionSettings")
	EAction SelectedAction;

	UPROPERTY(EditAnywhere, EditFixedSize, Category = "ActionSettings")
	TMap<EAction, FActionInfo> ActionMap;

	UPROPERTY(EditAnywhere, Category = "ActionSettings")
	float TeleportTime;

protected:

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void RegisterActions();
	void StartAction();
	void StopAction();

	void ExecuteIdle(float DeltaTime);
	void ExecuteUpDown(float DeltaTime);
	void ExecuteLeftRight(float DeltaTime);
	void ExecuteScale(float DeltaTime);
	void ExecuteRotate(float DeltaTime);
	void ExecuteDisappear(float DeltaTime);

	void Teleport();

	float ElapsedTime = 0.0f;
	FVector StartScale;
	FTimerHandle ActionTimerHandle;
	FVector InitialLocation;
};
