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

	IMenuInterface* menuInterface;

	APlayerController* playerController;

	UFUNCTION()
	void OnBTN_MainHostClicked();

public:
	void SetMenuInterface(IMenuInterface* interface);
	void Setup(IMenuInterface* interface);
	void Enable();
	void Disable();
};
