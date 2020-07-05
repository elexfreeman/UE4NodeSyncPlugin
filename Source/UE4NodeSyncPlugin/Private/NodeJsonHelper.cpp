// Fill out your copyright notice in the Description page of Project Settings.


#include "NodeJsonHelper.h"

TSharedPtr<FJsonObject> UNodeJsonHelper::fMakeVector(const FVector& vec)
{
	TSharedPtr<FJsonObject> resp = MakeShareable(new FJsonObject);

	resp->SetNumberField("X", vec.X);
	resp->SetNumberField("Y", vec.Y);
	resp->SetNumberField("Z", vec.Z);

	return resp;

}
