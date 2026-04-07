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
#include "Camera/CameraShakeBase.h"
#include "GrenadeLauncherUE5Character.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AGrenadeWeapon::AGrenadeWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	grenadeWeaponInfo.weaponInfo.reloadTime = 3;
	

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
	if (!hasReloaded) return;
	if (player)
		player->GetCharacterMovement()->MaxWalkSpeed = 0;

	charging = true;
}


void AGrenadeWeapon::StopFire()
{
	if (!charging) return;
	if (grenadeWeaponInfo.weaponInfo.ammo <= 0) return;
	if (!hasReloaded) return;

	AAmmo* ammo = GetWorld()->SpawnActor<AAmmo>(AmmoType, aimArea->GetComponentLocation(), aimArea->GetComponentRotation());
	ammo->projectileMovement->Velocity = launchVelocity;

	
	

	float launchLength = launchVelocity.Length();
	float min = ammo->projectileMovement->InitialSpeed = launchLength;
	float max = ammo->projectileMovement->MaxSpeed = launchLength;
	
	grenadeWeaponInfo.weaponInfo.ammo -= 1;
	ammo->ammoLeft = grenadeWeaponInfo.weaponInfo.ammo;
	

	StartShake();
	
	charging = false;
	hasFired = true;
	grenadeWeaponInfo.distance = originalWeaponInfo.distance;
	grenadeWeaponInfo.height = originalWeaponInfo.height;


	hasReloaded = false;

	GetWorldTimerManager().SetTimer(reloadTimerHandle, this, &AGrenadeWeapon::Reload, 3, false);


	if (player)
		player->GetCharacterMovement()->MaxWalkSpeed = 400;

}
