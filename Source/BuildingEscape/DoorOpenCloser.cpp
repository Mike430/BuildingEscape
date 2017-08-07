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
	_mActorThatOpens = this->GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UDoorOpenCloser::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (_mOpenTrigger->IsOverlappingActor(_mActorThatOpens))
	{
		if( _mIsPawnStillInTrigger == false )
		{
			this->OpenDoor();
			_mTimeDoorLastOpened = GetWorld()->GetTimeSeconds();
		}
		_mIsPawnStillInTrigger = true;
	}
	else
	{
		_mIsPawnStillInTrigger = false;

		if( (GetWorld()->GetTimeSeconds() - _mTimeDoorLastOpened ) > _mMaxTimeDoorPermittedOpen )
		{
			CloseDoor();
		}
	}
}