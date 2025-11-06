// Created by Neko Creative Technologies

#pragma once

#include "CoreMinimal.h"
#include "LasersInterface.h"
#include "Components/SceneComponent.h"
#include "EmitterComponent.generated.h"


class UHandlerComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MATCHCIRCUIT_API UEmitterComponent : public USceneComponent, public ILasersInterface
{
	GENERATED_BODY()

public:	
	UEmitterComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FLinearColor OverrideColor = FLinearColor::Black;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bUseOverrideColor = false;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


private:
	UPROPERTY()
	UHandlerComponent* OwningHandler = nullptr;

	UPROPERTY()
	ALaser* AttachedLaser = nullptr;

	UPROPERTY()
	FLinearColor CurrentColor = FLinearColor::Black;

	UPROPERTY()
	float MaxRange = 3000.0f;
};
