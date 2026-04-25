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
#include "EPlayerState.h"


// Sets default values
AGrenadeWeapon::AGrenadeWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	grenadeWeaponInfo.weaponInfo.reloadTime = 1;
	

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

	if (!player) return;
	

	
	AAmmo* ammo = GetWorld()->SpawnActor<AAmmo>(AmmoType, aimArea->GetComponentLocation(), player->GetControlRotation());
	ammo->projectileMovement->Velocity = player->GetControlRotation().Vector() * 2000.f;
	hasReloaded = false;
	GetWorldTimerManager().SetTimer(reloadTimerHandle, this, &AGrenadeWeapon::Reload, 3, false);
	player->ePlayerState = EPlayerState::Shoot;
}

// 	StartShake();
void AGrenadeWeapon::StopFire()
{
	
}
