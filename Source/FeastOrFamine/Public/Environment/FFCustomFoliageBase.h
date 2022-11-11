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

	UPROPERTY(EditDefaultsOnly,Category="Foliage System")
	TArray<FHarvestReward> HarvestRewards;
	
};
