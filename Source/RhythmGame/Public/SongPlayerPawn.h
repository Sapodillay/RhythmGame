// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Camera/CameraComponent.h"

//Input includes
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "NoteLane.h"

#include "SongPlayerPawn.generated.h"

UCLASS()
class RHYTHMGAME_API ASongPlayerPawn : public APawn
{
	GENERATED_BODY()

	//Inputs/Camera

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = true))
	UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere)
	TArray<ANoteLane*> NoteLanes;

#pragma region Input
	
	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputMappingContext* MappingContext;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* Row1_Action;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* Row2_Action;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* Row3_Action;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	UInputAction* Row4_Action;
	
#pragma endregion Input

	
	
#pragma region Song
	//Song 
	UPROPERTY()
	UAudioComponent* AudioComponent;

	UPROPERTY(EditDefaultsOnly, Category = "RhythmSong")
	USoundWave* SongFile;

	//BPM of the song, used to count the current beat.
	UPROPERTY(EditDefaultsOnly, Category = "RhythmSong")
	float BPM;
	
	UPROPERTY()
	bool isPlaying;

	float songPosition = 0;

	float songPositionInBeats = 0;

	float secondsPerBeat;

	float lastBeat;
	
	//changed at runtime, gets the current beat.
	UPROPERTY()
	float beat;
#pragma endregion Song


	void Row1();
	void Row2();
	void Row3();
	void Row4();
	
public:
	// Sets default values for this pawn's properties
	ASongPlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void StartSong();

	void RegisterNoteLane(ANoteLane* Lane);

};
