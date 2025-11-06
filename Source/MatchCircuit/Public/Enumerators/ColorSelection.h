// Created by Neko Creative Technologies

#pragma once

#include "CoreMinimal.h"
#include "ColorSelection.generated.h"

UENUM(BlueprintType)
enum class EColorSelection : uint8
{
	FirstLaserHit UMETA(DisplayName = "FirstLaserHit"),
	LastLaserHit UMETA(DisplayName = "LastLaserHit"),
	MergeLasers UMETA(DisplayName = "MergeLasers"),	
};
