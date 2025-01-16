// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/Player/LiseWan.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

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
	}
}

void ALiseWan::Move(const FInputActionValue& value)
{
	if (CharacterState!=ECharacterState::ECS_Notinteracted)return;
	
	const auto MovementVector=value.Get<FVector2D>();
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
}

void ALiseWan::Look(const FInputActionValue& value)
{
	const auto LookAxisVector=value.Get<FVector2D>();

	if (Controller!=nullptr && LookAxisVector.X!=0)
	{
		AddControllerYawInput(LookAxisVector.X);
	}
	if (Controller!=nullptr && LookAxisVector.Y!=0)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}