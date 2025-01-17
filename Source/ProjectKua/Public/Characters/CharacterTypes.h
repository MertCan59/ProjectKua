#pragma once

UENUM(BlueprintType)
enum class  ECharacterState : uint8
{
	ECS_Interacted UMETA(DisplayName = "Interacted State"), 
	ECS_Notinteracted UMETA(DisplayName = "Uninteracted State")
};