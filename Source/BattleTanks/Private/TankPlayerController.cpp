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
    UE_LOG(LogTemp, Warning, TEXT("Tick Method is working"));  

    //AimTowardsCrosshair();
}


ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}


void ATankPlayerController::AimTowardsCrosshair()
{
    if (!GetControlledTank()) { return; }
    ///Get world location if linetrace through crosshair
    ///If it hits the landscape
    ///Tell controlled tank to aim at this point 
}