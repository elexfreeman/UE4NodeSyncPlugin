// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NodeSocketAC.h"
#include "GameFramework/Controller.h"
#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"
#include "AIController.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"

#include "./RoutePath.h"
#include "./NodeJsonHelper.h"

#include "CharacterSync.generated.h"

/**
 * 
 */
UCLASS()
class UE4NODESYNCPLUGIN_API UCharacterSync : public UObject
{
	GENERATED_BODY()

private:
	UNodeSocketAC* vNodeSocketAC;

	// auth token
	FString sAuthToken = TEXT("");

public:

	UCharacterSync();

	/**
	 * builder constructor
	 * _vNodeSocketAC - instance of UNodeSocketAC
	 */
	UCharacterSync* fInitNodeSocket(UNodeSocketAC* _vNodeSocketAC);

	/**
	 * builder constructor
	 * _sAuthToken - auth token
	 */
	UCharacterSync* fInitToken(FString _sAuthToken);


	/*
	 * Move to loc and send to srv
	 */
	bool fSimpleMoveToLocation(AController* Controller, const FVector& GoalLocation);

	/*
	 * Send move to loc to server
	 */
	void fSendMoveToLoc(const FVector& GoalLocation);

	static UPathFollowingComponent* InitNavigationControl(AController& Controller);




	
};
