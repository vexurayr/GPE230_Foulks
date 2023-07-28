// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sound/SoundWave.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TriggerBox.h"
#include "LockAndKey.generated.h"

/**
 * 
 */
UCLASS()
class GPE230_FOULKS_API ALockAndKey : public ATriggerBox
{
	GENERATED_BODY()

public:
	ALockAndKey();

	UFUNCTION()
		void CheckActorType(class AActor* OverlappedActor, class AActor* OtherActor);
	UFUNCTION()
		void OpenTheDoor();

protected:
	UPROPERTY(EditAnywhere)
		USoundWave* doorOpeningSound;
};
