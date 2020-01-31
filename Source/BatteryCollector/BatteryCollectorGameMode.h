// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "BatteryCollectorGameMode.generated.h"


// enum to store the current state of gameplay

UENUM(BlueprintType)
enum class EBatteryPlayState : uint8
{
	EPlaying,
	EGameOver,
	EWon,
	EUnknown
};

UCLASS(minimalapi)
class ABatteryCollectorGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ABatteryCollectorGameMode();
	
	virtual void Tick(float DeltaTime) override;
	
	/** Returns power needed to win - needed for the HUD */
	UFUNCTION(BlueprintPure, Category = "Power")
	float GetPowerToWin() const;
	
	virtual void BeginPlay() override;
	
	/** Returns the current gameplay state*/
	UFUNCTION(BlueprintPure, Category = "Power")
	EBatteryPlayState GetCurrentState() const;
	
	/** Sets a new gameplay state */
	void SetCurrentState(EBatteryPlayState NewState);
	
protected:
	/** The rate at which the character loses power */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
	float DecayRate;
	
	/** The power needed to win the game */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
	float PowerToWin;
	
	/** The Widget class to use for our HUD screen */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Power", meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> HUDWidgetClass;
	
	/** The instance of the HUD class */
	UPROPERTY()
	class UUserWidget* CurrentWidget;
	
private:
	/** Keeps track of the gameplay state*/
	EBatteryPlayState CurrentState;
	
	TArray<class ASpawnVolume*> SpawnVolumeActors;
	
	/** This will handle any new function class taht rely upon changing the playing state of our game */
	void HandleNewState(EBatteryPlayState NewState);
};



