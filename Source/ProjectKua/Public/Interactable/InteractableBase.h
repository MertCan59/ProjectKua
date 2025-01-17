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
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	USphereComponent* OverlapComponent;

private:
	AActor* InteractedActor;
	ECharacterState CharacterState=ECharacterState::ECS_Interacted;
};
