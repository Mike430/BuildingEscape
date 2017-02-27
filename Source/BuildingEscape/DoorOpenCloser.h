// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "DoorOpenCloser.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UDoorOpenCloser : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorOpenCloser();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//AActor* _mOwner;
	//FRotator _mOpeningRotation;

	AActor* _mOwner;
	FRotator _mOpenRotation;
	FRotator _mCloseRotation;
	UPROPERTY(VisibleAnywhere)
		float _mOpenAngle;
	UPROPERTY(EditAnywhere)
		ATriggerVolume* _mOpenTrigger;
	UPROPERTY(EditAnywhere)
		AActor* _mActorThatOpens;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OpenDoor() { _mOwner->SetActorRotation(_mOpenRotation); }
	void CloseDoor() { _mOwner->SetActorRotation(_mCloseRotation); }
};
