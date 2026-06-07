// Fill out your copyright notice in the Description page of Project Settings.


#include "Ammo.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "LifeInterface.h"


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

	/*
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, TEXT("Rotating Grenade"));
	FRotator rotation = projectileMovement->Velocity.Rotation();
	SetActorRotation(rotation);
	*/

}

void AAmmo::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved,
	FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{

	GEngine->AddOnScreenDebugMessage(1, 5, FColor::Purple, TEXT("Ammo hit something"));
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), hitParticle, HitLocation);

	if (Other->Implements<ULifeInterface>() && weapon)
		ILifeInterface::Execute_TakeDamage(Other, weapon->weaponInfo.damage, HitLocation);

	
	Destroy();
	
}


