// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	_mReach = 100;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	UE_LOG( LogTemp, Warning, TEXT( "Grabber reporting for duty!" ) );
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint( _mPlayerPosition,
																_mPlayerViewAngle );

	UE_LOG( LogTemp, Warning, TEXT( "Position %s and Rotation %s on the Player" ),
		*_mPlayerPosition.ToString(), *_mPlayerViewAngle.ToString() );

	FVector PlayerForward = _mPlayerPosition + (_mPlayerViewAngle.Vector() * _mReach);

	DrawDebugLine( GetWorld(),
				   _mPlayerPosition,
				   PlayerForward,
				   FColor( 255, 0.0f, 0.0f ),
				   false,
				   0.0f,
				   0.0f,
				   10.0f );
}