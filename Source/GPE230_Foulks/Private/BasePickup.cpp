// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePickup.h"

// Sets default values
ABasePickup::ABasePickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	OnActorBeginOverlap.AddDynamic(this, &ABasePickup::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ABasePickup::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABasePickup::Apply(AMazeCharacter* Player)
{
	// Play sound to signify pickup being collected
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), pickupCollected, ABasePickup::GetActorLocation());

	UE_LOG(LogTemp, Log, TEXT("Applying powerup to %s."), *Player->GetName());

	DisablePickup();
}

// Called every frame
void ABasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/// <summary>
/// If overlapped actor is a maze character, apply the powerup and disable the pickup
/// </summary>
/// <param name="OverlappedComp"></param>
/// <param name="OtherActor"></param>
/// <param name="OtherComp"></param>
/// <param name="OtherBodyIndex"></param>
/// <param name="bFromSweep"></param>
/// <param name="SweepResult"></param>
void ABasePickup::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	// Ignore any actor that is not a maze character
	if (OtherActor->IsA(AMazeCharacter::StaticClass()))
	{
		Apply(Cast<AMazeCharacter>(OtherActor));
	}
}

/// <summary>
/// Hides actor and disables collision
/// </summary>
void ABasePickup::DisablePickup()
{
	if (!willRespawn)
	{
		// No need to keep it around if it won't appear again
		this->Destroy();
	}

	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);

	GetWorld()->GetTimerManager().SetTimer(pickupTimerHandle, this, &ABasePickup::EnablePickup, disabledDuration, false);
}

/// <summary>
/// Unhides actor and enables collision
/// </summary>
void ABasePickup::EnablePickup()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
}
