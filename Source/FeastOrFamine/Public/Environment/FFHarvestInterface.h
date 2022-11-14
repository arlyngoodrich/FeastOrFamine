// 2022 Arlyn Goodrich All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemSystem/Public/ItemData.h"
#include "FFHarvestInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UFFHarvestInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FEASTORFAMINE_API IFFHarvestInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	
public:

	/**
	 * @brief Called by the foliage actor when the player harvests it
	 * @param HarvestRewardItem 
	 */
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category="Harvest System")
	void GiveHarvestReward(FItemData HarvestRewardItem);
	
};
