// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Flashlight.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFlashLightToggled, bool, IsOn);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFlashLightDrained, float, CurrentBatteryLife);

UCLASS()
class CODENAME_LOST_API AFlashlight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlashlight();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Flashlight")
	UStaticMeshComponent* Mesh;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Flashlight")
	class USpotLightComponent* Light;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Flashlight")
	float MaxBatteryLife;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Flashlight")
	float CurrentBatteryLife;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Flashlight")
	float DrainBatteryLifeTickTime;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Flashlight")
	float BatteryDrainPerTick;

	void TurnLightOn();

	void TurnLightOff();

	void ToggleLight();

	UPROPERTY(BlueprintReadOnly, Category = "Flashlight")
	bool bIsLightOn;

	UPROPERTY(BlueprintAssignable, Category = "Flashlight")
	FFlashLightToggled LightToggled;

	UPROPERTY(BlueprintAssignable, Category = "Flashlight")
	FFlashLightDrained LightDrained;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void BatteryDrain();

	bool CanTurnOn();
};
