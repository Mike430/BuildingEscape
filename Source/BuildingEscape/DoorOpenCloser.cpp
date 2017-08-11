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

	switch(_mHinge)
	{
		case DoorHingeAxis::ON_X_AXIS:
			_mOpenRotation = FRotator( _mOpenAngle, 0.0f, 0.0f );
			break;
		case DoorHingeAxis::ON_Y_AXIS:
			_mOpenRotation = FRotator( 0.0f, _mOpenAngle, 0.0f );
			break;
		case DoorHingeAxis::ON_Z_AXIS:
			_mOpenRotation = FRotator( 0.0f, 0.0f, _mOpenAngle );
			break;
		default:
			_mOpenRotation = FRotator( 0.0f, _mOpenAngle, 0.0f );
			break;
	}



	_mCloseRotation = FRotator(0.0f, 0.0f, 0.0f);
	_mOwner->SetActorRotation(_mCloseRotation);
}


// Called every frame
void UDoorOpenCloser::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetTotalMassOfActorsOnPlate() >= PreasurePlateTriggerWeight)
	{
		this->OpenDoor();
	}
	else
	{
		CloseDoor();
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
		UE_LOG( LogTemp, Warning, TEXT( "%s weighs %f" ), *actor->GetName(), weight );
	}

	UE_LOG( LogTemp, Warning, TEXT( "%f out of %f" ), returnVal, PreasurePlateTriggerWeight );

	return returnVal;
}