// Copyright Epic Games, Inc. All Rights Reserved.

#include "BasicSlateCommands.h"

#define LOCTEXT_NAMESPACE "FBasicSlateModule"

/*
OpenPluginWindow : FUICommandInfo
BasicSlate : Name of the command, Can be used to identify the command in the UI
Bring up BasicSlate window : Tooltip for the command, displayed in the UI
EUserInterfaceActionType::Button : Type of the command, in this case a button
FInputChord : Default input chord for the command, can be empty,also can be such as FInputChord(EKeys::F1) for a key binding
*/
void FBasicSlateCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "BasicSlate", "Bring up BasicSlate window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
