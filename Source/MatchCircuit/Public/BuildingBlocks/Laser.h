// Created by Neko Creative Technologies

#pragma once

#include "CoreMinimal.h"
#include "LasersInterface.h"
#include "GameFramework/Actor.h"
#include "Laser.generated.h"

class UHandlerComponent;

UCLASS()
class MATCHCIRCUIT_API ALaser : public AActor, public ILasersInterface
{
	GENERATED_BODY()
	
public:
	
	ALaser();
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Color")
	FLinearColor ColorOverride = FLinearColor::Red;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float Range = 3000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	TArray<ALaser*> PreviousLasers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	UHandlerComponent* OwningHandler = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "References")
	TArray<AActor*> ActorsToIgnore;

	UFUNCTION(BlueprintCallable)
	void ChangeLaserColor(FLinearColor Value);

	UFUNCTION(BlueprintCallable)
	void UpdateLength(float InputPin);

	UFUNCTION(BlueprintCallable)
	void HandleHitActors(FHitResult InputPin);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsNotInPath(UHandlerComponent* InputHandler);

	UFUNCTION(BlueprintCallable)
	virtual void LaserStopHitting_Implementation(ALaser* Input) override;

	UFUNCTION(BlueprintCallable)
	void InitializeLaser(FLinearColor InColorOverride, TArray<ALaser*> InPreviousLasers, UHandlerComponent* InOwningHandler, TArray<AActor*> InActorsToIgnore);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMesh> LaserMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UMaterialInstance> SourceMaterial = nullptr;

	UPROPERTY()
	UMaterialInstanceDynamic* LaserMaterial = nullptr;

	UPROPERTY()
	float PreviousLength = 0.0f;

	UPROPERTY()
	TMap<UHandlerComponent*, FHitResult> HittingHandlers;

	UPROPERTY()
	TSet<UHandlerComponent*> PreviouslyHitHandlers;

	UPROPERTY()
	TSet<UHandlerComponent*> CurrentHitHandlers;
};
