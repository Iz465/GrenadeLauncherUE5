// Fill out your copyright notice in the Description page of Project Settings.


#include "GrenadeWeapon.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Weapons.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"
#include "Ammo.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AGrenadeWeapon::AGrenadeWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	

} 

// Called when the game starts or when spawned
void AGrenadeWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGrenadeWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

void AGrenadeWeapon::StartFire()
{

	charging = true;
}


void AGrenadeWeapon::StopFire()
{
	AAmmo* ammo = GetWorld()->SpawnActor<AAmmo>(AmmoType, aimArea->GetComponentLocation(), aimArea->GetComponentRotation());
	ammo->projectileMovement->Velocity = launchVelocity;

	float launchLength = launchVelocity.Length();
	float min = ammo->projectileMovement->InitialSpeed = launchLength;
	float max = ammo->projectileMovement->MaxSpeed = launchLength;

	
	charging = false;
	hasFired = true;
	height = 0;
	distance = 0;
}
