// Copyright Epic Games, Inc. All Rights Reserved.

#include "SamplePlugin.h"
#include "LevelEditor.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "WorkspaceMenuStructureModule.h"
#include "WorkspaceMenuStructure.h"
#include "Widgets/Docking/SDockTab.h"

#define LOCTEXT_NAMESPACE "FSamplePluginModule"

namespace SamplePluginDefine
{
	static const FName LevelEditorName = TEXT("LevelEditor");
	static const FName TabName = TEXT("TestTab");
}

void FSamplePluginModule::StartupModule()
{
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>(SamplePluginDefine::LevelEditorName);
	Extender = MakeShared<FExtender>();
	if (Extender.IsValid())
	{
		Extender->AddMenuBarExtension(
			"Help",
			EExtensionHook::After,
			nullptr,
			FMenuBarExtensionDelegate::CreateRaw(this, &FSamplePluginModule::OnWindowMenuBarExtension)
		);
	}
	
	const TSharedPtr<FExtensibilityManager> MenuExtensibilityManager = LevelEditorModule.GetMenuExtensibilityManager();
	if (MenuExtensibilityManager.IsValid())
	{
		MenuExtensibilityManager->AddExtender(Extender);
	}

	const TSharedRef<FGlobalTabmanager> GlobalTabManager = FGlobalTabmanager::Get();
	GlobalTabManager->RegisterTabSpawner(
		SamplePluginDefine::TabName,
		FOnSpawnTab::CreateRaw(this, &FSamplePluginModule::HandleRegisterTabSpawner)
	)
	.SetDisplayName(FText::FromName(SamplePluginDefine::TabName))
	.SetGroup(WorkspaceMenu::GetMenuStructure().GetLevelEditorCategory())
	.SetTooltipText(LOCTEXT("TabTooltipText", "This is a test tab."));
}

void FSamplePluginModule::ShutdownModule()
{
	const TSharedRef<FGlobalTabmanager> GlobalTabManager = FGlobalTabmanager::Get();
	GlobalTabManager->UnregisterTabSpawner(SamplePluginDefine::TabName);
	
	if (Extender.IsValid() && FModuleManager::Get().IsModuleLoaded(SamplePluginDefine::LevelEditorName))
	{
		FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>(SamplePluginDefine::LevelEditorName);
		const TSharedPtr<FExtensibilityManager> MenuExtensibilityManager = LevelEditorModule.GetMenuExtensibilityManager();
		if (MenuExtensibilityManager.IsValid())
		{
			MenuExtensibilityManager->RemoveExtender(Extender);
		}
	}
}

void FSamplePluginModule::OnWindowMenuBarExtension(FMenuBarBuilder& MenuBarBuilder)
{
	MenuBarBuilder.AddPullDownMenu(
		LOCTEXT("MenuBarTitle", "Sample Menu"),
		LOCTEXT("MenuBarToolkit", "A description of this menu is given here."),
		FNewMenuDelegate::CreateRaw(this, &FSamplePluginModule::OnPulldownMenuExtension)
	);
}

void FSamplePluginModule::OnPulldownMenuExtension(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.BeginSection(TEXT("SectionHook"), LOCTEXT("SectionNameA", "Section A"));

	MenuBuilder.AddSubMenu(
		LOCTEXT("PulldownMenuTitle1", "Sub Menu 1"),
		LOCTEXT("PulldownMenuToolTip1", "A description of this submenu is given here."),
		FNewMenuDelegate::CreateRaw(this, &FSamplePluginModule::HandleRegisterSubMenu1)
	);

	MenuBuilder.AddSubMenu(
		LOCTEXT("PulldownMenuTitle2", "Sub Menu 2"),
		LOCTEXT("PulldownMenuToolTip2", "A description of this submenu is given here."),
		FNewMenuDelegate::CreateRaw(this, &FSamplePluginModule::HandleRegisterSubMenu2)
	);

	MenuBuilder.EndSection();
	MenuBuilder.BeginSection(TEXT("SectionHook"), LOCTEXT("SectionNameB", "Section B"));

	MenuBuilder.AddSubMenu(
		LOCTEXT("PulldownMenuTitle3", "Sub Menu 3"),
		LOCTEXT("PulldownMenuToolTip3", "A description of this submenu is given here."),
		FNewMenuDelegate::CreateRaw(this, &FSamplePluginModule::HandleRegisterSubMenu3)
	);

	MenuBuilder.EndSection();
	MenuBuilder.BeginSection(TEXT("SectionHook"), LOCTEXT("SectionNameC", "Section C"));
	
	const TSharedRef<FGlobalTabmanager> GlobalTabManager = FGlobalTabmanager::Get();
	GlobalTabManager->PopulateTabSpawnerMenu(MenuBuilder, SamplePluginDefine::TabName);

	MenuBuilder.EndSection();
}

void FSamplePluginModule::HandleRegisterSubMenu1(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(
		LOCTEXT("MenuTitle1_1", "Sample Command 1"),
		LOCTEXT("ToolTip1_1", "A description of this command is given here."),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateLambda([]()
	{
		GEngine->AddOnScreenDebugMessage(0, 3.f, FColor::Green, TEXT("Execute Sample Command 1"));
	}))
	);

	MenuBuilder.AddMenuEntry(
		LOCTEXT("MenuTitle1_2", "Sample Command 2"),
		LOCTEXT("ToolTip1_2", "A description of this command is given here."),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateLambda([]()
	{
		GEngine->AddOnScreenDebugMessage(0, 3.f, FColor::Green, TEXT("Execute Sample Command 2"));
	}))
	);
}

void FSamplePluginModule::HandleRegisterSubMenu2(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(
		LOCTEXT("MenuTitle2_1", "Sample Command 3"),
		LOCTEXT("ToolTip2_1", "A description of this command is given here."),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateLambda([]()
	{
		GEngine->AddOnScreenDebugMessage(0, 3.f, FColor::Green, TEXT("Execute Sample Command 3"));
	}))
	);
}

void FSamplePluginModule::HandleRegisterSubMenu3(FMenuBuilder& MenuBuilder)
{
	MenuBuilder.AddMenuEntry(
		LOCTEXT("MenuTitle3_1", "Sample Command 4"),
		LOCTEXT("ToolTip3_1", "A description of this command is given here."),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateLambda([]()
	{
		GEngine->AddOnScreenDebugMessage(0, 3.f, FColor::Green, TEXT("Execute Sample Command 4"));
	}))
	);

	MenuBuilder.AddMenuEntry(
		LOCTEXT("MenuTitle3_2", "Sample Command 5"),
		LOCTEXT("ToolTip3_2", "A description of this command is given here."),
		FSlateIcon(),
		FUIAction(FExecuteAction::CreateLambda([]()
	{
		GEngine->AddOnScreenDebugMessage(0, 3.f, FColor::Green, TEXT("Execute Sample Command 5"));
	}))
	);
}

TSharedRef<SDockTab> FSamplePluginModule::HandleRegisterTabSpawner(const FSpawnTabArgs& TabSpawnArgs)
{
	TSharedRef<SDockTab> SpawnedTab = SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(STextBlock)
			.Text(LOCTEXT("TestTabText", "This is a test tab."))
		];
		
	return SpawnedTab;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSamplePluginModule, SamplePlugin)