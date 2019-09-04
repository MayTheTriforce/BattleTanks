// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const;
	virtual void BeginPlay() override;
	virtual void Tick( float DeltaTime ) override;

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float CrosshairYLocation = 0.33333;

	///Starts the tank moving the barrel so that a shot would shoot where the crosshead intersects the world
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
};
