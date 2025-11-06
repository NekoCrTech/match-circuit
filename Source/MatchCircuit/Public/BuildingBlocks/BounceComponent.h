// Created by Neko Creative Technologies

#pragma once

#include "CoreMinimal.h"
#include "LasersInterface.h"
#include "Components/ActorComponent.h"
#include "BounceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MATCHCIRCUIT_API UBounceComponent : public UActorComponent, public ILasersInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBounceComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
