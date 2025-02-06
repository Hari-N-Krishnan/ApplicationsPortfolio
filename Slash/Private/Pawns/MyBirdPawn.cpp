// Fill out your copyright notice in the Description page of Project Settings.
#include "Pawns/MyBirdPawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
// Sets default values
AMyBirdPawn::AMyBirdPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Capsule->SetCapsuleHalfHeight(20.f);
	Capsule->SetCapsuleRadius(15.f);
	SetRootComponent(Capsule);


	BirdMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BirdMesh"));
	BirdMesh->SetupAttachment(GetRootComponent());  // same as RootComponent or Capsule as it is set as the root component in this instance

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent); // same as GetRootComponent() or Capsule as it is set as the root component in this instance
	SpringArm->TargetArmLength = 115.f;

	BirdCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("BirdCamera"));
	BirdCamera->SetupAttachment(SpringArm); // as camera needs to be attached to the spring arm not the root component(capsule)
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AMyBirdPawn::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController())) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(MyBirdPawnMappingContext, 0);
		}
	}
	
}

void AMyBirdPawn::Move(const FInputActionValue& Value)
{
	const float DirectionValue = Value.Get<float>();
	if (Controller && (DirectionValue != 0.f)) {
		FVector Forward = GetActorForwardVector();
		AddMovementInput(Forward, DirectionValue);
	}
}

void AMyBirdPawn::Look(const FInputActionValue& Value)
{
	const FVector2D LookVector = Value.Get<FVector2D>();
	// Controller is same as GetController() in this instance
	if (Controller) {
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(LookVector.Y);
	}
}

//void AMyBirdPawn::Turn(float Value)
//{
//	AddControllerYawInput(Value);
//}
//
//void AMyBirdPawn::LookUpDown(float Value)
//{
//	AddControllerPitchInput(Value);
//}

// Called every frame
void AMyBirdPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyBirdPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//PlayerInputComponent->BindAxis(FName("Turn"), this, &AMyBirdPawn::Turn);
	//PlayerInputComponent->BindAxis(FName("LookUpDown"), this, &AMyBirdPawn::LookUpDown);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(MyBirdPawnMoveAction, ETriggerEvent::Triggered, this, &AMyBirdPawn::Move);
		EnhancedInputComponent->BindAction(MyBirdPawnLookAction, ETriggerEvent::Triggered, this, &AMyBirdPawn::Look);
	}

}

