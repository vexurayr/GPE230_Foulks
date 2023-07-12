// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickup.h"

void AHealthPickup::Apply(AMazeCharacter* Player)
{
	// Don't waste pickup if player is at max health
	if (Player->GetCurrentHealth() >= Player->maxHealth)
	{
		return;
	}

	Player->Heal(healingAmount);

	// Calls Apply in parent class for the debug info and to disable the pickup
	Super::Apply(Player);
}
