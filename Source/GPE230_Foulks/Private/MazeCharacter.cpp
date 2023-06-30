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
	_currentHealth = maxHealth;
}

/// <summary>
/// Apply incoming damage to the player's health and check if it killed the player
/// </summary>
/// <param name="DamageAmount">- The amount of health the player has lost</param>
/// <param name="DamageEvent"></param>
/// <param name="EventInstigator"></param>
/// <param name="DamageCauser"></param>
/// <returns>Player's resulting current health</returns>
float AMazeCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (!_isDead)
	{
		// Subtract incoming damage from current health
		_currentHealth -= DamageAmount;

		UE_LOG(LogTemp, Log, TEXT("Player Took %f Damage. %f Health Remaining."), DamageAmount, _currentHealth);

		if (_currentHealth <= 0)
		{
			Die();
		}

		return _currentHealth;
	}
	else
	{
		return 0;
	}
}

/// <summary>
/// Disable controls and play a death animation
/// </summary>
void AMazeCharacter::Die()
{
	_isDead = true;
	_currentHealth = 0;

	_disableControls = true;

	GetMesh()->PlayAnimation(_deathAnim, false);
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

	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &AMazeCharacter::StartSprinting);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &AMazeCharacter::StopSprinting);

	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Pressed, this, &AMazeCharacter::StartCrouching);
	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Released, this, &AMazeCharacter::StopCrouching);
}

/*
	AddMovementInput & AddControllerYawInput are Character class functions
	AddMovementInput() takes a direction and a speed and can be called multiple times at the same time
	AddControllerYawInput() takes a speed and rotates the character
*/

/// <summary>
/// Allow the player to continue playing after death
/// </summary>
void AMazeCharacter::ResetPlayer()
{
	_isDead = false;

	SetActorLocation(mazeBeginning);

	_currentHealth = maxHealth;

	_disableControls = false;
}

/// <summary>
/// Emit particles when the stun ability is used
/// </summary>
void AMazeCharacter::ActivateStunParticleSystem()
{
	if (_stunSystem)
	{
		USceneComponent* AttachComp = GetDefaultAttachComponent();

		UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(_stunSystem, AttachComp, NAME_None,
			FVector(0), FRotator(0), EAttachLocation::Type::KeepRelativeOffset, true);

		NiagaraComp->Activate();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Player attempted to use the stun ability, but no template particle system was found."));
	}
}

/// <summary>
/// Moves maze character forwards and backwards
/// </summary>
/// <param name="value"></param>
void AMazeCharacter::MoveFB(float value)
{
	if (_disableControls)
	{
		return;
	}

	AddMovementInput(GetActorForwardVector(), value * _walkSpeed);
}

/// <summary>
/// Moves maze character left and right
/// </summary>
/// <param name="value"></param>
void AMazeCharacter::MoveLR(float value)
{
	if (_disableControls)
	{
		return;
	}

	AddMovementInput(-GetActorRightVector(), value * _walkSpeed);
}

/// <summary>
/// Rotates maze character left and right
/// </summary>
/// <param name="value"></param>
void AMazeCharacter::RotateLR(float value)
{
	if (_disableControls)
	{
		return;
	}

	AddControllerYawInput(value * _rotationSpeed);
}

/// <summary>
/// Rotates maze character camera up and down
/// </summary>
/// <param name="value"></param>
void AMazeCharacter::RotateUD(float value)
{
	if (_disableControls)
	{
		return;
	}

	if (value)
	{
		// Cap pitch rotation, must disable "Use Pawn Control Rotation" for this method
		float nextPitchValue = SpringArmComponent->GetRelativeRotation().Pitch + (value * _rotationSpeed);
		
		if (nextPitchValue > -45 && nextPitchValue < 15)
		{
			SpringArmComponent->AddLocalRotation(FRotator(value * _rotationSpeed, 0, 0));
		}
	}
}

void AMazeCharacter::StartCrouching()
{
	if (_disableControls)
	{
		return;
	}

	GetCharacterMovement()->MaxWalkSpeed *= _crouchSpeedMultiplier;
}

void AMazeCharacter::StopCrouching()
{
	if (_disableControls)
	{
		return;
	}

	GetCharacterMovement()->MaxWalkSpeed /= _crouchSpeedMultiplier;
}

void AMazeCharacter::StartSprinting()
{
	if (_disableControls)
	{
		return;
	}

	GetCharacterMovement()->MaxWalkSpeed *= _sprintSpeedMultiplier;
}

void AMazeCharacter::StopSprinting()
{
	if (_disableControls)
	{
		return;
	}

	GetCharacterMovement()->MaxWalkSpeed /= _sprintSpeedMultiplier;
}

void AMazeCharacter::UseStunAbility()
{
	if (_disableControls)
	{
		return;
	}
}
