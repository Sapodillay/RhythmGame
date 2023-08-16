// Fill out your copyright notice in the Description page of Project Settings.


#include "SongPlayerPawn.h"

#include "Camera/CameraComponent.h"
#include "Components/AudioComponent.h"

#include "EnhancedInputComponent.h"

void ASongPlayerPawn::Row1()
{
	UE_LOG(LogTemp, Warning, TEXT("ROW 1"));
	if (!NoteLanes.IsEmpty())
	{
		NoteLanes[0]->SpawnNote();
		UE_LOG(LogTemp, Warning, TEXT("Spawned note"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to spawn note"));
	}
	
}

void ASongPlayerPawn::Row2()
{
	UE_LOG(LogTemp, Warning, TEXT("ROW 2"));
}

void ASongPlayerPawn::Row3()
{
	UE_LOG(LogTemp, Warning, TEXT("ROW 3"));
}

void ASongPlayerPawn::Row4()
{
	UE_LOG(LogTemp, Warning, TEXT("ROW 4"));
}

// Sets default values
ASongPlayerPawn::ASongPlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	AudioComponent->SetupAttachment(RootComponent);

	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(RootComponent);
	FirstPersonCameraComponent->SetWorldLocation(FVector(-90, 20, 440)); // Position the camera
	FirstPersonCameraComponent->SetWorldRotation(FRotator(0, -30, 0));
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

}

// Called when the game starts or when spawned
void ASongPlayerPawn::BeginPlay()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}
	
	Super::BeginPlay();
	StartSong();
}

// Called every frame
void ASongPlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isPlaying)
	{
		songPosition += DeltaTime;
		songPositionInBeats = FMath::Floor(songPosition / secondsPerBeat);
	}

	
	GEngine->AddOnScreenDebugMessage(1, 15.0f, FColor::Yellow,   FString::Printf(TEXT("Beat: %f"), songPositionInBeats));	
}

// Called to bind functionality to input
void ASongPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(Row1_Action, ETriggerEvent::Started, this, &ASongPlayerPawn::Row1);
		EnhancedInputComponent->BindAction(Row2_Action, ETriggerEvent::Started, this, &ASongPlayerPawn::Row2);
		EnhancedInputComponent->BindAction(Row3_Action, ETriggerEvent::Started, this, &ASongPlayerPawn::Row3);
		EnhancedInputComponent->BindAction(Row4_Action, ETriggerEvent::Started, this, &ASongPlayerPawn::Row4);
	}

}

void ASongPlayerPawn::StartSong()
{
	if (AudioComponent)
	{
		secondsPerBeat = 60.0f / BPM;
		AudioComponent->SetSound(SongFile);
		AudioComponent->SetVolumeMultiplier(0.5f);
		AudioComponent->Play();
		isPlaying = true;
	}

	
}

void ASongPlayerPawn::RegisterNoteLane(ANoteLane* Lane)
{
	NoteLanes.Add(Lane);
}

