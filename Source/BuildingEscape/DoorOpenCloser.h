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

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FDoorEvent );

UCLASS( ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class BUILDINGESCAPE_API UDoorOpenCloser : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDoorOpenCloser();
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY( EditAnywhere )
		ATriggerVolume* _mOpenTrigger = nullptr;
	UPROPERTY( EditAnywhere )
		float PreasurePlateTriggerWeight;

	UPROPERTY( BlueprintAssignable )
		FDoorEvent _mOnOpenRequest;
	UPROPERTY( BlueprintAssignable )
		FDoorEvent _mOnCloseRequest;

private:
	float GetTotalMassOfActorsOnPlate();

	const bool IsDoorTriggerNullptr();
};