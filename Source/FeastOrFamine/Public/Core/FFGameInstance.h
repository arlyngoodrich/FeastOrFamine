// 2022 Arlyn Goodrich All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "OnlineSessionSettings.h"
#include "FFGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FEASTORFAMINE_API UFFGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UFFGameInstance();

protected:

	// ----------- Main Menu UI Commands ----------- //

	/**
	 * @brief Will load default level and optionally create online session if playing online
	 * @param bShouldPlayOnline If the player should host a listen server for this session
	 */
	UFUNCTION(BlueprintCallable)
	void StartGame(bool bShouldPlayOnline);

	/**
	 * @brief If the player would like to join a game in progress
	 */
	UFUNCTION(BlueprintCallable)
	void JoinGame();
	

	// ----------- Online SubSystem Code ----------- //
	
	/**
	 * @brief Stores results from Session Search 
	 */
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
	
	/**
	 * @brief Online Session Interface pointer. Allows to create sessions, search for sessions, and join sessions. 
	 */
	IOnlineSessionPtr SessionInterface;
	
	virtual void Init() override;

	/**
	 * @brief Called by delegate from the Session Interface when a session is created
	 * @param SessionName Name of the session that was created
	 * @param bSucceeded If the session was successfully created 
	 */
	virtual void OnCreateSessionsComplete(FName SessionName, bool bSucceeded);

	/**
	 * @brief Called by delegate from the Session Interface when find sessions is complete
	 * @param bSucceeded If the interface succeeded in finding online sessions 
	 */
	virtual void OnFindSessionComplete(bool bSucceeded);

	/**
	 * @brief Called by delegate from interface when Session is joined
	 * @param SessionName Name of the session Joined
	 * @param Result Success or failure of join
	 */
	virtual void OnJoinSessionComplete(FName SessionName,EOnJoinSessionCompleteResult::Type Result);
	
	/**
	 * @brief Called by Start Game if bShouldPlayOnline = true.  Creates online session as listen server. 
	 */
	void CreateServer() const;
};
