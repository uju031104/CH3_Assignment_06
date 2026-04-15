#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"


/**
 * 
 */
UCLASS()
class CH3_ASSIGNMENT_01_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	TArray<TSubclassOf<class AMyActor>> SpawnActor;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	int32 SpawnCount = 10;
	
};
