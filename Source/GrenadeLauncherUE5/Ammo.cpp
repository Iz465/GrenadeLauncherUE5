// Fill out your copyright notice in the Description page of Project Settings.


#include "Ammo.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
AAmmo::AAmmo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

//	ammoCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	//RootComponent = ammoCollider;

	ammoMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ammo Mesh"));
	//RootComponent = ammoMesh;
//	ammoMesh->SetupAttachment(ammoCollider);
	projectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
}

// Called when the game starts or when spawned
void AAmmo::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAmmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

