
#include "PlayerCharacter.h"

#include "GameFramework/PawnMovementComponent.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CamComp->SetupAttachment(GetRootComponent());
	CamComp->SetRelativeLocation(FVector(50, 0, 50));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EIC->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, FName("DoMove"));
		EIC->BindAction(LookInputAction, ETriggerEvent::Triggered, this, FName("DoLook"));
		EIC->BindAction(JumpInputAction, ETriggerEvent::Started, this, FName("DoJumpUp"));
	}
}


void APlayerCharacter::DoMove_Implementation(FVector2D Input)
{
	FRotator MoveDirection = FRotator(0.0f, GetControlRotation().Yaw, GetControlRotation().Roll);
	
	GetMovementComponent()->AddInputVector(MoveDirection.RotateVector(FVector::ForwardVector) * Input.X);
	GetMovementComponent()->AddInputVector(MoveDirection.RotateVector(FVector::RightVector) * Input.Y);
}

void APlayerCharacter::DoLook_Implementation(FVector2D Input)
{
	AddControllerYawInput(Input.X);
	AddControllerPitchInput(Input.Y);
}

void APlayerCharacter::DoJumpUp_Implementation(bool Input)
{
	Jump();	
}




