// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponsComponent.generated.h"

class AWeapons;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRENADELAUNCHERUE5_API UWeaponsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponsComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	AWeapons* weapon;

	void StartFire();
	void StopFire();
	void Reload();
	void Aim();

	
	
};
