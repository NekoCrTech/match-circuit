// Created by Neko Creative Technologies

#pragma once

#include "CoreMinimal.h"
#include "LasersInterface.h"
#include "Components/ActorComponent.h"
#include "Enumerators/ColorSelection.h"
#include "HandlerComponent.generated.h"

DECLARE_DELEGATE(FActivateHandler);
DECLARE_DELEGATE(FDeactivateHandler);
DECLARE_DELEGATE_OneParam(FUpdateHandler, float);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MATCHCIRCUIT_API UHandlerComponent : public UActorComponent, public ILasersInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHandlerComponent();

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Conditions")
	bool bInvertSystem = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Conditions")
	bool bIsBlocking = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Conditions")
	bool bIsLocked = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Colors")
	EColorSelection UsedColor = EColorSelection::LastLaserHit;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Colors")
	bool bIsAdjustingColor = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Colors")
	bool bUseColorValue = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Colors")
	bool bCanMergeColor = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Lasers")
	TArray<FLinearColor> LaserRules;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Lasers")
	TArray<FLinearColor> LaserFilters;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Timer")
	float Duration = 0.f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Timer")
	float Substep = 0.016667f;

	FActivateHandler OnActivate;
	FDeactivateHandler OnDeactivate;
	FUpdateHandler OnUpdate;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	UPROPERTY()
	FLinearColor MergedColor = FLinearColor::Black;

	UPROPERTY()
	FLinearColor PassByColor = FLinearColor::Black;

	UPROPERTY()
	TArray<UActorComponent*> LinkedComponents;

	UPROPERTY()
	TArray<ALaser*> LasersInQueue;
	
	UPROPERTY()
	TArray<ALaser*> FilteredLasers;
	
	UPROPERTY()
	float TimerAlpha = 0.f;
	
	UPROPERTY()
	bool bReverseTimer = false;
	
	FTimerHandle* TimerHandle;

	UFUNCTION()
	bool UseTimer() const { return Duration!=0; }

	UFUNCTION()
	static FLinearColor SetAlphaToOne(FLinearColor InColor);

	UFUNCTION()
	FLinearColor GetVisibleColor();

	UFUNCTION()
	void RecalculateColors(ALaser* InputPin);
	
	UFUNCTION()
	void ComponentColorChange(ALaser* Modified);
};
