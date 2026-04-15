// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "MyActor.h"
#include "ActionComponent.h"

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	for (auto& MovingActor : SpawnActor) 
	{
		if (MovingActor)
		{
			for (int32 i = 0; i < SpawnCount; ++i)
			{
				FVector SpawnLocation = FVector(FMath::RandRange(-500.f, 500.f), FMath::RandRange(-500.f, 500.f), FMath::RandRange(-500.f, 500.f));
				FRotator SpawnRotation = FRotator::ZeroRotator;

				GetWorld()->SpawnActor<AMyActor>(MovingActor, SpawnLocation, SpawnRotation);
			}
		}
	}
}
