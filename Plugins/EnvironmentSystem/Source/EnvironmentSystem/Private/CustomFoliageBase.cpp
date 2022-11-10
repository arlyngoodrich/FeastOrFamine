// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomFoliageBase.h"

#include "CustomFoliageISMC.h"
#include "EnvironmentSystem.h"
#include "Net/UnrealNetwork.h"

// Sets default values
ACustomFoliageBase::ACustomFoliageBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	// Adds Static mesh component to actor
	FoliageMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Foliage Mesh"));
	FoliageMesh->SetIsReplicated(true);
	SetRootComponent(FoliageMesh);

}

void ACustomFoliageBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty >& OutLifetimeProps) const
{

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACustomFoliageBase, OriginatingFoliageISMC);
	
}


// Called when the game starts or when spawned
void ACustomFoliageBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACustomFoliageBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UCustomFoliageISMC* ACustomFoliageBase::GetOriginatingFoliageISMC() const {return OriginatingFoliageISMC;}

void ACustomFoliageBase::OnSpawned(UCustomFoliageISMC* SetOriginatingFoliageISMC, ACustomFoliageManager* SetFoliageManager)
{
	if(SetOriginatingFoliageISMC == nullptr)
	{
		UE_LOG(LogEnvironmentSystem,Error,TEXT("%s was given null Foliage ISMC"),
			*GetName())

		return;
	}

	//If true to use Debug
	if(bUseDebugMesh == true && DebugMesh != nullptr)
	{
		//Set to debug mesh
		FoliageMesh->SetStaticMesh(DebugMesh);
	}
	else
	{
		//If not using debug mesh, try to use Foliage ISMC mesh
		if(SetOriginatingFoliageISMC->GetStaticMesh())

		{
			FoliageMesh->SetStaticMesh(SetOriginatingFoliageISMC->GetStaticMesh());
		}
		else
		{
			UE_LOG(LogEnvironmentSystem,Warning,TEXT("%s Foliage ISMC Mesh is null"),
				*GetName())
		}
	}
	

	
	OriginatingFoliageISMC = SetOriginatingFoliageISMC;
	FoliageManager = SetFoliageManager;
	OnRep_RemoveInstance();
	
}

void ACustomFoliageBase::OnRep_RemoveInstance() const
{
	int32 Index;
	if(OriginatingFoliageISMC->GetInstanceIndexFromLocation(GetActorLocation(),Index) == false)
	{
		UE_LOG(LogEnvironmentSystem,Warning,TEXT("%s Failed To Remove Instance"),
			*GetName())
	}
	
	OriginatingFoliageISMC->RemoveInstance_Safe(Index);
	
}

void ACustomFoliageBase::RequestRemoval()
{
	if(HasAuthority() == false){return;}
	Multicast_AddInstance();
}


void ACustomFoliageBase::Multicast_AddInstance_Implementation()
{
	
	OriginatingFoliageISMC->AddInstance_Safe(GetActorTransform());
	Destroy();
}

