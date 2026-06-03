// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Struct_Weapons.h"
#include "FPS_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GRENADELAUNCHERUE5_API UFPS_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	FSavedWeaponInfo savedWeaponInfo;

protected:

	
};
