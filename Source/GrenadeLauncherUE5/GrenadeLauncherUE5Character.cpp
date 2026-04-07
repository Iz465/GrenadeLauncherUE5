// Copyright Epic Games, Inc. All Rights Reserved.

#include "GrenadeLauncherUE5Character.h"
#include "GrenadeLauncherUE5Projectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "Weapons.h"
#include "WeaponsComponent.h"
#include "LifeComponent.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AGrenadeLauncherUE5Character

AGrenadeLauncherUE5Character::AGrenadeLauncherUE5Character()
{
	// Character doesnt have a rifle at start

	bHasRifle = false;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	weaponsComponent = CreateDefaultSubobject<UWeaponsComponent>(TEXT("WeaponsComponent"));
	lifeComponent = CreateDefaultSubobject<ULifeComponent>(TEXT("LifeComponent"));

}






void AGrenadeLauncherUE5Character::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

}

void AGrenadeLauncherUE5Character::Destroyed()
{
	Super::Destroyed();
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Black, TEXT("Player has died!"));
}

//////////////////////////////////////////////////////////////////////////// Input

void AGrenadeLauncherUE5Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGrenadeLauncherUE5Character::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGrenadeLauncherUE5Character::Look);

		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AGrenadeLauncherUE5Character::Interact);

		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &AGrenadeLauncherUE5Character::StartFire);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Completed, this, &AGrenadeLauncherUE5Character::StopFire);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}


void AGrenadeLauncherUE5Character::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AGrenadeLauncherUE5Character::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AGrenadeLauncherUE5Character::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool AGrenadeLauncherUE5Character::GetHasRifle()
{
	return bHasRifle;
}

void AGrenadeLauncherUE5Character::Interact()
{


	if (!FirstPersonCameraComponent) return;
	FVector startLocation = FirstPersonCameraComponent->GetComponentLocation();
	FVector endLocation = (FirstPersonCameraComponent->GetForwardVector() * 500) + startLocation;
	FHitResult result;
	if (GetWorld()->LineTraceSingleByChannel(result, startLocation, endLocation, ECC_GameTraceChannel2))
	{
		DrawDebugLine(GetWorld(), startLocation, endLocation, FColor::Green, true);



		AWeapons* weapon = Cast<AWeapons>(result.GetActor());
		if (!weapon) return;
		FWeaponInfo weaponInfo;
		weapon->AttachToComponent(Mesh1P, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("hand_r"));
		weapon->SetActorRelativeLocation(weaponInfo.location);
		weapon->SetActorRelativeRotation(weaponInfo.rotation);

		weaponsComponent->weapon = weapon;
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Purple,result.GetActor()->GetName());

	
	}
		
	else
		DrawDebugLine(GetWorld(), startLocation, endLocation, FColor::Red, true);


}


void AGrenadeLauncherUE5Character::StartFire() {	if (!weaponsComponent) return; weaponsComponent->StartFire(); }
void AGrenadeLauncherUE5Character::StopFire() { if (!weaponsComponent) return; weaponsComponent->StopFire(); }



