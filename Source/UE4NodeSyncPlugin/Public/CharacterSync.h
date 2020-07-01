// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "NodeSocketAC.h"
#include "GameFramework/Controller.h"
#include "NavigationSystem.h"
#include "Navigation/PathFollowingComponent.h"
#include "AIController.h"

#include "./RoutePath.h"

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


public:

	UCharacterSync();

	/**
		builder constructor
		_vNodeSocketAC - instance of UNodeSocketAC
	*/
	UCharacterSync* fInitNodeSocket(UNodeSocketAC* _vNodeSocketAC);


	bool fSimpleMoveToLocation(AController* Controller, const FVector& GoalLocation);

	static UPathFollowingComponent* InitNavigationControl(AController& Controller);


	
};
