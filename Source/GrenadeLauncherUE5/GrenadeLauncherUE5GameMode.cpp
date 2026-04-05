// Copyright Epic Games, Inc. All Rights Reserved.

#include "GrenadeLauncherUE5GameMode.h"
#include "GrenadeLauncherUE5Character.h"
#include "UObject/ConstructorHelpers.h"

AGrenadeLauncherUE5GameMode::AGrenadeLauncherUE5GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
