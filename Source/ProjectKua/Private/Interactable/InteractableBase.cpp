// Fill out your copyright notice in the Description page of Project Settings.

#include "Interactable/InteractableBase.h"
#include "Characters/Player/LiseWan.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"

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
	InitialRotation=GetActorRotation();
}

void AInteractableBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AInteractableBase::Interact_Implementation()
{
    ALiseWan* LiseWan = Cast<ALiseWan>(GetWorld()->GetFirstPlayerController()->GetPawn());
	//const auto Rotation=GetActorRotation();
	if (LiseWan)
	{
		auto CachedAxisVector=LiseWan->GetActorRotation();
		switch (LiseWan->GetCharacterState())
		{
		case ECharacterState::ECS_Notinteracted:
			LiseWan->Controller->SetControlRotation(CachedAxisVector);
			Position=UKismetMathLibrary::VLerp(GetActorLocation(),LiseWan->GetLocation(),.5f);
			Position.Z=UKismetMathLibrary::Lerp(Position.Z,Position.Z+=ItemHeight,0.25);
			SetActorLocation(Position);
			SetActorRotation(LiseWan->GetActorRotation());
			break;
		case ECharacterState::ECS_Interacted:
			SetActorLocation(InitialPosition);
			SetActorRotation(InitialRotation);
			break;
		}
	}
}
void AInteractableBase::RotateInteractable(float YawInput, float PitchInput)
{
	FQuat YawRotation = FQuat(FVector(0.f, 0.f, 1.f), FMath::DegreesToRadians(YawInput * 2.f));
	FQuat PitchRotation = FQuat(FVector(1.f, 0.f, 0.f), FMath::DegreesToRadians(PitchInput * 2.f));

	FQuat CurrentRotation = GetActorQuat();

	FQuat NewRotation = PitchRotation * CurrentRotation * YawRotation;
	SetActorRotation(NewRotation);
}
