// Fill out your copyright notice in the Description page of Project Settings.


#include "RollaBallPlayer.h"
#include "GameFramework/SpringArmComponent.h" //gives access to full funtionality of the class unlike forward declaration
#include "Camera/CameraComponent.h"

// Sets default values
ARollaBallPlayer::ARollaBallPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SpringArm = CreateAbstractDefaultSubobject<USpringArmComponent>("SpringArm");
	Camera = CreateAbstractDefaultSubobject<UCameraComponent>("Camera");


	RootComponent = Mesh;

	SpringArm->SetupAttachment(Mesh); //Attach yourself to the Mesh (aka the RootComponent)
	Camera->SetupAttachment(SpringArm);

	Mesh->SetSimulatePhysics(true);

	
}

// Called when the game starts or when spawned
void ARollaBallPlayer::BeginPlay()
{
	Super::BeginPlay();

	//Needed to make variables valuse match designer expectations of those to be in hundreds max
	MoveForce *= Mesh->GetMass();
	JumpImpulse *= Mesh->GetMass();

	//Moved the binding to beginPlay as it wasn't working correctly in the constructor
	//Other way to solve: leave in the const., reparent BP class to Actor and back to Player, restore the settings
	Mesh->OnComponentHit.AddDynamic(this, &ARollaBallPlayer::OnHitCustom);
	
}


// Called to bind functionality to input
void ARollaBallPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("MoveForward", this, &ARollaBallPlayer::MoveForwad);
	InputComponent->BindAxis("MoveRight", this, &ARollaBallPlayer::MoveRight);

	InputComponent->BindAction("Jump", IE_Pressed, this, &ARollaBallPlayer::Jump);

}

void ARollaBallPlayer::MoveForwad(float Value)
{
	const FVector Forward = Camera->GetForwardVector() * MoveForce * Value;
	Mesh->AddForce(Forward);
}

void ARollaBallPlayer::MoveRight(float Value)
{
	const FVector Right = Camera->GetRightVector() * MoveForce * Value;
	Mesh->AddForce(Right);
}

void ARollaBallPlayer::Jump()
{
	if (JumpCount >= JumpMaxCount) return;

	Mesh->AddImpulse(FVector(0, 0, JumpImpulse));
	JumpCount++;
}


//Getting the direction of the hit and resetting the JumpCount
void ARollaBallPlayer::OnHitCustom(UPrimitiveComponent* HitComponent, AActor* OtherActor,
									UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	const float HitDirection = Hit.Normal.Z;

	if (HitDirection > 0)
	{
		JumpCount = 0;
	}

}

