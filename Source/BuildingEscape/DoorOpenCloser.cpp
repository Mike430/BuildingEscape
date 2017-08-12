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
}


// Called every frame
void UDoorOpenCloser::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if( IsDoorTriggerNullptr() )
	{
		return;
	}

	if (GetTotalMassOfActorsOnPlate() >= PreasurePlateTriggerWeight)
	{
		_mOnOpenRequest.Broadcast();
	}
	else
	{
		_mOnCloseRequest.Broadcast();
	}
}

float UDoorOpenCloser::GetTotalMassOfActorsOnPlate()
{
	float returnVal = 0.0f;

	TArray<AActor*> overlappingActors;
	_mOpenTrigger->GetOverlappingActors( overlappingActors, nullptr);
	float weight = 0.0f;

	for( const auto* actor : overlappingActors )
	{
		weight = actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		returnVal += weight;
		//UE_LOG( LogTemp, Warning, TEXT( "%s weighs %f" ), *actor->GetName(), weight );
	}

	//UE_LOG( LogTemp, Warning, TEXT( "%f out of %f" ), returnVal, PreasurePlateTriggerWeight );

	return returnVal;
}

const bool UDoorOpenCloser::IsDoorTriggerNullptr()
{
	if( _mOpenTrigger == nullptr )
	{
		UE_LOG( LogTemp, Error, TEXT( "DoorOpenCloser trigger is uninitialised as nullptr." ) );
		return true;
	}
	return false;
}
