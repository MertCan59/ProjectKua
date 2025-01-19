// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable/ObtainableItem.h"

#include "Characters/Player/LiseWan.h"
#include "Inventory/Inventory.h"

void AObtainableItem::AddToInventory_Implementation()
{
	ALiseWan* LiseWan = Cast<ALiseWan>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!LiseWan)
	{
	
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,"Owner is null!");
		}
		return;
	}
	
	UInventory* StoreItem = LiseWan->GetInventory();
	if (StoreItem)
	{
		StoreItem->AddToInventory(this);
	}
}
