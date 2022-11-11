// 2022 Arlyn Goodrich All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"
#include "EnvironmentData.Generated.h"


/**
 * @brief Items given when a foliage actor is harvested
 */
USTRUCT(BlueprintType)
struct FHarvestReward 
{
	GENERATED_USTRUCT_BODY()

	/**
	 * @brief Item to give 
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Harvesting")
	FItemData HarvestRewardItem;

	/**
	 * @brief Default amount of item to give
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory Position")
	int32 RewardAmount;

	/**
	 * @brief Is valid flag, null with default constructor
	 */
	bool bIsValid; 

	
	/**
	 * @brief Default constructor will be invalid
	 */
	FHarvestReward()
	{
		HarvestRewardItem = FItemData();
		RewardAmount = 0;
		bIsValid = false;
	}

	/**
	 * @brief Default constructor that will be valid
	 * @param SetHarvestRewardItem Item that will be rewarded
	 * @param SetRewardAmount Default of amount of item that will be given
	 */
	FHarvestReward(const FItemData SetHarvestRewardItem, const int32 SetRewardAmount)
	{
		HarvestRewardItem = SetHarvestRewardItem;
		RewardAmount = SetRewardAmount;
		bIsValid = true;
	}


	/**
	 * @brief Helper function to convert harvest reward into string
	 * @return HarvestReward as string
	 */
	FString GetRewardAsString() const
	{
		FString Reward;

		Reward += HarvestRewardItem.DisplayName.ToString();
		Reward.Append(" : ");
		Reward.AppendInt(RewardAmount);

		return Reward;
	}


	/**
	 * @brief The structs are the same if:
	 * The reward item is the same
	 * The default amount given is the same
	 * Both items are valid
	 */
	bool operator==(const FHarvestReward& HarvestReward) const
	{
		return
			(
				HarvestReward.HarvestRewardItem == HarvestRewardItem &&
				HarvestReward.RewardAmount == RewardAmount &&
				HarvestReward.bIsValid &&
				bIsValid
			);
	}
};
