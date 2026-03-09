
#include "PlayerCharacter.h"

#include "GameFramework/PawnMovementComponent.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SUL_COLLAB_2026/Component/HealthComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CamComp->SetupAttachment(GetRootComponent());
	CamComp->SetRelativeLocation(FVector(50, 0, 50));

	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	
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
		EIC->BindAction(DashInputAction, ETriggerEvent::Started, this, FName("DoDash"));
	}
}

void APlayerCharacter::EndDash()
{
	GetCharacterMovement()->GravityScale = StoredGravityScale;
	InDash = false;
	GetWorldTimerManager().SetTimer(DashCooldownTimer, this, &APlayerCharacter::ResetDash, DashCooldownTime);

}

void APlayerCharacter::ResetDash()
{
	GEngine->AddOnScreenDebugMessage(3, 0.5f, FColor::Red, "DashReset");

	CanDash = true;
}

void APlayerCharacter::Dash_Implementation()
{
	GetCharacterMovement()->Velocity = FVector(0, 0, 0);
	GetCharacterMovement()->GravityScale = 0;
	FVector PlayerVelocity = GetActorForwardVector() * DashSpeed;
	PlayerVelocity.Z = 0;
	LaunchCharacter(PlayerVelocity, false, false);
	GEngine->AddOnScreenDebugMessage(2, 1.5f, FColor::Red, PlayerVelocity.ToString());
	
}

void APlayerCharacter::DoDash_Implementation(bool Input)
{
	if (CanDash)
	{
		StoredSpeed = GetCharacterMovement()->Velocity.Size();
		StoredGravityScale = GetCharacterMovement()->GravityScale;
		GEngine->AddOnScreenDebugMessage(1, 0.5f, FColor::Red, "Do Dash");
		CanDash = false;
		InDash = true;
		Dash();
		GetWorldTimerManager().SetTimer(DashTimer, this, &APlayerCharacter::EndDash, DashTime);

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






