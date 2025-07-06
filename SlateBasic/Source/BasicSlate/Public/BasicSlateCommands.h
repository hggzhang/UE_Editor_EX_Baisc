// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "BasicSlateStyle.h"

class FBasicSlateCommands : public TCommands<FBasicSlateCommands>
{
public:
	/*
	TEXT("BasicSlate") : Name of the command set, used to identify this set of commands.

	*/
	FBasicSlateCommands()
		: TCommands<FBasicSlateCommands>(TEXT("BasicSlate"), NSLOCTEXT("Contexts", "BasicSlate", "BasicSlate Plugin"), NAME_None, FBasicSlateStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	/*
	FUICommandInfo :
	- Name
	- Tips : hat the command does, displayed in the UI
	- Type : EUserInterfaceActionType, such as Button, ToggleButton, etc.
	- HotKey : FInputChord, can be empty, or set to a specific key binding like FInputChord(EKeys::F1)
	- Icon : can be set to a specific icon, or left empty to use the default icon from the style set
	*/
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};