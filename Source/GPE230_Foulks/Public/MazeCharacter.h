// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "MazeCharacter.generated.h"

UCLASS()
class GPE230_FOULKS_API AMazeCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/// <summary>
	/// The max health of the player character, which will set the current health at runtime
	/// </summary>
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float maxHealth;
	UPROPERTY(EditAnywhere)
		FVector mazeBeginning;

	// Sets default values for this character's properties
	AMazeCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	/// <summary>
	/// The current health of the player character
	/// </summary>
	float _currentHealth;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
		virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
			AActor* DamageCauser) override;
	virtual void Die();

	// Spring arm component for reducing camera obstruction
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		class USpringArmComponent* SpringArmComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		class UCameraComponent* CameraComponent;

// Variables and functions for character movement
private:
	UPROPERTY(EditAnywhere)
		float walkSpeed;
	UPROPERTY(EditAnywhere)
		float crouchSpeedMultiplier;
	UPROPERTY(EditAnywhere)
		float sprintSpeedMultiplier;
	UPROPERTY(EditAnywhere)
		float rotationSpeed;

	void MoveFB(float value);
	void MoveLR(float value);
	void RotateLR(float value);
	void RotateUD(float value);
	void StartCrouching();
	void StopCrouching();
	void StartSprinting();
	void StopSprinting();
};
