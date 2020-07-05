// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterSync.h"


UCharacterSync::UCharacterSync()
{
	vNodeSocketAC = nullptr;
}

UCharacterSync* UCharacterSync::fInitNodeSocket(UNodeSocketAC* _vNodeSocketAC)
{
	vNodeSocketAC = _vNodeSocketAC;
	return this;
}

UCharacterSync* UCharacterSync::fInitToken(FString _sAuthToken)
{
	sAuthToken = _sAuthToken;
	return this;
}

UPathFollowingComponent* UCharacterSync::InitNavigationControl(AController& Controller)
{
	AAIController* AsAIController = Cast<AAIController>(&Controller);
	UPathFollowingComponent* PathFollowingComp = nullptr;

	if (AsAIController)
	{
		PathFollowingComp = AsAIController->GetPathFollowingComponent();
	}
	else
	{
		PathFollowingComp = Controller.FindComponentByClass<UPathFollowingComponent>();
		if (PathFollowingComp == nullptr)
		{
			PathFollowingComp = NewObject<UPathFollowingComponent>(&Controller);
			PathFollowingComp->RegisterComponentWithWorld(Controller.GetWorld());
			PathFollowingComp->Initialize();
		}
	}

	return PathFollowingComp;
}


bool UCharacterSync::fSimpleMoveToLocation(AController* Controller, const FVector& GoalLocation)
{
	bool bOk = true;
	UNavigationSystemV1* NavSys = Controller ? FNavigationSystem::GetCurrent<UNavigationSystemV1>(Controller->GetWorld()) : nullptr;
	if (NavSys == nullptr || Controller == nullptr || Controller->GetPawn() == nullptr)
	{
		bOk = false;
	}

	if (!bOk) { return bOk; }

	UPathFollowingComponent* PFollowComp = UCharacterSync::InitNavigationControl(*Controller);

	bOk = !((PFollowComp == nullptr) || (!PFollowComp->IsPathFollowingAllowed()));
	if (!bOk) { return bOk; }

	// send to srv
	fSendMoveToLoc(GoalLocation);
	

	// moving

	const bool bAlreadyAtGoal = PFollowComp->HasReached(GoalLocation, EPathFollowingReachMode::OverlapAgent);

	// script source, keep only one move request at time
	if (PFollowComp->GetStatus() != EPathFollowingStatus::Idle)
	{
		PFollowComp->AbortMove(*NavSys, FPathFollowingResultFlags::ForcedScript | FPathFollowingResultFlags::NewRequest
			, FAIRequestID::AnyRequest, bAlreadyAtGoal ? EPathFollowingVelocityMode::Reset : EPathFollowingVelocityMode::Keep);
	}

	// script source, keep only one move request at time
	if (PFollowComp->GetStatus() != EPathFollowingStatus::Idle)
	{
		PFollowComp->AbortMove(*NavSys, FPathFollowingResultFlags::ForcedScript | FPathFollowingResultFlags::NewRequest);
	}

	if (bAlreadyAtGoal)
	{
		PFollowComp->RequestMoveWithImmediateFinish(EPathFollowingResult::Success);
	}
	else
	{
		const FVector AgentNavLocation = Controller->GetNavAgentLocation();
		const ANavigationData* NavData = NavSys->GetNavDataForProps(Controller->GetNavAgentPropertiesRef(), AgentNavLocation);
		if (NavData)
		{
			FPathFindingQuery Query(Controller, *NavData, AgentNavLocation, GoalLocation);
			FPathFindingResult Result = NavSys->FindPathSync(Query);
			if (Result.IsSuccessful())
			{
				PFollowComp->RequestMove(FAIMoveRequest(GoalLocation), Result.Path);
			}
			else if (PFollowComp->GetStatus() != EPathFollowingStatus::Idle)
			{
				PFollowComp->RequestMoveWithImmediateFinish(EPathFollowingResult::Invalid);
			}
		}
	}

	


	return bOk;

}


void UCharacterSync::fSendMoveToLoc(const FVector& GoalLocation)
{
	TSharedPtr<FJsonObject> request = MakeShareable(new FJsonObject);
	TSharedPtr<FJsonObject> data = MakeShareable(new FJsonObject);

	data->SetObjectField("loc", UNodeJsonHelper::fMakeVector(GoalLocation));

	request->SetStringField("sClientToken", FString(TEXT("")));
	request->SetStringField("sRoute", FString(TEXT("client_move_to_loc")));

	request->SetObjectField("data", data);

	FString sMsg;
	TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&sMsg);
	FJsonSerializer::Serialize(request.ToSharedRef(), Writer);

	vNodeSocketAC->EmitStr(sMsg);
}
