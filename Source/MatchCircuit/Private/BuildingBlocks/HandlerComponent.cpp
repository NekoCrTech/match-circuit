// Created by Neko Creative Technologies


#include "BuildingBlocks/HandlerComponent.h"

#include "BuildingBlocks/Laser.h"

// Sets default values for this component's properties
UHandlerComponent::UHandlerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UHandlerComponent::BeginPlay()
{
	Super::BeginPlay();
}

FLinearColor UHandlerComponent::SetAlphaToOne(FLinearColor InColor)
{
	return FLinearColor(InColor.R, InColor.G, InColor.B, 1.0f);
}

FLinearColor UHandlerComponent::GetVisibleColor()
{
	if (UsedColor==EColorSelection::FirstLaserHit)
	{
		PassByColor = LasersInQueue[0]->ColorOverride;
	}
	else if (UsedColor==EColorSelection::LastLaserHit)
	{
		PassByColor = LasersInQueue[LasersInQueue.Num()-1]->ColorOverride;
	}
	else
	{
		PassByColor = SetAlphaToOne(MergedColor);
	}
	return PassByColor;
}

void UHandlerComponent::RecalculateColors(ALaser* InputPin)
{
	if (UsedColor==EColorSelection::MergeLasers)
	{
		MergedColor = FLinearColor::Black;
		for (ALaser* Laser : LasersInQueue)
		{
			MergedColor = Laser->ColorOverride + MergedColor;
		}
	}
	ComponentColorChange(InputPin);
}

void UHandlerComponent::ComponentColorChange(ALaser* Modified)
{
	for (UActorComponent* LinkedComponent : LinkedComponents)
	{
		LinkedComponent.
	}
}

