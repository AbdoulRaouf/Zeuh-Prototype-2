// Fill out your copyright notice in the Description page of Project Settings.


#include "ZeuhShooterCharacter.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "zeuh/zeuhGameModeBase.h"

// Sets default values
AZeuhShooterCharacter::AZeuhShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AZeuhShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health=MaxHealth;

	Gun=GetWorld()->SpawnActor<AGun>(Gunclass);
	GetMesh()->HideBoneByName(TEXT("Weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform,TEXT("WeaponSocket"));
	Gun->SetOwner(this);
	
}

bool AZeuhShooterCharacter::isDead() const
{
	return Health<=0;
}

float AZeuhShooterCharacter::GetHealthPercent() const
{
	return Health/MaxHealth;
}

// Called every frame
void AZeuhShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AZeuhShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	/*les déplacement*/
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AZeuhShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AZeuhShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AZeuhShooterCharacter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AZeuhShooterCharacter::LookRightRate);
	
	/*Action*/

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AZeuhShooterCharacter::Shoot);

}

float AZeuhShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent,AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApplied=FMath::Min(Health,DamageToApplied);
	Health-=DamageToApplied;
	UE_LOG(LogTemp,Warning,TEXT("Health left %f"),Health);
	if (isDead())
	{
		AzeuhGameModeBase* GameMode=GetWorld()->GetAuthGameMode<AzeuhGameModeBase>();
		if (GameMode!=nullptr)
		{
			GameMode->PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
	}
	return DamageToApplied;
}


void AZeuhShooterCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AZeuhShooterCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AZeuhShooterCharacter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue* RotationRate * GetWorld()->GetDeltaSeconds());
}

void AZeuhShooterCharacter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AZeuhShooterCharacter::Shoot()
{
	Gun->PullTrigger();
}

/*void AZeuhShooterCharacter::LookRight(float AxisValue)
{
}*/

/*
void AZeuhShooterCharacter::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}*/

