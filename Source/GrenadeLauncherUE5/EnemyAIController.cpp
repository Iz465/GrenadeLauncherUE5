// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

// ai logic done in behavior tree
AEnemyAIController::AEnemyAIController() 
{
    PrimaryActorTick.bCanEverTick = true;
}

void AEnemyAIController::BeginPlay()
{
    Super::BeginPlay();
  
}

void AEnemyAIController::OnPossess(APawn* pawn)
{
    Super::OnPossess(pawn);

    if (behaviorTreeAsset)
    {
        UseBlackboard(behaviorTreeAsset->BlackboardAsset, BlackboardComponent);
        RunBehaviorTree(behaviorTreeAsset);
    }

    enemy = Cast<AEnemy>(GetPawn());

    if (BlackboardComponent && enemy)   // set up blackboard values
    {
     
        BlackboardComponent->SetValueAsFloat("AttackDistance", enemy->attackDistance);
        BlackboardComponent->SetValueAsFloat("PlayerDistance", 1000);
        BlackboardComponent->SetValueAsEnum("EEnemyState", 1);
        BlackboardComponent->SetValueAsBool("CanAttack", false);
        GetWorldTimerManager().SetTimerForNextTick(this, &AEnemyAIController::SetPlayerTarget);
    }

    else
        GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, TEXT("Blackboard failed!"));
  

}

void AEnemyAIController::SetPlayerTarget()
{
    APawn* playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    
        BlackboardComponent->SetValueAsObject("PlayerTarget", playerPawn);
}




void AEnemyAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    /*
    APawn* playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);


    if (!playerPawn) return;
    if (!enemy) return;
    
    
    float playerDistance = FVector::Dist(playerPawn->GetActorLocation(), GetPawn()->GetActorLocation());
    MoveToActor(playerPawn, 15.0f);
    GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, FString::SanitizeFloat(playerDistance));
    if (playerDistance < enemy->attackDistance)
        GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, TEXT("Attack!"));
   */
    
    
}