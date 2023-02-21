// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuSystem/MainMenu.h"
#include "Components/Button.h"
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

void UMainMenu::SetMenuInterface(IMenuInterface* interface)
{
	menuInterface = interface;
}

void UMainMenu::Setup(IMenuInterface* menuInterface)
{
	this->menuInterface = menuInterface;
	this->bIsFocusable = true;
}

void UMainMenu::Enable()
{
	UWorld* world = GetWorld();

	if (!ensure(world != nullptr))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("World is null!")));

		return;
	}

	playerController = world->GetFirstPlayerController();

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

void UMainMenu::Disable()
{
	if (!ensure(playerController != nullptr))
	{
		return;
	}

	this->RemoveFromViewport();

	FInputModeGameOnly inputModeData;

	playerController->SetInputMode(inputModeData);
	playerController->SetShowMouseCursor(false);
}