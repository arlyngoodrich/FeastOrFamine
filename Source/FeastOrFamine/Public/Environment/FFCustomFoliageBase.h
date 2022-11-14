// 2022 Arlyn Goodrich All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "CustomFoliageBase.h"
#include "EnvironmentData.h"
#include "FFCustomFoliageBase.generated.h"

/**
 * 
 */
UCLASS()
class FEASTORFAMINE_API AFFCustomFoliageBase : public ACustomFoliageBase
{
	GENERATED_BODY()

protected:

	/**
	 * @brief Rewards that will be given to the harvesting player 
	 */
	UPROPERTY(EditDefaultsOnly,Category="Foliage System")
	TArray<FHarvestReward> HarvestRewards;

	/**
	 * @brief Attempts to give harvesting player harvest rewards.  Uses Harvest Interface so it's not character class specific
	 * @param HarvestingCharacter Character that should receive the harvest reward
	 * @return true if successfully given, false if not.  Does not take into account things like inventory space.  Only checks
	 * to make sure the receiving character has the interface
	 */
	virtual bool OnHarvest(ACharacter* HarvestingCharacter);

	/**
	 * @brief Converts the sub class of AItem base to FItems. Multiplies the quantity by the harvest amount
	 * @return Array of Item Data to add to the harvesting character
	 */
	TArray<FItemData> CalculateHarvestRewardItems();

};
