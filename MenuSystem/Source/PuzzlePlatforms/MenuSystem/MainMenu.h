// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MainMenu.generated.h"

/**
 *
 */
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* BTN_MainHost;

	UPROPERTY(meta = (BindWidget))
	class UButton* BTN_MainJoin;

	UPROPERTY(meta = (BindWidget))
	class UButton* BTN_Cancel;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* WSW_MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UWidget* OVL_MainMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* OVL_JoinMenu;

	IMenuInterface* menuInterface;

	APlayerController* playerController;

	UFUNCTION()
	void OnBTN_MainHostClicked();

	UFUNCTION()
	void OnBTN_MainJoinClicked();

	UFUNCTION()
	void OnBTN_CancelClicked();

public:
	void SetMenuInterface(IMenuInterface* interface);
	void Setup(IMenuInterface* interface);
	void Enable();
	void Disable();
};
