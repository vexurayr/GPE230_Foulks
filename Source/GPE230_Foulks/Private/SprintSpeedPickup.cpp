// Fill out your copyright notice in the Description page of Project Settings.


#include "SprintSpeedPickup.h"

void ASprintSpeedPickup::Apply(AMazeCharacter* Player)
{
	Player->IncreaseSprintSpeedMultiplier(sprintSpeedMultiplierIncrease);

	// Calls Apply in parent class for the debug info and to disable the pickup
	Super::Apply(Player);
}
