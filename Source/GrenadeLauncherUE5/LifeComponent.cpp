// Fill out your copyright notice in the Description page of Project Settings.


#include "LifeComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
ULifeComponent::ULifeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULifeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULifeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULifeComponent::TakeDamage(float damage)
{
	
	lifeStruct.health -= damage;
	if (lifeStruct.health <= 0)
		Death();
	
		
	
		
}

void ULifeComponent::Death()
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, TEXT("DEATH HAS COME"));
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, GetOwner()->GetName());
	GetOwner()->Destroy();
}

void ULifeComponent::Heal(float amount)
{
	lifeStruct.health += amount;
	lifeStruct.health = FMath::Clamp(lifeStruct.health, 0, originalLifeStruct.health);
}
