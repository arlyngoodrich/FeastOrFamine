// 2022 Arlyn Goodrich All Rights Reserved


#include "Environment/FFCustomFoliageBase.h"
#include "FeastOrFamine/FeastOrFamine.h"
#include "Environment/FFHarvestInterface.h"
#include "GameFramework/Character.h"


bool AFFCustomFoliageBase::OnHarvest(ACharacter* HarvestingCharacter)
{
	
	if(HarvestingCharacter == nullptr)
	{
		UE_LOG(LogFFEnvironmentSystem, Warning,TEXT("Custom Foliage being harvested by null character"))
		return false;
	}
	
	if(HarvestingCharacter->Implements<UFFHarvestInterface>())
	{
		IFFHarvestInterface* HarvestInterface = Cast<IFFHarvestInterface>(HarvestingCharacter);

		const TArray<FItemData> HarvestRewardItems = CalculateHarvestRewardItems();

		//If 0 rewards, return false and log warning 
		if(HarvestRewardItems.Num() == 0)
		{
			UE_LOG(LogFFEnvironmentSystem,Warning,TEXT("%s does not have any harvest rewards"),*GetClass()->GetName())
			return false;
		}
		
		for (int i = 0; i < HarvestRewardItems.Num(); ++i)
		{

			UE_LOG(LogFFEnvironmentSystem,Log,TEXT("%s is giving %s as a harvest reward to %s"),
				*GetName(),*HarvestRewardItems[i].DisplayName.ToString(),*HarvestingCharacter->GetName())
			
			HarvestInterface->GiveHarvestReward(HarvestRewardItems[i]);
		}

		return true;
	
	}
	else
	{
		UE_LOG(LogFFEnvironmentSystem,Warning,TEXT("Harvesting character does not implement harvesting interface"))
		return false;
	}

}

TArray<FItemData> AFFCustomFoliageBase::CalculateHarvestRewardItems()
{
	TArray<FItemData> HarvestRewardItems;

	for (int i = 0; i < HarvestRewards.Num(); ++i)
	{
		const AItemBase* DefaultItemBase = Cast<AItemBase>(HarvestRewards[i].HarvestRewardClass.GetDefaultObject());
		FItemData HarvestItem = DefaultItemBase->GetItemData();
		HarvestItem.SetFromDefaultObject(HarvestRewards[i].HarvestRewardClass);

		//Make sure harvest reward amount is greater than or equal to zero, if not then skip adding
		if(HarvestRewards[i].RewardAmount > 0)
		{
			HarvestItem.ItemQuantity *= HarvestRewards[i].RewardAmount;
			HarvestRewardItems.Add(HarvestItem);
		}
	}

	return HarvestRewardItems;
}
