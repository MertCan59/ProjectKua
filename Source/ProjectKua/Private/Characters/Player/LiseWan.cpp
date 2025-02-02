// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Player/LiseWan.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SceneComponent.h"
#include "Inventory/Inventory.h"

#include "DebugHelper.h"

// Sets default values
ALiseWan::ALiseWan()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	bUseControllerRotationPitch=false;
	bUseControllerRotationYaw=false;
	bUseControllerRotationRoll=false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate=FRotator(0.f,400.f,0.f);
	
	CameraBoom=CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	
	ViewCamera=CreateDefaultSubobject<UCameraComponent>(TEXT("ViewCamera"));
	ViewCamera->SetupAttachment(CameraBoom);

	//PHYSIC CONTROL
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Block);

	// OVERLAP CONTROL 
	OverlapSphere=CreateDefaultSubobject<USphereComponent>(TEXT("OverlapSphere"));
	OverlapSphere->SetupAttachment(GetRootComponent());
	OverlapSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	OverlapSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapSphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);

	GetPositionToMove=CreateDefaultSubobject<USceneComponent>(TEXT("GetPositionToMove"));
	GetPositionToMove->SetupAttachment(GetRootComponent());

	Inventory=CreateDefaultSubobject<UInventory>(TEXT("Inventory"));
}

// Called when the game starts or when spawned
void ALiseWan::BeginPlay()
{
	Super::BeginPlay();

	CameraBoom->TargetOffset=FVector(0.0f,0.0f,CameraHeight);
	CameraBoom->TargetArmLength=ArmLength;
	
	APlayerController* PlayerController=Cast<APlayerController>(GetController());
	if(PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem=ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			SubSystem->AddMappingContext(PlayerInputContext,0);
		}
	}
	if (GetCapsuleComponent())
	{
		OverlapSphere->OnComponentBeginOverlap.AddDynamic(this,&ALiseWan::OnSphereOverlap);
		OverlapSphere->OnComponentEndOverlap.AddDynamic(this,&ALiseWan::OnSphereOverlapEnd);
	}
}

void ALiseWan::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->Implements<UInteractable>())
	{
		InteractedActor = OtherActor;
	}
}

void ALiseWan::OnSphereOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (InteractedActor == OtherActor)
	{
		InteractedActor = nullptr;
	}
}

// Called every frame
void ALiseWan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ALiseWan::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnchancedComponent=CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnchancedComponent->BindAction(MovementAction,ETriggerEvent::Triggered,this,&ALiseWan::Move);
		EnchancedComponent->BindAction(LookingAction,ETriggerEvent::Triggered,this,&ALiseWan::Look);
		EnchancedComponent->BindAction(Interaction,ETriggerEvent::Started,this,&ALiseWan::Interact);
		EnchancedComponent->BindAction(InventoryUsing,ETriggerEvent::Started,this,&ALiseWan::UseInventory);
	}
}

void ALiseWan::Move(const FInputActionValue& Value)
{
	if (CharacterState!=ECharacterState::ECS_Notinteracted)return;
	
	const auto MovementVector=Value.Get<FVector2D>();
	const auto Rotation=Controller->GetControlRotation();

	const FRotator YawRotation(0.f,Rotation.Yaw,0.f);
	const auto ForwardDirection=FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const auto RightDirection=FRotationMatrix(Rotation).GetUnitAxis(EAxis::Y);

	if (Controller!=nullptr && MovementVector.Y!=0)
	{
		AddMovementInput(ForwardDirection,MovementVector.Y);
	}
	
	if (Controller!=nullptr && MovementVector.X!=0)
	{
		AddMovementInput(RightDirection,MovementVector.X);
	}
	const FVector Direction = (ForwardDirection * MovementVector.Y + RightDirection * MovementVector.X).GetSafeNormal();
	if (!Direction.IsNearlyZero())
	{
		const FRotator TargetRotation = Direction.Rotation();
		SetActorRotation(FRotator(0.f, TargetRotation.Yaw, 0.f));
	}
}

void ALiseWan::Look(const FInputActionValue& Value)
{
	auto LookAxisVector=Value.Get<FVector2D>();
	if (CharacterState!=ECharacterState::ECS_Notinteracted && InteractedActor)
	{
		AInteractableBase* Interactable=CastChecked<AInteractableBase>(InteractedActor);
		if (Interactable && LookAxisVector.SizeSquared()>0)
		{
			
			if (Interactable && LookAxisVector.SizeSquared() > 0)
			{
				Interactable->RotateInteractable(-LookAxisVector.X,LookAxisVector.Y);
			}
			return;
		}
	}
	if (Controller!=nullptr && LookAxisVector.X!=0)
	{
		AddControllerYawInput(LookAxisVector.X);
	}
	if (Controller!=nullptr && LookAxisVector.Y!=0)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ALiseWan::Interact()
{
	if (InteractedActor)
	{
		IInteractable* Interactable = Cast<IInteractable>(InteractedActor);
		IObtainable* Obtainable=Cast<IObtainable>(InteractedActor);
		if (Interactable)
		{
			if (!Obtainable)
			{
				switch (CharacterState)
				{
				case ECharacterState::ECS_Interacted:
					Interactable->Execute_Interact(InteractedActor);
					SetCharacterState(ECharacterState::ECS_Notinteracted);
					break;
				
				case ECharacterState::ECS_Notinteracted:
					Interactable->Execute_Interact(InteractedActor);
					SetCharacterState(ECharacterState::ECS_Interacted);
					break;
				}
			}else
			{
				IObtainable* ObtainedObject=Cast<IObtainable>(InteractedActor);
				if (ObtainedObject)
				{
					ObtainedObject->Execute_AddToInventory(InteractedActor);
					InventoredItem=InteractedActor;
				}
			}
		}
	}
}

void ALiseWan::UseInventory()
{
	IObtainable* ObtainedObject=Cast<IObtainable>(InventoredItem);
	if (Inventory && ObtainedObject)
	{
		Inventory->GetFromInventory(ObtainedObject);
		InventoredItem=nullptr;
	}
}

float ALiseWan::GetCameraHeight() const
{
	return CameraHeight;
}

float ALiseWan::GetArmLength() const
{
	return  ArmLength;
}

UInventory* ALiseWan::GetInventory()
{
	return Inventory;
}

void ALiseWan::SetCharacterState(ECharacterState State)
{
	CharacterState=State;
}

ECharacterState ALiseWan::GetCharacterState()const
{
	return CharacterState;
}

FVector ALiseWan::GetLocation() const
{
	return GetPositionToMove->GetComponentLocation();
}
