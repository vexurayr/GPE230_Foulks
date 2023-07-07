// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePowerup.h"

// Sets default values
ABasePowerup::ABasePowerup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABasePowerup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePowerup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

