// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeGameMode.h"

// Initialize things like the player's pawn
void AMazeGameMode::InitGameState()
{
	// Super refers to a header file or parent class
	// In this case, calls InitGameState() in MazeGameMode.h
	Super::InitGameState();

	// ADefaultPawn is the parent of the default pawn class
	// If there is no override for the default pawn class
	if (DefaultPawnClass == ADefaultPawn::StaticClass())
	{
		// Set the default pawn to our custom pawn
		DefaultPawnClass = DefaultPlayerCharacter;
	}
}