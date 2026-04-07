// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapons.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class AAmmo;
class UCameraShakeBase;
class AGrenadeLauncherUE5Character;

USTRUCT(BlueprintType)
struct FWeaponInfo 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float speed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ammo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float reloadTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector location = FVector(-30.06, 8.3814, -6.020); // red, green, blue.  x , y , z
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator rotation = FRotator(-60.29, -46.04, 5.5241); // green, blue, red, y, z, x


};


UCLASS()
class GRENADELAUNCHERUE5_API AWeapons : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapons();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void StartFire();
	virtual void StopFire();
	virtual void Reload();
	virtual void Aim();
	UFUNCTION(BlueprintImplementableEvent)
	void StartShake();



	

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* aimArea;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* weaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool hasFired = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool hasReloaded = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ammo")
	TSubclassOf<AAmmo> AmmoType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CameraShake")
	TSubclassOf<UCameraShakeBase> cameraShake;
	FTimerHandle reloadTimerHandle;
	AGrenadeLauncherUE5Character* player;
};
