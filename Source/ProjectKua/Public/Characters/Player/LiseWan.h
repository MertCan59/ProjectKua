// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/CharacterTypes.h"
#include "GameFramework/Character.h"
#include "LiseWan.generated.h"

class UInputMappingContext;
class UInputAction;
class USpringArmComponent;
class UCameraComponent;

struct FInputActionValue;

UCLASS()
class PROJECTKUA_API ALiseWan : public ACharacter
{
	GENERATED_BODY()

public:
	ALiseWan();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
protected:
	
	virtual void BeginPlay() override;

	ECharacterState CharacterState=ECharacterState::ECS_Notinteracted;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Input")
	UInputMappingContext* PlayerInputContext;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Input")
	UInputAction* MovementAction;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Input")
	UInputAction* LookingAction;
	
	//** CALLBACKS FOR INPUTS **//
	void Move(const FInputActionValue& value);
	void Look(const FInputActionValue& value);

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
};
