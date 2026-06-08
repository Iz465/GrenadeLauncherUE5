// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h" 
#include "Camera/CameraShakeBase.h"
#include "Kismet/GameplayStatics.h"
#include "GrenadeLauncherUE5Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "FPS_GameInstance.h"
#include "Animation/AnimMontage.h"
#include "Camera/CameraComponent.h"   
#include "NiagaraFunctionLibrary.h"

FWeaponInfo AWeapons::originalWeaponInfo;

// Sets default values
AWeapons::AWeapons()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	SetActorTickEnabled(true);

	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	weaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Grenade Launcher Mesh"));
	weaponMesh->SetupAttachment(RootComponent);



	aimArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Aim Area"));
	aimArea->SetupAttachment(weaponMesh);

	weaponFlashArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Weapon Flash Area"));
	weaponFlashArea->SetupAttachment(weaponMesh);


	

}

// Called when the game starts or when spawned
void AWeapons::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	SetActorTickEnabled(true);
	ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	player = Cast<AGrenadeLauncherUE5Character>(playerCharacter);

	gameInstance = Cast<UFPS_GameInstance>(UGameplayStatics::GetGameInstance(this));
	if (gameInstance)
	{
		weaponInfo.damage = gameInstance->savedWeaponInfo.damage;
		weaponInfo.ammo = gameInstance->savedWeaponInfo.ammo;
		weaponInfo.reloadTime = gameInstance->savedWeaponInfo.reloadSpeedRate;
		weaponInfo.fireRate = gameInstance->savedWeaponInfo.fireRate;

		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, FString::SanitizeFloat(gameInstance->savedWeaponInfo.damage));
	}

	else
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, TEXT("Game Instance not found"));

}

// Called every frame
void AWeapons::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void AWeapons::StartFire()
{

	if (hasFiredRate) return;

	if (!hasReloaded) return;

	if (!player) return;

	if (weaponAnimationMontage)
		player->GetMesh1P()->GetAnimInstance()->Montage_Play(weaponAnimationMontage, 1);
	if (weaponFlash)
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), weaponFlash, weaponFlashArea->GetComponentLocation());


	hasFiredRate = true;
	GetWorldTimerManager().SetTimer(reloadTimerHandle, this, &AWeapons::ResetFireRate, weaponInfo.fireRate, false);

	if (AmmoType)
	{
		AAmmo* ammo = GetWorld()->SpawnActor<AAmmo>(AmmoType, aimArea->GetComponentLocation(), player->GetControlRotation());
		ammo->projectileMovement->Velocity = player->GetControlRotation().Vector() * 2000.f;
		weaponInfo.ammo -= 1;

		ammo->weapon = this;
	}
	




	StartShake();

	if ((weaponInfo.ammo) == 0)
	{
		hasReloaded = false;

		//GetWorldTimerManager().SetTimer(reloadTimerHandle, this, &AGrenadeWeapon::Reload, 3, false);
		ReloadAnimation();


	}

}

void AWeapons::StopFire()
{

	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Emerald, TEXT("Firing Cancelled"));
}



void AWeapons::Reload()
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Emerald, TEXT("Reloading The Weapon"));
	hasReloaded = true;
	hasFiredRate = false;
}

void AWeapons::ResetFireRate()
{
	hasFiredRate = false;
}

void AWeapons::Aim()
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Emerald, TEXT("Aiming The Weapon"));
}

void AWeapons::StartShake()
{
	FVector shakeLocation = player->GetFirstPersonCameraComponent()->GetComponentLocation();
	UGameplayStatics::PlayWorldCameraShake(GetWorld(), cameraShake, shakeLocation, 50, 50, 1);
} 

void AWeapons::ActivatePerk(FPerks fperks)
{
	if (fperks.bNumerical)
		ChangePerkValue(fperks);
	else
		GEngine->AddOnScreenDebugMessage(1, 5, FColor::Magenta, TEXT("Specific Perk chosen..."));
}

void AWeapons::ChangePerkValue(FPerks fperks)
{
	

	switch (fperks.perkEnum)
	{
	case EPerkName::damage: gameInstance->savedWeaponInfo.damage += (gameInstance->savedWeaponInfo.damage / 5);
		gameInstance->savedWeaponInfo.damage = FMath::Clamp(gameInstance->savedWeaponInfo.damage, .1f, originalWeaponInfo.damage * fperks.valueCap);  
		UE_LOG(LogTemp, Warning, TEXT("Original damage value: %f Current damage value: %f Max value: %f"), originalWeaponInfo.damage, gameInstance->savedWeaponInfo.damage, originalWeaponInfo.damage * fperks.valueCap); break;

	case EPerkName::reloadTime: gameInstance->savedWeaponInfo.reloadSpeedRate += fperks.maxValue;
		gameInstance->savedWeaponInfo.reloadSpeedRate = FMath::Clamp(gameInstance->savedWeaponInfo.reloadSpeedRate, 0, originalWeaponInfo.reloadTime * fperks.valueCap);
		UE_LOG(LogTemp, Warning, TEXT("Original reload value: %f Current reload value: %f Max value: %f"), originalWeaponInfo.reloadTime, gameInstance->savedWeaponInfo.reloadSpeedRate, originalWeaponInfo.reloadTime * 4); break;

	case EPerkName::ammoIncrease: gameInstance->savedWeaponInfo.ammo += (gameInstance->savedWeaponInfo.ammo / 5);
		gameInstance->savedWeaponInfo.ammo = FMath::Clamp(gameInstance->savedWeaponInfo.ammo, .1f, originalWeaponInfo.ammo * fperks.valueCap);
		UE_LOG(LogTemp, Warning, TEXT("Original ammo value: %d Current ammo value: %d Max value: %f"), originalWeaponInfo.ammo, gameInstance->savedWeaponInfo.ammo, originalWeaponInfo.ammo * fperks.valueCap); break;

	case EPerkName::fireRate: gameInstance->savedWeaponInfo.fireRate -= (gameInstance->savedWeaponInfo.fireRate / 5); 
		gameInstance->savedWeaponInfo.fireRate = FMath::Clamp(gameInstance->savedWeaponInfo.fireRate, originalWeaponInfo.fireRate / fperks.valueCap, originalWeaponInfo.fireRate);
		UE_LOG(LogTemp, Warning, TEXT("Original fire rate value: %f Current fire rate value: %f Max value: %f"), originalWeaponInfo.fireRate, gameInstance->savedWeaponInfo.fireRate, originalWeaponInfo.fireRate / fperks.valueCap); break;

	case EPerkName::freezeTime: break;
	case EPerkName::poisonTime: break;
	case EPerkName::burnTime: break;
		
	}




	
	
}

