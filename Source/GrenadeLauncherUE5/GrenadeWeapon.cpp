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
#include "Animation/AnimMontage.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGrenadeWeapon::AGrenadeWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	weaponInfo.reloadTime = 1;
	weaponInfo.ammo = 5;

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
	if (hasFiredRate) return;

	if (!hasReloaded) return;

	if (!player) return;

//	AGrenadeLauncherUE5Character* grenadePlayer = Cast<AGrenadeLauncherUE5Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
//	if (!player) return;
	
//	UAnimInstance* AnimInstance = grenadePlayer->GetMesh1P()->GetAnimInstance();
//	if (!AnimInstance) return;
//	AnimInstance->Montage_Play(weaponAnimationMontage);
	//AnimInstance->Montage_JumpToSection(FName("Shoot"), weaponAnimationMontage);


	FireAnimation();

	
	hasFiredRate = true;
	GetWorldTimerManager().SetTimer(reloadTimerHandle, this, &AGrenadeWeapon::ResetFireRate, weaponInfo.fireRate, false);
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, TEXT("Fired"));

	
	
	
	AAmmo* ammo = GetWorld()->SpawnActor<AAmmo>(AmmoType, aimArea->GetComponentLocation(), player->GetControlRotation());
	ammo->projectileMovement->Velocity = player->GetControlRotation().Vector() * 2000.f;

	weaponInfo.ammo -= 1;
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, FString::SanitizeFloat(weaponInfo.ammo));
	if ((weaponInfo.ammo) == 0)		
	{
		hasReloaded = false;
	
		//GetWorldTimerManager().SetTimer(reloadTimerHandle, this, &AGrenadeWeapon::Reload, 3, false);
		ReloadAnimation();
	//	AnimInstance->Montage_Play(weaponAnimationMontage);
	//	AnimInstance->Montage_JumpToSection(FName("Reload"), weaponAnimationMontage);
		
	}

	
		

	
}

// 	StartShake();
void AGrenadeWeapon::StopFire()
{
	
}

void AGrenadeWeapon::Reload()
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, TEXT("Reloading grenade launcher"));
	hasReloaded = true;
	hasFiredRate = false;
}
