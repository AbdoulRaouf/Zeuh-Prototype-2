// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"

#include "EngineUtils.h"
#include "ZeuhShooterAIController.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);
	UE_LOG(LogTemp,Warning,TEXT("A Pawn Was Killed !"));
	APlayerController* PlayerController= Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController!=nullptr)
	{

		EndGame(false);
		
		//PlayerController->GameHasEnded(nullptr,false);
	}
	//chercher tous les IA du niveau
	for (AZeuhShooterAIController* Controller: TActorRange<AZeuhShooterAIController>(GetWorld()))
	{
		if(!Controller->IsDead())
		{
			return;
		}
	}
	EndGame(true);
	
}

void AKillEmAllGameMode::EndGame(bool bIsplayerWinner)
{
	for(AController* Controller:TActorRange<AController>(GetWorld()))
	{
		bool bIsWinner=Controller->IsPlayerController()==bIsplayerWinner;

		Controller->GameHasEnded(Controller->GetPawn(),bIsWinner);
		/*if (bIsplayerWinner)
		{
			Controller->GameHasEnded(nullptr,bIsPlayerController);
		}
		else
		{
			Controller->GameHasEnded(nullptr,!bIsplayerWinner);
		}*/
	}
	
}
