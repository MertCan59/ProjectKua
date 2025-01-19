// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable/InteractableBase.h"
#include "Interfaces/Obtainable.h"
#include "ObtainableItem.generated.h"

class UInventory;
/**
 * 
 */
UCLASS()
class PROJECTKUA_API AObtainableItem : public AInteractableBase,public IObtainable
{
	GENERATED_BODY()
public:
	virtual void AddToInventory_Implementation() override;

private:

};
