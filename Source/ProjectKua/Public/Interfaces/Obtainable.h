// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Obtainable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UObtainable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PROJECTKUA_API IObtainable
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintNativeEvent)
	void AddToInventory();
};
