// Copyright Epic Games, Inc. All Rights Reserved.

#include "SteamMultiTestGameMode.h"
#include "SteamMultiTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASteamMultiTestGameMode::ASteamMultiTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
