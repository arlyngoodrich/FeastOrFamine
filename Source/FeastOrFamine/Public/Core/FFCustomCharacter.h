// 2022 Arlyn Goodrich All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "CustomCharacter.h"
#include "Environment/FFHarvestInterface.h"
#include "FFCustomCharacter.generated.h"

/**
 * 
 */
UCLASS()
class FEASTORFAMINE_API AFFCustomCharacter : public ACustomCharacter, public  IFFHarvestInterface
{
	GENERATED_BODY()

public:


	/**
 * @brief Called by the foliage actor when the player harvests it
 * @param HarvestRewardItem 
 */
	virtual void GiveHarvestReward_Implementation(FItemData HarvestRewardItem) override;

	
};
