// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapons.h"
#include "GrenadeWeapon.generated.h"

USTRUCT(BlueprintType)
struct FGrenadeWeaponInfo 
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWeaponInfo weaponInfo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float height = 171;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float distance = 300;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float explosionRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float knockBack;

};

UCLASS()
class GRENADELAUNCHERUE5_API AGrenadeWeapon : public AWeapons
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrenadeWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	void StartFire() override;
	void StopFire() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool charging = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector launchVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGrenadeWeaponInfo grenadeWeaponInfo;

	FGrenadeWeaponInfo originalWeaponInfo;



};
