// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons.h"
#include "Struct_Weapons.generated.h"



class UTexture2D;
class UAnimSequence;

USTRUCT(BlueprintType)
struct FSavedWeaponInfo : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int ammo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float reloadSpeedRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float fireRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* image;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AWeapons> weapon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector location;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator rotation;
};