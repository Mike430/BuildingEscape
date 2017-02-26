// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "DoorOpenCloser.h"


// Sets default values for this component's properties
UDoorOpenCloser::UDoorOpenCloser()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorOpenCloser::BeginPlay()
{
	Super::BeginPlay();

	// ...
	_mOwner = GetOwner();
	_mOpeningRotation = FRotator(0.0f, 150.0f, 0.0f);
	_mOwner->SetActorRotation(_mOpeningRotation);
	
}


// Called every frame
void UDoorOpenCloser::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

