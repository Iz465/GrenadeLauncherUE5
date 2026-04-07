// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"
#include "Enemy.h"

// Sets default values
AEnemyManager::AEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyManager::AddEnemy(AEnemy* enemy)
{
	aliveEnemies.Add(enemy);
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, FString::Printf(TEXT("Enemy Added. Enemy Amount: %d"), aliveEnemies.Num()));
}

void AEnemyManager::RemoveEnemy(AEnemy* enemy)
{
	aliveEnemies.Remove(enemy);
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, FString::Printf(TEXT("Enemy Removed. Enemy Amount: %d"), aliveEnemies.Num()));
}
