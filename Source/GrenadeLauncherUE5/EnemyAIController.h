// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */

class AEnemy;
class UBehaviourTree;
class UBlackboardComponent;


UCLASS()
class GRENADELAUNCHERUE5_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public: 
	AEnemyAIController();
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* pawn) override;

	AEnemy* enemy;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* behaviorTreeAsset;

	UPROPERTY()
	UBlackboardComponent* BlackboardComponent;

	void SetPlayerTarget();

	

};
