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

void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick( DeltaTime );
    AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if (!GetControlledTank()) { return; }

    FVector HitLocation; //Out parameter
    if (GetSightRayHitLocation(HitLocation)) //side effect: is going to line trace
    {
        GetControlledTank()->AimAt(HitLocation);
    }
}

// Get world location if linetrace through crosshair, True if hits the landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
    // Find the crosshair position on screen in pixel coodinates
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

    //De-project the screen position of the crosshair to a world direction
    FVector LookDirection;
    if (GetLookDirection(ScreenLocation, LookDirection))
    {
        //Line-trace along that LookDirection, to see what we hit (up to our max range)
        GetLookVectorHitLocation(LookDirection, HitLocation);
    }

    return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
        FHitResult HitResult;
        auto StartLocation = PlayerCameraManager->GetCameraLocation();
        auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
        if (GetWorld()->LineTraceSingleByChannel(
                        HitResult,
                        StartLocation,
                        EndLocation,
                        ECollisionChannel::ECC_Visibility)
                )
        {
                HitLocation = HitResult.Location;
                return true;
        }
        HitLocation = FVector(0);
        return false; //Trace Failed
}

 bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    FVector CameraWorldLocation;
    return  DeprojectScreenPositionToWorld(
            ScreenLocation.X, 
            ScreenLocation.Y,
            CameraWorldLocation,
            LookDirection
    );
}