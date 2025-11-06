// Created by Neko Creative Technologies


#include "BuildingBlocks/Laser.h"
#include "BuildingBlocks/HandlerComponent.h"

// Sets default values
ALaser::ALaser()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	

}

// Called when the game starts or when spawned
void ALaser::BeginPlay()
{
	Super::BeginPlay();

	InitializeLaser(ColorOverride,PreviousLasers,OwningHandler,ActorsToIgnore);
}

// Called every frame
void ALaser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateLength(Range);
	
	FCollisionQueryParams QueryParams;
	for (const AActor* Actor : ActorsToIgnore)
	{
		QueryParams.AddIgnoredActor(Actor);
	}
	TArray<FHitResult> OutHits;
	bool bHit = GetWorld()->SweepMultiByChannel(
		OutHits,
		GetActorLocation(),
		GetActorLocation()+ GetActorForwardVector()*Range,
		FQuat::Identity,
		ECC_GameTraceChannel1, // Or ECC_LaserTrace if your custom channel is named that way
		FCollisionShape::MakeSphere(0.5),
		QueryParams
	);

	for (const FHitResult& Hit : OutHits)
	{
		if (Hit.Distance<=Range)
		{
			UpdateLength(Hit.Distance);
		}
		HandleHitActors(Hit);
	}

	for (TSet<UHandlerComponent*> Difference = CurrentHitHandlers.Difference(PreviouslyHitHandlers); UHandlerComponent* Handler : Difference)
	{
		if (IsValid(Handler))
		{
			Handler->Execute_LaserStopHitting(Handler,this);
			HittingHandlers.Remove(Handler);
		}
	}
	
	PreviouslyHitHandlers = CurrentHitHandlers;
	CurrentHitHandlers.Empty();
}

void ALaser::InitializeLaser(const FLinearColor InColorOverride, const TArray<ALaser*> InPreviousLasers, UHandlerComponent* InOwningHandler, TArray<AActor*> InActorsToIgnore)
{
	
	if (SourceMaterial == nullptr || Mesh == nullptr)
	{
		Destroy();
		return;
	}

	ColorOverride = InColorOverride;
	PreviousLasers = InPreviousLasers;
	OwningHandler = InOwningHandler;
	ActorsToIgnore = InActorsToIgnore;
	
	Mesh->SetStaticMesh(LaserMesh);
	LaserMaterial = Mesh->CreateDynamicMaterialInstance(0,SourceMaterial);
	ChangeLaserColor(ColorOverride);
}

void ALaser::ChangeLaserColor(FLinearColor Value)
{
	ColorOverride = Value;

	LaserMaterial->SetVectorParameterValue("BaseColor",ColorOverride);
	for (UHandlerComponent* Handler : PreviouslyHitHandlers)
	{
		Handler->Execute_IntermediateChange(Handler,this);
	}
}

void ALaser::UpdateLength(float InputPin)
{
	if(!FMath::IsNearlyEqual(InputPin,PreviousLength, 0.000001f))
	{
		PreviousLength = InputPin;
		Mesh->SetWorldScale3D(FVector(0.1f, 0.1f, PreviousLength/100.0f));
	}
}

void ALaser::HandleHitActors(FHitResult InputPin)
{
	if(UHandlerComponent* HandlerLocal = Cast<UHandlerComponent>(InputPin.GetActor()->GetComponentByClass(UHandlerComponent::StaticClass())))
	{
		if(IsNotInPath(HandlerLocal))
		{
			HittingHandlers.Add(HandlerLocal,InputPin);

			if (PreviouslyHitHandlers.Contains(HandlerLocal))
			{
				HandlerLocal->Execute_LaserUpdateHitting(HandlerLocal,this,InputPin);
			}
			else
			{
				HandlerLocal->Execute_LaserStartHitting(HandlerLocal,this,InputPin);
			}
			CurrentHitHandlers.Add(HandlerLocal);
		}
	}
}

bool ALaser::IsNotInPath(UHandlerComponent* InputHandler)
{
	if(!PreviousLasers.IsEmpty())
	{
		for (ALaser* Laser : PreviousLasers)
		{
			if(OwningHandler == Laser->OwningHandler)
			{
				return false;
			}
			if(!Laser->IsNotInPath(InputHandler))
			{
				return false;
			}
		}
	}
	return true;
}

void ALaser::LaserStopHitting_Implementation(ALaser* Input)
{
	for(UHandlerComponent* Handler : PreviouslyHitHandlers)
	{
		Handler->Execute_LaserStopHitting(Handler,this);
	}
	Destroy();
}
