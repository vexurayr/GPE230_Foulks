// Fill out your copyright notice in the Description page of Project Settings.

#include "MazeCharacter.h"
#include "LockAndKey.h"

/// <summary>
/// Call CheckActorType when something enters the collider
/// </summary>
ALockAndKey::ALockAndKey()
{
	OnActorBeginOverlap.AddDynamic(this, &ALockAndKey::CheckActorType);
}

/// <summary>
/// On collision with a trigger box, check for a maze character, open the door if one is found
/// </summary>
/// <param name="OverlappedActor"></param>
/// <param name="OtherActor"></param>
void ALockAndKey::CheckActorType(AActor* OverlappedActor, AActor* OtherActor)
{
	// Ignore any actor that is not a maze character
	if (OtherActor->IsA(AMazeCharacter::StaticClass()))
	{
		OpenTheDoor();
	}
}

/// <summary>
/// Delete the door and key by destroying the entire object and any children
/// </summary>
void ALockAndKey::OpenTheDoor()
{
	this->Destroy();
}
