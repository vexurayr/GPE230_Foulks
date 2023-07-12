// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePickup.h"
#include "HealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class GPE230_FOULKS_API AHealthPickup : public ABasePickup
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere)
		float healingAmount;

	virtual void Apply(AMazeCharacter* Player) override;
};
