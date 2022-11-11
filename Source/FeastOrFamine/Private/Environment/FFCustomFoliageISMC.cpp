// 2022 Arlyn Goodrich All Rights Reserved


#include "Environment/FFCustomFoliageISMC.h"

#include "FeastOrFamine/FeastOrFamine.h"

TSubclassOf<ACustomFoliageBase> UFFCustomFoliageISMC::GetCustomFoliageBase()
{
	
	TSubclassOf<ACustomFoliageBase> ClassToSpawn = nullptr;

	if(GetActorClassFromMeshMap(ClassToSpawn))
	{
		return ClassToSpawn;
	}
	else
	{

		UE_LOG(LogFFEnvironmentSystem,Log,TEXT("%s could not match mesh with actor map reverting to spawn default actor"),
	*GetName())
		
		return DefaultFoliageActorClass;
	}
	
}

bool UFFCustomFoliageISMC::GetActorClassFromMeshMap(TSubclassOf<ACustomFoliageBase>& OutFoliageClass)
{
	OutFoliageClass = nullptr;
	
	for (int i = 0; i < FoliageActorMeshMaps.Num(); ++i)
	{
		if(FoliageActorMeshMaps[i].FISMCStaticMesh == GetStaticMesh())
		{
			FoliageActorMeshMaps[i].FoliageActorToSpawn = OutFoliageClass;
			return true;
		}
	}
	
	return false;
}

