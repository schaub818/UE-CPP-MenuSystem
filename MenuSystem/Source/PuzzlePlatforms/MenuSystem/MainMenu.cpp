// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuSystem/MainMenu.h"
#include "Components/Button.h"

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
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, FString::Printf(TEXT("Hosting server")));
}