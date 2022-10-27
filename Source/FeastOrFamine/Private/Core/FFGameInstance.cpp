// 2022 Arlyn Goodrich All Rights Reserved


#include "Core/FFGameInstance.h"
#include "FeastOrFamine/FeastOrFamine.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

UFFGameInstance::UFFGameInstance()
{
}

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

void UFFGameInstance::JoinGame()
{
}

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
		}
	}
}

void UFFGameInstance::OnCreateSessionsComplete(FName SessionName, bool bSucceeded)
{
	if(bSucceeded)
	{
		GetWorld()->ServerTravel('/Game/FeastOrFamine/Maps/RockShoals?listen');
	}
	else
	{
		UE_LOG(LogFFGameInstance,Warning,TEXT("Failed to create online session"))
	}
}

void UFFGameInstance::OnFindSessionComplete(bool bSucceeded)
{
}

void UFFGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
}

void UFFGameInstance::CreateServer() const
{
	UE_LOG(LogFFGameInstance,Log,TEXT("Creating online session listen server"))

	FOnlineSessionSettings SessionSettings;
	SessionSettings.bAllowJoinInProgress = true;
	SessionSettings.bIsDedicated = false;
	SessionSettings.bIsLANMatch = (IOnlineSubsystem::Get()->GetSubsystemName() != "NULL") ? false : true;
	SessionSettings.bShouldAdvertise = true;
	SessionSettings.bUsesPresence = true;
	SessionSettings.NumPublicConnections = 5;

	SessionInterface->CreateSession(0,FName("Test Session"),SessionSettings);
	
}
