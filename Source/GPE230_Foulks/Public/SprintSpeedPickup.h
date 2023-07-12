// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePickup.h"
#include "SprintSpeedPickup.generated.h"

/**
 * 
 */
UCLASS()
class GPE230_FOULKS_API ASprintSpeedPickup : public ABasePickup
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere)
		float sprintSpeedMultiplierIncrease;

	virtual void Apply(AMazeCharacter* Player) override;
};
