// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstance.h"

#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

#include "PlatformTrigger.h"
#include "MenuSystem/MainMenu.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer & ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> menuBPClassFinder(TEXT("/Game/MenuSystem/WBP_MainMenu"));

	if (!ensure(menuBPClassFinder.Class != nullptr))
	{
		UE_LOG(LogTemp, Error, TEXT("Menu class not found!"));

		return;
	}

	menuClass = menuBPClassFinder.Class;

	UE_LOG(LogTemp, Warning, TEXT("Found class %s"), *menuClass->GetName());
}

void UPuzzlePlatformsGameInstance::Init()
{
	Super::Init();

	if (!ensure(menuClass != nullptr))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, FString::Printf(TEXT("Menu class not found!")));

		return;
	}

	menu = CreateWidget<UMainMenu>(this, menuClass);

	if (!ensure(menu != nullptr))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, FString::Printf(TEXT("CreateWidget failed!")));

		return;
	}

	menu->Setup(this);
}

void UPuzzlePlatformsGameInstance::LoadMenu()
{
	if (!ensure(menu != nullptr))
	{
		return;
	}

	menu->Enable(GetFirstLocalPlayerController());
}

void UPuzzlePlatformsGameInstance::Host()
{
	if (menu != nullptr)
	{
		menu->Disable(GetFirstLocalPlayerController());
	}

	UWorld* World = GetWorld();

	if (!ensure(World != nullptr))
	{
		return;
	}

	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
	if (menu != nullptr)
	{
		menu->Disable(GetFirstLocalPlayerController());
	}

	APlayerController* playerController = GetFirstLocalPlayerController();

	if (!ensure(playerController != nullptr))
	{
		return;
	}

	playerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}
