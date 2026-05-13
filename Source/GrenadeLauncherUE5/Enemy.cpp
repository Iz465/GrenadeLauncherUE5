// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "LifeComponent.h"
#include "EnemyManager.h"
#include "EngineUtils.h" // header need for TActorIterator
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "GameFramework/Character.h"
#include "AIController.h"
#include "EnemyAIController.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	lifeComponent = CreateDefaultSubobject<ULifeComponent>(TEXT("LifeComponent"));


	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();



	for (TActorIterator<AEnemyManager> i(GetWorld()); i; ++i)
	{
		enemyManager = *i;
		break; 
	}
	
	if (enemyManager)
		enemyManager->AddEnemy(this);
	else
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, TEXT("Enemy not added to array"));

	
}


// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::Destroyed()
{
	if(!enemyManager) return;
	enemyManager->RemoveEnemy(this);
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Red, TEXT("Destruction of enemy"));
}

