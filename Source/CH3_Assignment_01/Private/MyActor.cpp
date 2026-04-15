#include "MyActor.h"
#include "ActionComponent.h"

AMyActor::AMyActor()
{
	PrimaryActorTick.bCanEverTick = false;
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	SetRootComponent(RootScene);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(RootScene);

	ActionComp = CreateDefaultSubobject<UActionComponent>(TEXT("ActionComponent"));
}

void AMyActor::BeginPlay()
{
	Super::BeginPlay();

}

void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

