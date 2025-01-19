// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/CharacterTypes.h"
#include "GameFramework/Character.h"
#include "Interfaces/Interactable.h"
#include "Interactable/InteractableBase.h"
#include "Interfaces/Obtainable.h"

#include "LiseWan.generated.h"

class USceneComponent;
class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;
class UCapsuleComponent;
class USphereComponent;
class UInventory;

struct FInputActionValue;

UCLASS()
class PROJECTKUA_API ALiseWan : public ACharacter
{
	GENERATED_BODY()

public:
	ALiseWan();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	FORCEINLINE float GetCameraHeight() const;
	FORCEINLINE float GetArmLength() const;
	FORCEINLINE UInventory* GetInventory();

	void SetCharacterState(ECharacterState State);
	ECharacterState GetCharacterState()const;

	FVector GetLocation()const;
protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnSphereOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
		);
	
	UFUNCTION()
	 void OnSphereOverlapEnd(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex
		);
	 ECharacterState CharacterState=ECharacterState::ECS_Notinteracted;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Input")
	UInputMappingContext* PlayerInputContext;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Input")
	UInputAction* MovementAction;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Input")
	UInputAction* LookingAction;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Input")
	UInputAction* Interaction;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Input")
	UInputAction* InventoryUsing;

	
	
	//** CALLBACKS FOR INPUTS **//
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Interact();
	void UseInventory();

	//** CAMERA PROPERTIES **//
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Camera Properties")
	float CameraHeight=100;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Camera Properties")
	float ArmLength=-1.0f;
	
private:	

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;

	UPROPERTY(VisibleAnywhere,Category="OverlapCapsule")
	UCapsuleComponent* OverlapComponent;
	
	UPROPERTY(VisibleAnywhere,Category="OverlapSphere")
	USphereComponent* OverlapSphere;
	
	UPROPERTY(VisibleAnywhere,Category="Object Move Position")
	USceneComponent* GetPositionToMove;
	
	UPROPERTY(VisibleAnywhere)
	AActor* InteractedActor=nullptr;
	
	UPROPERTY(VisibleAnywhere)
	AActor* InventoredItem=nullptr;

	

	UPROPERTY(VisibleAnywhere)
	UInventory* Inventory;
};