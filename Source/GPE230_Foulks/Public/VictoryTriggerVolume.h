// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePickup.h"
#include "VictoryTriggerVolume.generated.h"

/**
 * 
 */
UCLASS()
class GPE230_FOULKS_API AVictoryTriggerVolume : public ABasePickup
{
	GENERATED_BODY()
	
protected:
	virtual void Apply(AMazeCharacter* Player) override;
};
