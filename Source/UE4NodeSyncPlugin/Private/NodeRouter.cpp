// Fill out your copyright notice in the Description page of Project Settings.


#include "NodeRouter.h"


bool UNodeRouter::fIsMsgOk(const FString& msg)
{
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(msg);
	TSharedPtr<FJsonObject> request = MakeShareable(new FJsonObject);
	FJsonSerializer::Deserialize(JsonReader, request);

	bool out = false;
	request->TryGetBoolField(TEXT("ok"), out);

	return out;

}

FString UNodeRouter::fGetRouteFromMsg(const FString& msg)
{
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(msg);
	TSharedPtr<FJsonObject> request = MakeShareable(new FJsonObject);
	FJsonSerializer::Deserialize(JsonReader, request);

	FString out;
	request->TryGetStringField("sRoute", out);

	return out;
}


TSharedPtr<FJsonObject> UNodeRouter::fGetDataFromMsg(const FString& msg)
{
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(msg);
	TSharedPtr<FJsonObject> request = MakeShareable(new FJsonObject);
	FJsonSerializer::Deserialize(JsonReader, request);

	TSharedPtr<FJsonObject> data = MakeShareable(new FJsonObject);

	data = request->GetObjectField("data");

	return data;
}
