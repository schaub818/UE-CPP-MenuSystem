// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstance.h"

#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

#include "PlatformTrigger.h"

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

	UE_LOG(LogTemp, Warning, TEXT("GameInstance Init"));
}

void UPuzzlePlatformsGameInstance::LoadMenu()
{
	if (!ensure(menuClass != nullptr))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, FString::Printf(TEXT("Menu class not found!")));

		return;
	}

	UUserWidget* menu = CreateWidget<UUserWidget>(this, menuClass);

	if (!ensure(menu != nullptr))
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, FString::Printf(TEXT("CreateWidget failed!")));

		return;
	}

	menu->bIsFocusable = true;
	menu->AddToViewport();

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	FInputModeUIOnly inputModeData;

	inputModeData.SetWidgetToFocus(menu->TakeWidget());
	inputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	PlayerController->SetInputMode(inputModeData);
}

void UPuzzlePlatformsGameInstance::Host()
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting"));

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;

	Engine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}
