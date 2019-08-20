// Fill out your copyright notice in the Description page of Project Settings.
#include "TankPlayerController.h"


//Tickvoid 
void ATankPlayerController::Tick(float DeltaTime)
{
    //Super
    Super::Tick( DeltaTime );
    UE_LOG(LogTemp, Warning, TEXT("Tick Method is working"));  

    //AimTowardsCrosshair();
}

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


ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}
