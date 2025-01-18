// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactable.h"
#include "Characters/CharacterTypes.h"
#include "InteractableBase.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class PROJECTKUA_API AInteractableBase : public AActor,public IInteractable
{
	GENERATED_BODY()
	
public:	
	AInteractableBase();
	virtual void Tick(float DeltaTime) override;
	virtual void Interact_Implementation() override;

	void RotateInteractable(float YawInput,float PitchInput);

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	USphereComponent* OverlapComponent;

	//** POLISHING VARIABLES **//
	UPROPERTY(EditAnywhere,Category="Position Variables")
	float ItemHeight;

private:
	AActor* InteractedActor;
	FVector InitialPosition;
	FRotator InitialRotation;
	
	FVector Position;
};