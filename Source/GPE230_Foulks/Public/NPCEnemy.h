// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "GameFramework/Character.h"
#include "NPCEnemy.generated.h"

UCLASS()
class GPE230_FOULKS_API ANPCEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPCEnemy();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Collision")
		void DetectHit();

private:
	UPROPERTY(EditAnywhere)
		float _TraceRadius = 500.0f;
	UPROPERTY(EditAnywhere)
		FName _PunchingHandSocketName;
	UPROPERTY(EditAnywhere)
		float _HitDamage;

};
