// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LifeComponent.generated.h"

// this script is for all actors that take damage e.g player, enemies.
USTRUCT(BlueprintType)
struct FLifeStruct
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float health = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float damage = 10;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRENADELAUNCHERUE5_API ULifeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULifeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable)
	void TakeDamage(float damage);
	UFUNCTION(BlueprintCallable)
	void Death();
	UFUNCTION(BlueprintCallable)
	void Heal(float amount);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLifeStruct lifeStruct;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Life Stats")
	FLifeStruct originalLifeStruct;
	
};
