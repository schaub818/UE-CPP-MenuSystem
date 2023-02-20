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

	if (!ensure(BTN_Host != nullptr))
	{
		return false;
	}

	BTN_Host->OnClicked.AddDynamic(this, &UMainMenu::OnBTN_HostClicked);

	return true;
}

void UMainMenu::OnBTN_HostClicked()
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