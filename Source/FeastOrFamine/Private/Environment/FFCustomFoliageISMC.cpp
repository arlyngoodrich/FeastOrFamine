// 2022 Arlyn Goodrich All Rights Reserved


#include "Environment/FFCustomFoliageISMC.h"

#include "FeastOrFamine/FeastOrFamine.h"

TSubclassOf<ACustomFoliageBase> UFFCustomFoliageISMC::GetCustomFoliageBase()
{
	
	TSubclassOf<ACustomFoliageBase> ClassToSpawn = nullptr;

	if(GetActorClassFromMeshMap(ClassToSpawn))
	{

		if(ClassToSpawn == nullptr)
		{
			UE_LOG(LogFFEnvironmentSystem,Log,TEXT("Class To Spawn is Nullptr"))
			return DefaultFoliageActorClass;
		}

		//UE_LOG(LogFFEnvironmentSystem,Log,TEXT("Returned class %s from map"),*ClassToSpawn->GetName())
		return ClassToSpawn;
	}
	else
	{

		UE_LOG(LogFFEnvironmentSystem,Log,TEXT("%s could not %s mesh with actor map reverting to spawn default actor"),
	*GetName(),*GetStaticMesh()->GetName())
		
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
			OutFoliageClass = FoliageActorMeshMaps[i].FoliageActorToSpawn;
			return true;
		}
	}
	
	return false;
}

