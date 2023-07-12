// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "MazeCharacter.h"
#include "BasePickup.generated.h"

UCLASS()
class GPE230_FOULKS_API ABasePickup : public ATriggerBox
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasePickup();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere)
		bool willRespawn;

	UPROPERTY(EditAnywhere)
		float disabledDuration;

	FTimerHandle pickupTimerHandle;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		virtual void Apply(AMazeCharacter* Player);

	UFUNCTION()
		void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION()
		void DisablePickup();

	UFUNCTION()
		void EnablePickup();
};
