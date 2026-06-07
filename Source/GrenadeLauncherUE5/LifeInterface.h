#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LifeInterface.generated.h"

UINTERFACE(BlueprintType)
class ULifeInterface : public UInterface
{
	GENERATED_BODY()
};

class GRENADELAUNCHERUE5_API ILifeInterface
{
	GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void TakeDamage(float damage, FVector hitLocation);

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
    void Death();
};