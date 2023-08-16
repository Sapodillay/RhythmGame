// Fill out your copyright notice in the Description page of Project Settings.


#include "NoteLane.h"

#include "NoteBlock.h"
#include "SongPlayerPawn.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ANoteLane::ANoteLane()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	
	
	NotePath = CreateDefaultSubobject<USplineComponent>(TEXT("Note Path"));
	NotePath->SetupAttachment(RootComponent);

	JudgementArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Judgement Area Collider"));
	JudgementArea->SetupAttachment(NotePath);
	
}

// Called when the game starts or when spawned
void ANoteLane::BeginPlay()
{
	Super::BeginPlay();
	ASongPlayerPawn* PlayerPawn = Cast<ASongPlayerPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (PlayerPawn)
	{
		PlayerPawn->RegisterNoteLane(this);
	}

	
}

// Called every frame
void ANoteLane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(NotePath)
	{
		if(!NotesToMove.IsEmpty())
		{
			for (auto NoteTuple : NotesToMove)
			{
				
				NoteTuple.Value += 1.0f;
				FVector Location = NotePath->GetLocationAtDistanceAlongSpline(NoteTuple.Value, ESplineCoordinateSpace::World);
				GEngine->AddOnScreenDebugMessage(2, 15.0f, FColor::Yellow,   FString::Printf(TEXT("Distance: %f"), NoteTuple.Value));	
				NoteTuple.Key->SetActorLocation(Location);
			}
		}
	}

}

void ANoteLane::SpawnNote()
{
	//Test spawn mesh. move to factory class later
	FActorSpawnParameters SpawnParams;
	ANoteBlock* Note = GetWorld()->SpawnActor<ANoteBlock>(ANoteBlock::StaticClass(), NotePath->GetLocationAtDistanceAlongSpline(0, ESplineCoordinateSpace::World), GetActorRotation(), SpawnParams);
	NotesToMove.Add(Note, 0.0f);
	
}

