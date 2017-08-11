// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetupInputComponent();
}


// Called every frame
void UGrabber::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint( _mPlayerPosition,
																_mPlayerViewAngle );

	FVector PlayerForward = _mPlayerPosition + ( _mPlayerViewAngle.Vector() * _mReach );

	//DrawRay( _mPlayerPosition, PlayerForward );

	if( _mPhysicsHandle->GrabbedComponent )
	{
		_mPhysicsHandle->SetTargetLocation( PlayerForward );
	}
}


void UGrabber::FindPhysicsHandleComponent()
{
	_mPhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if( _mPhysicsHandle == nullptr )
	{
		UE_LOG( LogTemp, Error, TEXT( "Grabber Owner missing UPhysicsHandleComponent on object %s" ), *( GetOwner()->GetName() ) );
		_mOwnerhasPhysicsHandle = false;
	}
	else
	{
		_mOwnerhasPhysicsHandle = true;
	}
}


void UGrabber::SetupInputComponent()
{
	_mInputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if( _mInputComponent == nullptr )
	{
		UE_LOG( LogTemp, Error, TEXT( "Grabber Owner missing (Pawn)InputComponent on object %s" ), *( GetOwner()->GetName() ) );
		_mOwnerHasInputComponent = false;
	}
	else
	{
		_mOwnerHasInputComponent = true;
	}

	if( _mOwnerHasInputComponent )
	{
		_mInputComponent->BindAction( "Grab", IE_Pressed, this, &UGrabber::Grab );
		_mInputComponent->BindAction( "Grab", IE_Released, this, &UGrabber::Release );
	}
}


const void UGrabber::DrawRay( FVector start, FVector end )
{
	DrawDebugLine( GetWorld(),
				   start,
				   end,
				   FColor( 255, 0.0f, 0.0f ),
				   false,
				   0.0f,
				   0.0f,
				   10.0f );
}


void UGrabber::Grab()
{
	UE_LOG( LogTemp, Warning, TEXT( "Grab button pressed!" ) );

	// RayCast - try and reach an actor immidiatly infront of the player with a collision channel.
	auto HitResult = GetFirstPhysicsBodyInReach();

	// if hit - try and attch a physics handle to it.
	if( HitResult.GetActor() != nullptr )
	{
		auto GrabTargetComponent = HitResult.GetComponent();

		_mPhysicsHandle->GrabComponentAtLocation( GrabTargetComponent,
												  NAME_None,
												  GrabTargetComponent->GetOwner()->GetActorLocation() );
	}
}


void UGrabber::Release()
{
	UE_LOG( LogTemp, Warning, TEXT( "Grab button released!" ) );
	// TODO release Physics handle.

	_mPhysicsHandle->ReleaseComponent();
}


const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint( _mPlayerPosition, _mPlayerViewAngle );

	FVector PlayerForward = _mPlayerPosition + ( _mPlayerViewAngle.Vector() * _mReach );
	DrawRay( _mPlayerPosition, PlayerForward );
	FCollisionQueryParams traceParam( FName( TEXT( "" ) ), false, GetOwner() );
	FHitResult hitResult;

	GetWorld()->LineTraceSingleByObjectType( hitResult,
											 _mPlayerPosition,
											 PlayerForward,
											 ECollisionChannel::ECC_PhysicsBody,
											 traceParam );

	AActor* actorHit = hitResult.GetActor();

	if( actorHit )
	{
		UE_LOG( LogTemp, Warning, TEXT( "RayCast hit %s" ), *( actorHit->GetName() ) );
	}

	return hitResult;
}