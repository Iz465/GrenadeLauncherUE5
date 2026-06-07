// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Struct_Perks.generated.h"

class UTexture2D;

UENUM(BlueprintType)

enum class EPerkName : uint8
{
	damage,
	fireRate,
	reloadTime,
	ammoIncrease,
	freeze,
	poison,
	burn,
	freezeTime,
	poisonTime,
	burnTime,
	ricochet,
	aimbot,
	multiShot,
	instantShot

};

UENUM(BlueprintType)

enum class EPerkRarity : uint8
{
	common,
	uncommon,
	rare,
	legendary
};


USTRUCT(BlueprintType)
struct FPerks : public FTableRowBase
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float minValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float maxValue;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float valueCap;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float cooldown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag tag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPerkName perkEnum;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPerkRarity Rarity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bNumerical;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* icon;

};



