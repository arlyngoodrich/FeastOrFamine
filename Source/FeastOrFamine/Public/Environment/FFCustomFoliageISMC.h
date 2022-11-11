// 2022 Arlyn Goodrich All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "CustomFoliageISMC.h"
#include "EnvironmentData.h"
#include "FFCustomFoliageISMC.generated.h"

class ACustomFoliageBase;

/**
 * 
 */
UCLASS()
class FEASTORFAMINE_API UFFCustomFoliageISMC : public UCustomFoliageISMC
{
	GENERATED_BODY()

public:

	virtual TSubclassOf<ACustomFoliageBase> GetCustomFoliageBase() override;

protected:

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Foliage System")
	TArray<FFoliageActorMeshMap> FoliageActorMeshMaps;

	bool GetActorClassFromMeshMap(TSubclassOf<ACustomFoliageBase>& OutFoliageClass);
	
};
