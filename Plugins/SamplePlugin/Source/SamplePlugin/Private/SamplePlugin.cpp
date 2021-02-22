// Copyright Epic Games, Inc. All Rights Reserved.

#include "SamplePlugin.h"
#include "LevelEditor.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

#define LOCTEXT_NAMESPACE "FSamplePluginModule"
#define LEVEL_EDITOR_NAME "LevelEditor"

void FSamplePluginModule::StartupModule()
{
	if (IsRunningCommandlet())
	{
		return;
	}

	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>(LEVEL_EDITOR_NAME);
	Extender = MakeShareable(new FExtender());
	if (Extender.IsValid())
	{
		Extender->AddMenuBarExtension(
			"Help",
			EExtensionHook::After,
			NULL,
			FMenuBarExtensionDelegate::CreateRaw(this, &FSamplePluginModule::OnWindowMenuBarExtension)
		);
	}

	TSharedPtr<FExtensibilityManager> MenuExtensibilityManager = LevelEditorModule.GetMenuExtensibilityManager();
	if (MenuExtensibilityManager.IsValid())
	{
		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(Extender);
	}
}

void FSamplePluginModule::ShutdownModule()
{
	if (Extender.IsValid() && FModuleManager::Get().IsModuleLoaded(LEVEL_EDITOR_NAME))
	{
		FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>(LEVEL_EDITOR_NAME);
		TSharedPtr<FExtensibilityManager> MenuExtensibilityManager = LevelEditorModule.GetMenuExtensibilityManager();
		if (MenuExtensibilityManager.IsValid())
		{
			LevelEditorModule.GetToolBarExtensibilityManager()->RemoveExtender(Extender);
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
	MenuBuilder.BeginSection("SectionHook", LOCTEXT("SectionNameA", "Section A"));

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
	MenuBuilder.BeginSection("SectionHook", LOCTEXT("SectionNameB", "Section B"));

	MenuBuilder.AddSubMenu(
		LOCTEXT("PulldownMenuTitle3", "Sub Menu 3"),
		LOCTEXT("PulldownMenuToolTip3", "A description of this submenu is given here."),
		FNewMenuDelegate::CreateRaw(this, &FSamplePluginModule::HandleRegisterSubMenu3)
	);

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

#undef LEVEL_EDITOR_NAME
#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FSamplePluginModule, SamplePlugin)