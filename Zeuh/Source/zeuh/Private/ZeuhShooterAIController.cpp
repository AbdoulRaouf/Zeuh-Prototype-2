// Fill out your copyright notice in the Description page of Project Settings.


#include "ZeuhShooterAIController.h"

#include "ZeuhShooterCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"


void AZeuhShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	if(AIBehaviors!=nullptr)
	{
		RunBehaviorTree(AIBehaviors);

		APawn* PlayerPawn= UGameplayStatics::GetPlayerPawn(GetWorld(),0);
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"),PlayerPawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsVector(TEXT("StarLocation"),GetPawn()->GetActorLocation());
	}
	
}

void AZeuhShooterAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	
	/*APawn* PlayerPawn= UGameplayStatics::GetPlayerPawn(GetWorld(),0);

	
	if(LineOfSightTo(PlayerPawn))
	{
		//definir la localisation du jouer
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());

		//definir la derniere position connue
		GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
		
		///l'actor sur lequel on se focalise
	SetFocus(PlayerPawn);
		//ou aller et à quel mettre s'arreter
		MoveToActor((PlayerPawn),acceptanceRadius);

	}
	else
	{
		GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
	}
*/
	
}

bool AZeuhShooterAIController::IsDead() const
{
	AZeuhShooterCharacter* ControlledCharacter= Cast<AZeuhShooterCharacter>(GetPawn());
	if (ControlledCharacter!=nullptr)
	{
		return ControlledCharacter->isDead();
	}
	return true;
}
