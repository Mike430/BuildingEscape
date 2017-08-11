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

	if( _mPhysicsHandle->GrabbedComponent )
	{
		FVector PlayerForward = GetReachLineEnd();
		DrawRay( _mPlayerPosition, PlayerForward );
		_mPhysicsHandle->SetTargetLocation( PlayerForward );
	}
}


void UGrabber::FindPhysicsHandleComponent()
{
	_mPhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if( _mPhysicsHandle == nullptr )
	{
		UE_LOG( LogTemp, Error, TEXT( "Grabber Owner missing UPhysicsHandleComponent on object %s" ), *( GetOwner()->GetName() ) );
	}
}


void UGrabber::SetupInputComponent()
{
	_mInputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if( _mInputComponent == nullptr )
	{
		UE_LOG( LogTemp, Error, TEXT( "Grabber Owner missing (Pawn)InputComponent on object %s" ), *( GetOwner()->GetName() ) );
	}
	else
	{
		_mInputComponent->BindAction( "Grab", IE_Pressed, this, &UGrabber::Grab );
		_mInputComponent->BindAction( "Grab", IE_Released, this, &UGrabber::Release );
	}
}


void UGrabber::Grab()
{
	auto HitResult = GetFirstPhysicsBodyInReach();

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
	_mPhysicsHandle->ReleaseComponent();
}


FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	FVector PlayerForward = GetReachLineEnd();
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


FVector UGrabber::GetReachLineEnd()
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint( _mPlayerPosition,
																_mPlayerViewAngle );

	return _mPlayerPosition + ( _mPlayerViewAngle.Vector() * _mReach );
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