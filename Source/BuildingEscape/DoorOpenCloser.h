// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "Components/ActorComponent.h"
#include "DoorOpenCloser.generated.h"

UENUM( BlueprintType )
enum class DoorHingeAxis : uint8
{
	ON_X_AXIS 	UMETA( DisplayName = "AroundX" ),
	ON_Y_AXIS 	UMETA( DisplayName = "AroundY" ),
	ON_Z_AXIS	UMETA( DisplayName = "AroundZ" )
};

UCLASS( ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class BUILDINGESCAPE_API UDoorOpenCloser : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDoorOpenCloser();
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	void OpenDoor() { _mOwner->SetActorRotation( _mOpenRotation ); }
	void CloseDoor() { _mOwner->SetActorRotation( _mCloseRotation ); }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	AActor* _mOwner;
	FRotator _mOpenRotation;
	FRotator _mCloseRotation;

	float _mTimeDoorLastOpened;
	bool _mIsPawnStillInTrigger;

	UPROPERTY( EditAnywhere )
		float _mOpenAngle;
	UPROPERTY( EditAnywhere )
		ATriggerVolume* _mOpenTrigger;
	UPROPERTY( EditAnywhere )
		float _mMaxTimeDoorPermittedOpen;
	UPROPERTY( EditAnywhere )
		DoorHingeAxis _mHinge;
	UPROPERTY( EditAnywhere )
		float PreasurePlateTriggerWeight;

private:
	float GetTotalMassOfActorsOnPlate();
};