// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"

#include "AIController.h"
#include "ZeuhShooterCharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName=TEXT("Shoot Node");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	if (OwnerComp.GetOwner()==nullptr)
	{
		return EBTNodeResult::Failed;
	}
	AZeuhShooterCharacter* Character=Cast<AZeuhShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	if (Character==nullptr)
	{
		return EBTNodeResult::Failed;
	}

	Character->Shoot();
	
	return EBTNodeResult::Succeeded;
}

