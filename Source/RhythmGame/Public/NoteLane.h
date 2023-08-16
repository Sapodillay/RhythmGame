// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NoteBlock.h"
#include "Components/BoxComponent.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Actor.h"
#include "NoteLane.generated.h"

UCLASS()
class RHYTHMGAME_API ANoteLane : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	USplineComponent* NotePath;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* JudgementArea;

	UPROPERTY(VisibleAnywhere)
	TMap<ANoteBlock*, float> NotesToMove;

	UPROPERTY(EditDefaultsOnly)
	float notespeed = 100.0f;

	AActor* SelectedActor;
	

public:	
	// Sets default values for this actor's properties
	ANoteLane();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnNote();

	void HandleInput();

	UFUNCTION(BlueprintCallable)
	void OnBeginOverlap(AActor* OverlapActor);

	void HandleScore(float distance);

};
