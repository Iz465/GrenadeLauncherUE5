// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapons.h"
#include "GrenadeWeapon.generated.h"



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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float height;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float distance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float explosionRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float knockBack;

	void StartFire() override;
	void StopFire() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool charging = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector launchVelocity;



};
