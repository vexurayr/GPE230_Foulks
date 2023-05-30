// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeCharacter.h"

// Sets default values
AMazeCharacter::AMazeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Instantiate components
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

	// Attach class components to the character's skeletal mesh component
	SpringArmComponent->SetupAttachment(GetMesh());

	// Attach the camera to the spring arm component
	CameraComponent->AttachToComponent(SpringArmComponent, FAttachmentTransformRules::KeepRelativeTransform);

	// Set defaults for spring arm component
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->bEnableCameraLag = true;
	SpringArmComponent->TargetArmLength = 300.0f;
}

// Called when the game starts or when spawned
void AMazeCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMazeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMazeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// The first parameter is the axis mapping name set in the project settings
	// The second parameter is the character the axis map is controlling
	// The third parameter is the function the axis will call, passing in its scale
	PlayerInputComponent->BindAxis(TEXT("MoveFB"), this, &AMazeCharacter::MoveFB);
	PlayerInputComponent->BindAxis(TEXT("MoveLR"), this, &AMazeCharacter::MoveLR);
	PlayerInputComponent->BindAxis(TEXT("RotateLR"), this, &AMazeCharacter::RotateLR);
	PlayerInputComponent->BindAxis(TEXT("RotateUD"), this, &AMazeCharacter::RotateUD);
}

/*
	AddMovementInput & AddControllerYawInput are Character class functions
	AddMovementInput() takes a direction and a speed and can be called multiple times at the same time
	AddControllerYawInput() takes a speed and rotates the character
*/

/// <summary>
/// Moves maze character forwards and backwards
/// </summary>
/// <param name="value"></param>
void AMazeCharacter::MoveFB(float value)
{
	AddMovementInput(GetActorForwardVector(), value * moveSpeed);
}

/// <summary>
/// Moves maze character left and right
/// </summary>
/// <param name="value"></param>
void AMazeCharacter::MoveLR(float value)
{
	AddMovementInput(-GetActorRightVector(), value * moveSpeed);
}

/// <summary>
/// Rotates maze character left and right
/// </summary>
/// <param name="value"></param>
void AMazeCharacter::RotateLR(float value)
{
	AddControllerYawInput(value * rotationSpeed);
}

/// <summary>
/// Rotates maze character camera up and down
/// </summary>
/// <param name="value"></param>
void AMazeCharacter::RotateUD(float value)
{
	if (value)
	{
		// Cap pitch rotation, must disable "Use Pawn Control Rotation" for this method
		float nextPitchValue = SpringArmComponent->GetRelativeRotation().Pitch + (value * rotationSpeed);
		
		if (nextPitchValue > -45 && nextPitchValue < 15)
		{
			SpringArmComponent->AddLocalRotation(FRotator(value * rotationSpeed, 0, 0));
		}
	}
}
