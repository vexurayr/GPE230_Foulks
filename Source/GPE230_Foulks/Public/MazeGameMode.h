// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
// Access and change the default pawn for the player
#include "GameFramework/DefaultPawn.h"
// Access and change info about the MazeCharacter class
#include "MazeCharacter.h"
#include "MazeGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GPE230_FOULKS_API AMazeGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	void InitGameState() override;

private:
	// UPROPERTY modifies the variable that follows it
	// EditAnywhere allows modification of private variables in Blueprint
	// NoClear prevents variable from being null or empty
	UPROPERTY(EditAnywhere, NoClear)
	// Variable type that only holds the specified data type and derived classes (instances and children)
	// StaticClass represents the base class at runtime
		TSubclassOf<AMazeCharacter> DefaultPlayerCharacter = AMazeCharacter::StaticClass();
};
