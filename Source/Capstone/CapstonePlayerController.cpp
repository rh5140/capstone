// Copyright Epic Games, Inc. All Rights Reserved.

#include "CapstonePlayerController.h"
#include "GameFramework/Pawn.h"
#include "CapstoneCharacter.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "Capstone.h"

ACapstonePlayerController::ACapstonePlayerController()
{
	// configure the controller
	bShowMouseCursor = false;
}

void ACapstonePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Only set up input on local player controllers
	if (IsLocalPlayerController())
	{
		// Add Input Mapping Context
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}

		// Set up action bindings
		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
		{
			EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &ACapstonePlayerController::OnMoveForward);
			EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &ACapstonePlayerController::OnMoveRight);
		}
		else
		{
			UE_LOG(LogCapstone, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
		}
	}
}

void ACapstonePlayerController::OnMoveForward(const FInputActionInstance& Instance)
{
	if (APawn* MyPawn = GetPawn())
	{
		float AxisValue = Instance.GetValue().Get<float>();
		MyPawn->AddMovementInput(FVector::ForwardVector, AxisValue);
	}
}

void ACapstonePlayerController::OnMoveRight(const FInputActionInstance& Instance)
{
	if (APawn* MyPawn = GetPawn())
	{
		float AxisValue = Instance.GetValue().Get<float>();
		MyPawn->AddMovementInput(FVector::LeftVector, AxisValue);
	}
}

