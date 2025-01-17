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
	InitialPosition=GetActorLocation();

}

void AInteractableBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInteractableBase::Interact_Implementation()
{
    ALiseWan* LiseWan = Cast<ALiseWan>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (LiseWan)
	{
		switch (LiseWan->GetCharacterState())
		{
		case ECharacterState::ECS_Notinteracted:
			SetActorLocation(FVector(GetActorLocation().X,GetActorLocation().Y,LiseWan->GetCameraHeight()+75.f));
			break;
		case ECharacterState::ECS_Interacted:
			SetActorLocation(InitialPosition);
			break;
		}
	}
}