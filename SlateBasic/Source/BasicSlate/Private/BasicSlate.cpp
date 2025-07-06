// Copyright Epic Games, Inc. All Rights Reserved.

#include "BasicSlate.h"
#include "BasicSlateStyle.h"
#include "BasicSlateCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"
#include "SMyCompoundWidget.h"
static const FName BasicSlateTabName("BasicSlate");

#define LOCTEXT_NAMESPACE "FBasicSlateModule"


void FBasicSlateModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	// Initialize the style and commands
	FBasicSlateStyle::Initialize();
	FBasicSlateStyle::ReloadTextures();

	FBasicSlateCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	// Map the command to the button click action
	PluginCommands->MapAction(
		FBasicSlateCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FBasicSlateModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FBasicSlateModule::RegisterMenus));
	
	// Register the tab spawner for the plugin tab
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(BasicSlateTabName, FOnSpawnTab::CreateRaw(this, &FBasicSlateModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FBasicSlateTabTitle", "BasicSlate"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FBasicSlateModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FBasicSlateStyle::Shutdown();

	FBasicSlateCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(BasicSlateTabName);
}

TSharedRef<SDockTab> FBasicSlateModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FBasicSlateModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("BasicSlate.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SMyCompoundWidget)
				.InitText(FText::FromString(TEXT("Init Text")))
			]
		];
}

void FBasicSlateModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(BasicSlateTabName);
}

void FBasicSlateModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FBasicSlateCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FBasicSlateCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FBasicSlateModule, BasicSlate)