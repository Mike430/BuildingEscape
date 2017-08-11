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
	bool _mOwnerhasPhysicsHandle;
	UInputComponent* _mInputComponent = nullptr;
	bool _mOwnerHasInputComponent;

	FVector _mPlayerPosition;
	FRotator _mPlayerViewAngle;

	FVector _mActorPosition;
	FRotator _mActorViewAngle;

	UPROPERTY( EditAnywhere )
		float _mReach;

	//rayCast and grab
	void Grab();
	//Drop possessed object
	void Release();

private:
	void FindPhysicsHandleComponent();
	void SetupInputComponent();
	const void DrawRay(FVector start, FVector end);
	const FHitResult GetFirstPhysicsBodyInReach();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};