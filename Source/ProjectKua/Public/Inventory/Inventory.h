// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/Obtainable.h"
#include "Inventory.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTKUA_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	

	UInventory();
	void AddToInventory(IObtainable* Obtainable);
	void GetFromInventory(IObtainable* Obtainable);
	
protected:

private:
	UPROPERTY(EditAnywhere)
	TArray<IObtainable*> StoredItems;

	UPROPERTY(EditAnywhere)
	int MaxStoreableItem=10;

	UPROPERTY(VisibleAnywhere)
	int CurrentStoredItem=0;
};
