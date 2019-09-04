// Fill out your copyright notice in the Description page of Project Settings.
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    auto ControlledTank = GetControlledTank();
    if (!ControlledTank)
    {
        UE_LOG(LogTemp, Error, TEXT("PlayerController not possesing a tank"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController Possessing: %s"), *(ControlledTank->GetName()));
    }
    
}


//Tickvoid 
void ATankPlayerController::Tick(float DeltaTime)
{
    //Super
    Super::Tick( DeltaTime );
    AimTowardsCrosshair();

    //AimTowardsCrosshair();
}


ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}


void ATankPlayerController::AimTowardsCrosshair()
{
    if (!GetControlledTank()) { return; }

    FVector HitLocation; ///Out parameter
    if (GetSightRayHitLocation(HitLocation))   ///side effect: is going to line trace
    {

    //UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *HitLocation.ToString());
    ///Tell controlled tank to aim at this point 

    }
}
///Get world location if linetrace through crosshair, If it hits the landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
    //Find the crosshair position on the screen in pixel coodinates
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
    UE_LOG(LogTemp, Warning, TEXT("ScreenLocation: %s"), *ScreenLocation.ToString());
    //De-project the screen position of the crosshair to a world direction

    //Line-trace along that look direction to see what object we hit up to our max range
    return true;
}