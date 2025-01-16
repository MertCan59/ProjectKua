// Fill out your copyright notice in the Description page of Project Settings.


#include "StarterContent/StarterActor.h"

// Sets default values
AStarterActor::AStarterActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStarterActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStarterActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

