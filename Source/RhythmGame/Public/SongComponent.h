// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FileMediaSource.h"
#include "Components/ActorComponent.h"
#include "SongComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RHYTHMGAME_API USongComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY()
	UAudioComponent* AudioComponent;

	UPROPERTY(EditDefaultsOnly, Category = "RhythmSong")
	USoundWave* SongFile;
	

public:	
	// Sets default values for this component's properties
	USongComponent();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
