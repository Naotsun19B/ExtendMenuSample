// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FExtender;
class FMenuBuilder;
class FMenuBarBuilder;

class FSamplePluginModule : public IModuleInterface
{
private:
	// ���j���[�̊g���|�C���g.
	TSharedPtr<FExtender> Extender;

public:
	// IModuleInterface interface.
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	// End of IModuleInterface interface.

private:
	// ���j���[�o�[�Ɋg�����e��o�^.
	void OnWindowMenuBarExtension(FMenuBarBuilder& MenuBarBuilder);

	// �v���_�E�����j���[�̓o�^.
	void OnPulldownMenuExtension(FMenuBuilder& MenuBuilder);

	// �v���_�E�����j���[�ȉ��̃T�u���j���[��o�^.
	void HandleRegisterSubMenu1(FMenuBuilder& MenuBuilder);
	void HandleRegisterSubMenu2(FMenuBuilder& MenuBuilder);
	void HandleRegisterSubMenu3(FMenuBuilder& MenuBuilder);
};
