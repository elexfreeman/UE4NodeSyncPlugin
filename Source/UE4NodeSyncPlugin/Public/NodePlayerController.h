// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NodeSocketAC.h"
#include "./CharacterSync.h"
#include "./TopDownCharacter.h"
#include "./NodeRouter.h"

#include "NodePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UE4NODESYNCPLUGIN_API ANodePlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	ANodePlayerController();

	UPROPERTY(BluePrintReadWrite, Category = "AA_Net")
	UNodeSocketAC* vNodeSocketAC;

	UCharacterSync* vCharacterSync;
	UNodeRouter* vNodeRouter;

	// --------------------------------------------
	//					Network



	UPROPERTY(BluePrintReadWrite, Category = "AA_Net")
		FString sServerAddress = TEXT("127.0.0.1");

	UPROPERTY(BluePrintReadWrite, Category = "AA_Net")
		int32 nServerPort = 3007;



protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	bool bOk = true;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();

	/** Navigate player to the current touch location. */
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

	
};
