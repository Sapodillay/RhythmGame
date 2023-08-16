// Fill out your copyright notice in the Description page of Project Settings.


#include "NoteBlock.h"

// Sets default values
ANoteBlock::ANoteBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NoteMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Note mesh"));
	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/Mesh/cube"));
	NoteMesh->SetStaticMesh(MeshObj.Object);
	NoteMesh->SetWorldScale3D(FVector(0.1, 0.1, 0.1));
	RootComponent = NoteMesh;

}

// Called when the game starts or when spawned
void ANoteBlock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANoteBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

