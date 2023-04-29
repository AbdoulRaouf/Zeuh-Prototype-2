// Fill out your copyright notice in the Description page of Project Settings.


#include "ZeuhShooterPlayerController.h"

#include "Blueprint/UserWidget.h"

void AZeuhShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	HUD=CreateWidget(this,HUDclass);
	if (HUD!=nullptr)
	{
		HUD->AddToViewport();
	}
}

void AZeuhShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);
	//UE_LOG(LogTemp,Warning,TEXT("Fini !"));

	HUD->RemoveFromViewport();

	if (bIsWinner)
	{
		UUserWidget* winScreen=CreateWidget(this,WinScreenclass);
		if (winScreen!=nullptr)
		{
			winScreen->AddToViewport();
		}
	}
	else
	{
		UUserWidget* LoseScreen=CreateWidget(this,LoseScreenClass);
		if (LoseScreen!=nullptr)
		{
			LoseScreen->AddToViewport();
		}
		
	}
	
	GetWorldTimerManager().SetTimer(RestartTimer,this,&APlayerController::RestartLevel,RestartDelay);
}
