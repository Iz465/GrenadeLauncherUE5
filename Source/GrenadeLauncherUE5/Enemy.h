// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Enemy.generated.h"

class ULifeComponent;
class AEnemyManager;


UCLASS()
class GRENADELAUNCHERUE5_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ULifeComponent* lifeComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AEnemyManager* enemyManager = nullptr;

	virtual void Destroyed() override;
	

};
