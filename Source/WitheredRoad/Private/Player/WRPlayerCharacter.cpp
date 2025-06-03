// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/WRPlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"



// Sets default values
AWRPlayerCharacter::AWRPlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SprngArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SprngArmComp"));
	SprngArmComp->bUsePawnControlRotation = true;
	SprngArmComp->SetupAttachment(RootComponent);
	SprngArmComp->SetUsingAbsoluteRotation(true);

	CamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CamComp"));
	CamComp->SetupAttachment(SprngArmComp);



	UCharacterMovementComponent* ChMoveComp = GetCharacterMovement();
	ChMoveComp->bUseControllerDesiredRotation = true;
	ChMoveComp->MaxWalkSpeed = 550.0f;
	ChMoveComp->JumpZVelocity = 550;
	ChMoveComp->GravityScale = 1.35f;
	ChMoveComp->BrakingDecelerationFalling = 200.f;

}



// Called every frame
void AWRPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWRPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	const APlayerController* PC = GetController<APlayerController>();
	const ULocalPlayer* LP = PC->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();

	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(DefaultInputMapping, 0);

	UEnhancedInputComponent* InpComp = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	// Fix: Ensure the correct function signature is used for BindAction  
	InpComp->BindAction(Input_Move, ETriggerEvent::Triggered, this, &AWRPlayerCharacter::Move);
	InpComp->BindAction(Input_Look, ETriggerEvent::Triggered, this, &AWRPlayerCharacter::Look);
	InpComp->BindAction(Input_Jump, ETriggerEvent::Triggered, this, &AWRPlayerCharacter::Jump);
}

void AWRPlayerCharacter::Move(const FInputActionInstance& Instance)
{

	FRotator CtrlRot = GetControlRotation();
	CtrlRot.Pitch = 0.0f;
	CtrlRot.Roll = 0.0f;

	// Get value from input (combined value from WASD keys or single Gamepad stick) and convert to Vector (x,y)
	const FVector2D AxisValue = Instance.GetValue().Get<FVector2D>();

	// Move forward/back
	AddMovementInput(CtrlRot.Vector(), AxisValue.Y);

	// Move Right/Left strafe
	const FVector RightVector = CtrlRot.RotateVector(FVector::RightVector);
	AddMovementInput(RightVector, AxisValue.X);

}

void AWRPlayerCharacter::Look(const FInputActionValue& InputValue)
{

	const FVector2D Value = InputValue.Get<FVector2D>();

	AddControllerYawInput(Value.X);
	AddControllerPitchInput(Value.Y);


}

FVector AWRPlayerCharacter::GetPawnViewLocation() const
{

	return CamComp->GetComponentLocation();

}

