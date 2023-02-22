// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuSystem/MainMenu.h"

#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/Widget.h"
#include "Components/WidgetSwitcher.h"

#include "PuzzlePlatformsGameInstance.h"

bool UMainMenu::Initialize()
{
	if (!Super::Initialize())
	{
		return false;
	}

	if (!ensure(BTN_MainHost != nullptr))
	{
		return false;
	}

	BTN_MainHost->OnClicked.AddDynamic(this, &UMainMenu::OnBTN_MainHostClicked);

	if (!ensure(BTN_MainJoin != nullptr))
	{
		return false;
	}

	BTN_MainJoin->OnClicked.AddDynamic(this, &UMainMenu::OnBTN_MainJoinClicked);

	if (!ensure(BTN_Join != nullptr))
	{
		return false;
	}

	BTN_Join->OnClicked.AddDynamic(this, &UMainMenu::OnBTN_JoinClicked);

	if (!ensure(BTN_Cancel != nullptr))
	{
		return false;
	}

	BTN_Cancel->OnClicked.AddDynamic(this, &UMainMenu::OnBTN_CancelClicked);

	return true;
}

void UMainMenu::OnBTN_MainHostClicked()
{
	if (!ensure(menuInterface != nullptr))
	{
		return;
	}

	menuInterface->Host();
}

void UMainMenu::OnBTN_MainJoinClicked()
{
	if (!ensure(WSW_MenuSwitcher != nullptr))
	{
		return;
	}

	if (!ensure(OVL_JoinMenu != nullptr))
	{
		return;
	}

	WSW_MenuSwitcher->SetActiveWidget(OVL_JoinMenu);
}

void UMainMenu::OnBTN_JoinClicked()
{
	if (!ensure(menuInterface != nullptr))
	{
		return;
	}

	if (!ensure(TXT_IPAddress != nullptr))
	{
		return;
	}

	menuInterface->Join(TXT_IPAddress->GetText().ToString());
}

void UMainMenu::OnBTN_CancelClicked()
{
	if (!ensure(WSW_MenuSwitcher != nullptr))
	{
		return;
	}

	if (!ensure(OVL_MainMenu != nullptr))
	{
		return;
	}

	WSW_MenuSwitcher->SetActiveWidget(OVL_MainMenu);
}

void UMainMenu::SetMenuInterface(IMenuInterface* interface)
{
	menuInterface = interface;
}

void UMainMenu::Setup(IMenuInterface* interface)
{
	menuInterface = interface;

	this->bIsFocusable = true;
}

void UMainMenu::Enable(APlayerController* playerController)
{
	if (!ensure(playerController != nullptr))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("playerController is null!")));

		return;
	}

	this->AddToViewport();

	FInputModeUIOnly inputModeData;

	inputModeData.SetWidgetToFocus(this->TakeWidget());
	inputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	playerController->SetInputMode(inputModeData);
	playerController->SetShowMouseCursor(true);
}

void UMainMenu::Disable(APlayerController* playerController)
{
	if (!ensure(playerController != nullptr))
	{
		return;
	}

	this->RemoveFromParent();

	FInputModeGameOnly inputModeData;

	playerController->SetInputMode(inputModeData);
	playerController->SetShowMouseCursor(false);
}