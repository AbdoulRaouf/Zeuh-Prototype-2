// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ZeuhShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ZEUH_API AZeuhShooterPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:
	virtual void GameHasEnded(class AActor* EndGameFocus=nullptr, bool bIsWinner=false) override;
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LoseScreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> WinScreenclass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUDclass;
	
	UPROPERTY(EditAnywhere)
	float RestartDelay=5;

	FTimerHandle RestartTimer;
	UPROPERTY()
	UUserWidget* HUD;
	
};
