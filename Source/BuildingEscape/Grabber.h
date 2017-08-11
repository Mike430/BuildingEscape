// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPhysicsHandleComponent* _mPhysicsHandle = nullptr;
	UInputComponent* _mInputComponent = nullptr;

	FVector _mPlayerPosition;
	FRotator _mPlayerViewAngle;

	UPROPERTY( EditAnywhere )
		float _mReach;

	// rayCast and possess object
	void Grab();
	// Drop possessed object
	void Release();

private:
	// Getting the physics handle on the Owner and binding it to a member level variable.
	void FindPhysicsHandleComponent();

	// Gets the input component that appears at runtime and handles bindings.
	void SetupInputComponent();

	// Ray cast and return the first object hit.
	FHitResult GetFirstPhysicsBodyInReach();

	// Returns a point in front of the player and centred in view.
	FVector GetReachLineEnd();
	
	// Utility function for drawing a red line between two points.
	const void DrawRay( FVector start, FVector end );

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};