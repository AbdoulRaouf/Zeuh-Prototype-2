// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//creation du component parent
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	//specification de parent
	SetRootComponent(Root);
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

}

void AGun::PullTrigger()
{
	//Verifier si ça tire !
	//UE_LOG(LogTemp,Warning,TEXT("ShOOt !"));
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound,Mesh,TEXT("MuzzleFlashSocket"));

	FHitResult Hit;
	FVector ShootDirection;
	
	bool bSucces=GunTrace(Hit,ShootDirection);
	if(bSucces)
	{
		//point à Dessiner à la fin d'un line trace
		//DrawDebugPoint(GetWorld(),Hit.Location,20,FColor::Red, true);

		
		//effect à appliquer sur la surface
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ImpactEffect,Hit.Location,ShootDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(),ImpactSound,Hit.Location);
		
		AActor* HitActor= Hit.GetActor();
		if (HitActor!=nullptr)
		{
			//Faire des Dommage
			FPointDamageEvent DamageEvent(Damage,Hit,ShootDirection,nullptr);
			AController* OwnerController=GetOwnerController();
			HitActor->TakeDamage(Damage,DamageEvent,OwnerController,this);
		}
	}

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AGun::GunTrace(FHitResult& Hit, FVector& ShootDirection)
{
	AController* OwnerController=GetOwnerController();
	//si !null
	if (OwnerController == nullptr) return false;

	//Variable pour storer le Transform du Owner - le Scale
	FVector Location; //le star point du line trace
	FRotator Rotation;
	
	//Avoir le point de vue du owner
	OwnerController->GetPlayerViewPoint(Location, Rotation);

	//la direction de là ou vient le line trace afin de pouvoir jouer l'animation dans le bon sens
	ShootDirection= -Rotation.Vector();


	//Le point d'impacte d'un bullet
	FVector End=Location + Rotation.Vector()* MaxRange;

	/*Dessiner une Camera à chaque clique Selon le point de vue du Owner
	DrawDebugCamera(GetWorld(), Location, Rotation, 90, 2, FColor::Red, true);*/

	//correction de bug se tuer soit meme
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this); //ignorer le collisionneur du gun lui meme
	Params.AddIgnoredActor(GetOwner());//ignorer le collisionneur du detenteur du gun aussi
	

	//verifier si l'on a toucher une de nos surface specifier
	return GetWorld()->LineTraceSingleByChannel(Hit,Location,End, ECollisionChannel::ECC_GameTraceChannel1,Params);
}

AController* AGun::GetOwnerController() const
{
	//Recuper le character cible--ZeuhShooterCharacer hein !!
	APawn* OwnerPawn = Cast<APawn>(GetOwner());

	//verifier que c'est pas null
	if (OwnerPawn == nullptr) return nullptr;

	return OwnerPawn->GetController();
}

