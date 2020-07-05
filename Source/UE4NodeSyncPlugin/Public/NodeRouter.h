// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"
#include "NodeRouter.generated.h"

/**
 * Для работы с маршрутами команд сети
 */
UCLASS()
class UE4NODESYNCPLUGIN_API UNodeRouter : public UObject
{
	GENERATED_BODY()
	
public:

	bool fIsMsgOk(const FString& msg);
	FString fGetRouteFromMsg(const FString& msg);
	TSharedPtr<FJsonObject> fGetDataFromMsg(const FString& msg);

};
