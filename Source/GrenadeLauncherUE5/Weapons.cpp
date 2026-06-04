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
		weaponInfo.reloadTime = gameInstance->savedWeaponInfo.reloadTime;
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

	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Emerald, TEXT("Weapon Fired"));

	if (!player) return;
	
	player->GetMesh1P()->GetAnimInstance()->Montage_Play(weaponAnimationMontage, 1);
}

void AWeapons::StopFire()
{

	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Emerald, TEXT("Firing Cancelled"));
}



void AWeapons::Reload()
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Emerald, TEXT("Reloading The Weapon"));
	hasReloaded = true;
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



