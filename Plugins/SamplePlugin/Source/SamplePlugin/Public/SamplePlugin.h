// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FExtender;
class FMenuBuilder;
class FMenuBarBuilder;

class FSamplePluginModule : public IModuleInterface
{
public:
	// IModuleInterface interface.
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	// End of IModuleInterface interface.

private:
	// メニューバーに拡張内容を登録.
	void OnWindowMenuBarExtension(FMenuBarBuilder& MenuBarBuilder);

	// プルダウンメニューの登録.
	void OnPulldownMenuExtension(FMenuBuilder& MenuBuilder);

	// プルダウンメニュー以下のサブメニューを登録.
	void HandleRegisterSubMenu1(FMenuBuilder& MenuBuilder);
	void HandleRegisterSubMenu2(FMenuBuilder& MenuBuilder);
	void HandleRegisterSubMenu3(FMenuBuilder& MenuBuilder);

	// タブが生成されるときに呼ばれる.
	TSharedRef<SDockTab> HandleRegisterTabSpawner(const FSpawnTabArgs& TabSpawnArgs);
	
private:
	// メニューの拡張ポイント.
	TSharedPtr<FExtender> Extender;
};
