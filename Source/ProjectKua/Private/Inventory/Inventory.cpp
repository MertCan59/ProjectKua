// Fill out your copyright notice in the Description page of Project Settings.

#include "Inventory/Inventory.h"

#include "Characters/Player/LiseWan.h"


UInventory::UInventory()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UInventory::AddToInventory(IObtainable* Obtainable)
{
	if (Obtainable && CurrentStoredItem < MaxStoreableItem)
	{
		StoredItems.AddUnique(Obtainable);
		CurrentStoredItem++;
		GEngine->AddOnScreenDebugMessage(-1, 2.5, FColor::Red, "Added to the Inventory ");

	}else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Failed to add item to inventory!"));
	}
}

void UInventory::GetFromInventory(IObtainable* Obtainable)
{
	if (Obtainable && CurrentStoredItem > 0)
	{
		StoredItems.Pop();
		CurrentStoredItem--;

		AActor* ActorToSpawn = Cast<AActor>(Obtainable);
		ALiseWan* LiseWan = Cast<ALiseWan>(GetWorld()->GetFirstPlayerController()->GetPawn());
		if (ActorToSpawn)
		{
			FVector SpawnLocation = LiseWan->GetActorLocation();
			FRotator SpawnRotation = LiseWan->GetActorRotation();

			AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn->GetClass(), SpawnLocation, SpawnRotation);
			if (SpawnedActor)
			{
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Item spawned successfully."));
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Failed to spawn the item."));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("No items to get from inventory."));
	}
}