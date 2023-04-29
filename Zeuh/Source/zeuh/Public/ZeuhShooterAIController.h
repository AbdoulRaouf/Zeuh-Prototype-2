// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ZeuhShooterAIController.generated.h"

/**
 * 
 */
UCLASS()
class ZEUH_API AZeuhShooterAIController : public AAIController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaSeconds) override;
	bool IsDead() const;

	//espace entre l'ai et le joueur
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehaviors;
	//float acceptanceRadius=150;
};
