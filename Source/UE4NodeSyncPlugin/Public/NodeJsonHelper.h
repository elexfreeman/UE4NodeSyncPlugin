// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"

#include "NodeJsonHelper.generated.h"

/**
 * 
 */
UCLASS()
class UE4NODESYNCPLUGIN_API UNodeJsonHelper : public UObject
{
	GENERATED_BODY()

public:

	static TSharedPtr<FJsonObject> fMakeVector(const FVector& vec);
	
};
