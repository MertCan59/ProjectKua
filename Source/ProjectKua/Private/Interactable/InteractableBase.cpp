// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable/InteractableBase.h"

#include "Characters/Player/LiseWan.h"
#include "Components/SphereComponent.h"


// Sets default values
AInteractableBase::AInteractableBase()
{
	PrimaryActorTick.bCanEverTick = false;
	StaticMeshComponent=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	RootComponent=StaticMeshComponent;

	StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMeshComponent->SetCollisionResponseToAllChannels(ECR_Block);
	StaticMeshComponent->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);

	OverlapComponent=CreateDefaultSubobject<USphereComponent>(TEXT("OverlapSphereComponent"));
	OverlapComponent->SetupAttachment(StaticMeshComponent);
	OverlapComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComponent->SetCollisionResponseToAllChannels(ECR_Block);
	OverlapComponent->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
	OverlapComponent->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);
}


void AInteractableBase::BeginPlay()
{
	Super::BeginPlay();
	
}


void AInteractableBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInteractableBase::Interact_Implementation()
{
	switch (CharacterState)
	{
	case ECharacterState::ECS_Interacted:
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Interacting with this character!");
		break;
	case ECharacterState::ECS_Notinteracted:
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Not interacting with this character!");
		break;
	}
}

