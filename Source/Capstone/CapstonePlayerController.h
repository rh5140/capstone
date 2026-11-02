// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputAction.h"
#include "CapstonePlayerController.generated.h"

class UNiagaraSystem;
class UInputMappingContext;
class UInputAction;
class UPathFollowingComponent;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  Player controller for a top-down perspective game.
 *  Implements point and click based controls
 */
UCLASS(abstract)
class ACapstonePlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	/** MappingContext */
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	TObjectPtr<class UInputAction> MoveForwardAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input)
	TObjectPtr<class UInputAction> MoveRightAction;

	void OnMoveForward(const FInputActionInstance& Instance);
	void OnMoveRight(const FInputActionInstance& Instance);
	
public:

	/** Constructor */
	ACapstonePlayerController();

protected:

	/** Initialize input bindings */
	virtual void SetupInputComponent() override;
};


