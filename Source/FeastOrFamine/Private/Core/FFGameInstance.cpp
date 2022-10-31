// 2022 Arlyn Goodrich All Rights Reserved


#include "Core/FFGameInstance.h"
#include "FeastOrFamine/FeastOrFamine.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "CoreGlobals.h"


UFFGameInstance::UFFGameInstance()
{
}

// ----------- Main Menu UI Commands ----------- //

void UFFGameInstance::StartGame(bool bShouldPlayOnline)
{
	UE_LOG(LogFFGameInstance, Log, TEXT("Starting New Game.  Should play Online = %s"), bShouldPlayOnline ? TEXT("true") : TEXT("false"))

	if(bShouldPlayOnline)
	{
		CreateServer();
	}
	else
	{
		//Open Default Level
		UGameplayStatics::OpenLevel(GetWorld(),"RockShoals");
	}
	
}

void UFFGameInstance::SearchForSessions()
{

	UE_LOG(LogFFGameInstance, Log, TEXT("Starting to search for onnline sessions..."))
	
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->bIsLanQuery = (IOnlineSubsystem::Get()->GetSubsystemName() == "NULL");
	SessionSearch->MaxSearchResults = 10000;
	SessionSearch->QuerySettings.Set("SEARCH_PRESENCE",true,EOnlineComparisonOp::Equals);

	SessionInterface->FindSessions(0,SessionSearch.ToSharedRef());
}

// ----------- Instance  Info ----------- //

FString UFFGameInstance::GetProjectVersion()
{

	FString ProjectVersion;
	
	if(GConfig)
	{
		GConfig->GetString(
			TEXT("/Script/EngineSettings.GeneralProjectSettings"),
			TEXT("ProjectVersion"),
			ProjectVersion,
			GGameIni
			);
	}
	else
	{
		UE_LOG(LogFFGameInstance,Warning,TEXT("Game instance could not get GConfig"))
	}

	return ProjectVersion;
}


// ----------- Online SubSystem Code ----------- //

void UFFGameInstance::Init()
{
	Super::Init();

	if(const IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get())
	{
		SessionInterface = Subsystem->GetSessionInterface();
		if(SessionInterface.IsValid())
		{
			//Assign delegates from session interface
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this,&UFFGameInstance::OnCreateSessionsComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this,&UFFGameInstance::OnFindSessionComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this,&UFFGameInstance::OnJoinSessionComplete);
			UE_LOG(LogFFGameInstance,Log,TEXT("Online subsystem successful init"))
		}
	}
	else
	{
		UE_LOG(LogFFGameInstance,Warning,TEXT("No valid online sub system"))
	}
}

void UFFGameInstance::OnCreateSessionsComplete(FName SessionName, bool bSucceeded)
{
	if(bSucceeded)
	{
		UE_LOG(LogFFGameInstance,Log,TEXT("Created online session starting sever travel to default game map"))
		GetWorld()->ServerTravel("/Game/FeastOrFamine/Maps/RockShoals?listen");
	}
	else
	{
		UE_LOG(LogFFGameInstance,Warning,TEXT("Failed to create online session"))
	}
}

void UFFGameInstance::OnFindSessionComplete(bool bSucceeded)
{
	if(bSucceeded)
	{
		const TArray<FOnlineSessionSearchResult> SearchResults = SessionSearch->SearchResults;
		
		if(SearchResults.Num())
		{
			UE_LOG(LogFFGameInstance,Log,TEXT(" Found %d online sessions"),SearchResults.Num())

			//TEMP NEED TO UPDATE 
			SessionInterface->JoinSession(0,FName("TestSession"),SearchResults[0]);
			
		}
		else
		{
			UE_LOG(LogFFGameInstance,Log,TEXT(" Found 0 online sessions"))
		}
	}
	else
	{
		UE_LOG(LogFFGameInstance,Warning,TEXT("Failed to find online sessions"))
	}
}



void UFFGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if(APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),0))
	{
		FString JoinAddress = "";
		SessionInterface->GetResolvedConnectString(SessionName,JoinAddress);
		if(JoinAddress != "")
		{
			UE_LOG(LogFFGameInstance,Log,TEXT("Joining address: %s"),*JoinAddress)
			PlayerController->ClientTravel(JoinAddress,ETravelType::TRAVEL_Absolute);
		}
		else
		{
			UE_LOG(LogFFGameInstance,Warning,TEXT("No valid join address"))
		}
	}
	
}

void UFFGameInstance::CreateServer() const
{
	UE_LOG(LogFFGameInstance,Log,TEXT("Staring to create online session listen server"))

	FOnlineSessionSettings SessionSettings;
	SessionSettings.bAllowJoinInProgress = true;
	SessionSettings.bIsDedicated = false;
	SessionSettings.bIsLANMatch = (IOnlineSubsystem::Get()->GetSubsystemName() != "NULL") ? false : true;
	SessionSettings.bShouldAdvertise = true;
	SessionSettings.bUsesPresence = true;
	SessionSettings.NumPublicConnections = 5;

	SessionInterface->CreateSession(0,FName("Test Session"),SessionSettings);
	
}
