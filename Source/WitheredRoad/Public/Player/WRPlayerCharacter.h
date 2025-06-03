// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "WRPlayerCharacter.generated.h"


class UInputMappingContext;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class WITHEREDROAD_API AWRPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:


protected:

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> DefaultInputMapping;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Move;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Look;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> Input_Jump;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USpringArmComponent> SprngArmComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCameraComponent> CamComp;

	void Move(const FInputActionInstance& Instance);

	void Look(const FInputActionValue& InputValue);


public:

	// Sets default values for this character's properties
	AWRPlayerCharacter();

	virtual FVector GetPawnViewLocation() const override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
