// Created by Neko Creative Technologies

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LasersInterface.generated.h"

class ALaser;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class ULasersInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MATCHCIRCUIT_API ILasersInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void LaserStartHitting(ALaser* Input, FHitResult HitInfo);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void LaserStopHitting(ALaser* Input);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void LaserUpdateHitting(ALaser* Input, FHitResult HitInfo);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void IntermediateChange(ALaser* Changed);
};
