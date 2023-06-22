// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCEnemy.h"

// Sets default values
ANPCEnemy::ANPCEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANPCEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

/// <summary>
/// Detect objects hit by the NPC's fists
/// </summary>
void ANPCEnemy::DetectHit()
{
	bool canDamage = true;

	// Get location of the fist
	const FVector PunchLocation = GetMesh()->GetSocketLocation(_PunchingHandSocketName);

	// Don't detect the NPC or its controller in the spheretrace
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	ActorsToIgnore.Add(GetOwner());

	// Array for actors hit by the spheretrace
	TArray<FHitResult> HitArray;

	// Spheretrace around fist for overlapped actors - true if there are any, false if there are none
	const bool Hit = UKismetSystemLibrary::SphereTraceMulti(GetWorld(), PunchLocation, PunchLocation, _TraceRadius,
		UEngineTypes::ConvertToTraceType(ECC_Camera), false, ActorsToIgnore, EDrawDebugTrace::None, HitArray,
		true, FLinearColor::Red, FLinearColor::Green, 2.0f);

	// Name of this actor for debugging
	FString ownerName = this->GetName();

	// If the hit was valid
	if (Hit)
	{
		for (const FHitResult HitResult : HitArray)
		{
			if (canDamage)
			{
				FString hitActorName = HitResult.GetActor()->GetName();

				UE_LOG(LogTemp, Log, TEXT("NpcEnemy actor \"%s\" hit other actor \"%s\", dealing %f damage."), *ownerName,
					*hitActorName, _HitDamage);

				// Apply generic damage to hit actor
				UGameplayStatics::ApplyDamage(HitResult.GetActor(), _HitDamage, GetController(), this, UDamageType::StaticClass());

				canDamage = false;
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("NpcEnemy actor \"%s\" did not detect any valid hits on its last attack."), *ownerName);
	}
}

// Called every frame
void ANPCEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPCEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

