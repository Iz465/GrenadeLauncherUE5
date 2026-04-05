// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h" 

// Sets default values
AWeapons::AWeapons()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	weaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Grenade Launcher Mesh"));
	weaponMesh->SetupAttachment(RootComponent);



	aimArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Aim Area"));
	aimArea->SetupAttachment(weaponMesh);

}

// Called when the game starts or when spawned
void AWeapons::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapons::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapons::StartFire()
{

	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Emerald, TEXT("Weapon Fired"));
}

void AWeapons::StopFire()
{

	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Emerald, TEXT("Firing Cancelled"));
}

void AWeapons::Reload()
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Emerald, TEXT("Reloading The Weapon"));
}


void AWeapons::Aim()
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Emerald, TEXT("Aiming The Weapon"));
}



