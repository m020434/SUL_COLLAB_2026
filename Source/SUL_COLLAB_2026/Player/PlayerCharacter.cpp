
#include "PlayerCharacter.h"
#include "GameFramework/PawnMovementComponent.h"
#include "InputAction.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetStringLibrary.h"
#include "SUL_COLLAB_2026/Component/HealthComponent.h"
#include "SUL_COLLAB_2026/Weapon/Weapon.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a Camera Component
	CamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CamComp->SetupAttachment(GetRootComponent());
	CamComp->SetRelativeLocation(FVector(40, 0, 50));

	// Add the Health Component
	HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
	
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	StoredFriction = GetCharacterMovement()->GroundFriction;
	DefaultHeight = GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
	StoredGravityScale = GetCharacterMovement()->GravityScale;
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
		EIC->BindAction(MoveInputAction,ETriggerEvent::Completed, this, FName("StopMove"));
		EIC->BindAction(LookInputAction, ETriggerEvent::Triggered, this, FName("DoLook"));
		EIC->BindAction(JumpInputAction, ETriggerEvent::Started, this, FName("DoJumpUp"));
		EIC->BindAction(DashInputAction, ETriggerEvent::Started, this, FName("DoDashNSlide"));
		EIC->BindAction(DashInputAction, ETriggerEvent::Completed, this, FName("StopDashNSlide"));
		EIC->BindAction(ShootInputAction, ETriggerEvent::Triggered, this, FName("DoShoot"));
		EIC->BindAction(ReloadInputAction, ETriggerEvent::Started, this, FName("DoReload"));

	}
}

void APlayerCharacter::DoShoot_Implementation(bool Input)
{
	if (Gun != nullptr)
	{
		Gun->Shoot();
	}

	else
	{
		GEngine->AddOnScreenDebugMessage(2, 1, FColor::Red, "No Gun");
	}
	
}

// Set the player input to zero for the dashes
void APlayerCharacter::StopMove_Implementation(FVector2D Input)
{
	PlayerInputDirection = FVector2D::Zero();
}

void APlayerCharacter::Slide_Implementation()
{
	FVector Force = (GetActorForwardVector() * PlayerInputDirection.X) + (GetActorRightVector() * PlayerInputDirection.Y);
	Force = UKismetMathLibrary::Normal(Force);
	BrakingForce = -Force;
	Force.Z = -1;
	Force = Force*SlideForce;
	SlidingForce = Force * 0.05f;
	BrakingForce.Z = -10;
	BrakingForce = BrakingForce *SlideForce * 0.005f;
	MinSlide = false;
	SlideTimeOnFloor = 0;
	GetCharacterMovement()->GroundFriction = 0.5f;
	ChangeToSlideHeight();
	GetCharacterMovement()->AddForce(Force);
	GetWorldTimerManager().SetTimer(SlideCooldownTimer, this, &APlayerCharacter::ResetSlide, SlideCooldownTime);

}

void APlayerCharacter::ChangeToSlideHeight_Implementation()
{
	
}

void APlayerCharacter::ChangeToDefaultHeight_Implementation()
{
	
}

void APlayerCharacter::DoReload_Implementation(bool Input)
{
	if (Gun != nullptr)
	{
		Gun->Reloading();
	}

	else
	{
		GEngine->AddOnScreenDebugMessage(2, 1, FColor::Red, "No Gun");
	}
}



// End the dash, Reset velocity, turn on gravity, set a cooldown timer
void APlayerCharacter::EndDash()
{
	FVector Velocity = UKismetMathLibrary::Normal(GetCharacterMovement()->Velocity);
	GetCharacterMovement()->Velocity = Velocity*StoredSpeed;
	GetCharacterMovement()->GravityScale = StoredGravityScale;
	PlayerMovementState = PlayerMovementState::Walk;
	GetWorldTimerManager().SetTimer(DashCooldownTimer, this, &APlayerCharacter::ResetDash, DashCooldownTime);
	
}

// Reset the dash so the player can dash again
void APlayerCharacter::ResetDash()
{
	CanDash = true;
}

void APlayerCharacter::CheckSlide()
{
	float ChangeinHeight = GetActorLocation().Z - SlideHeight;
	
	if (ChangeinHeight> 0.001f)
	{
		GetCharacterMovement()->AddForce(BrakingForce * ChangeinHeight);
	}

	if (ChangeinHeight < -0.001f&& !GetCharacterMovement()->IsFalling())
	{
		GetCharacterMovement()->AddForce(SlidingForce);
	}
	
	SlideHeight = GetActorLocation().Z;
}

void APlayerCharacter::EndSLide()
{
	if (MinSlide && !PlayerMovementAction)
	{
		FRotator MoveDirection = FRotator(0.0f, GetControlRotation().Yaw, GetControlRotation().Roll);
		GetCharacterMovement()->GravityScale = StoredGravityScale;
		GetMovementComponent()->AddInputVector(MoveDirection.RotateVector(FVector::ForwardVector) * PlayerInputDirection.X);
		GetMovementComponent()->AddInputVector(MoveDirection.RotateVector(FVector::RightVector) * PlayerInputDirection.Y);
		ChangeToDefaultHeight();
		GetCharacterMovement()->GroundFriction = StoredFriction;
		PlayerMovementState = PlayerMovementState::Walk;
		GetWorldTimerManager().PauseTimer(SlideTimer);
	}
}


void APlayerCharacter::ReachMinimumSlide()
{
	MinSlide = true;
	EndSLide();
}

void APlayerCharacter::ResetSlide()
{
	CanSlide = true;
}


// Dash, Calculated the velocity for the dash depending on the input pressed and turning of gravity so all other force
// does not affect the dash.
void APlayerCharacter::Dash_Implementation()
{
	GetCharacterMovement()->Velocity = FVector(0, 0, 0);
	GetCharacterMovement()->GravityScale = 0;

	if (PlayerInputDirection != FVector2D::Zero())
	{
		FVector Velocity = (GetActorForwardVector() * PlayerInputDirection.X) + (GetActorRightVector() * PlayerInputDirection.Y);
		PlayerVelocity = UKismetMathLibrary::Normal(Velocity) * DashSpeed;
	}

	else
	{
		PlayerVelocity = GetActorForwardVector() * DashSpeed;
	}
	
	PlayerVelocity.Z = 0;
	LaunchCharacter(PlayerVelocity, false, false);
	
}

// The response to the dash input Press
void APlayerCharacter::DoDashNSlide_Implementation(bool Input)
{
	
	if (PlayerMovementState == PlayerMovementState::Walk)
	{

		if (!GetCharacterMovement()->IsFalling() && PlayerInputDirection.X > 0)
		{
			PlayerMovementAction = true;
			if (CanSlide)
			{
				PlayerMovementState = PlayerMovementState::Slide;
				SlideHeight = GetActorLocation().Z;
				CanSlide = false;
				Slide();
				GetWorldTimerManager().SetTimer(EndSlideTimer, this, &APlayerCharacter::ReachMinimumSlide, MinSlideTime);
				GetWorldTimerManager().SetTimer(SlideTimer, this, &APlayerCharacter::CheckSlide,GetWorld()->GetDeltaSeconds(), true);
			}
		}
		else
		{
			if (CanDash)
			{
				StoredSpeed = GetCharacterMovement()->Velocity.Size();
				CanDash = false;
				PlayerMovementState = PlayerMovementState::Dash;
				Dash();
				GetWorldTimerManager().SetTimer(DashTimer, this, &APlayerCharacter::EndDash, DashTime);
			}

		}
	}
}

void APlayerCharacter::StopDashNSlide_Implementation()
{
	PlayerMovementAction = false;
	if (PlayerMovementState == PlayerMovementState::Slide)
	{
		EndSLide();
	}
	
}

// Move the player
void APlayerCharacter::DoMove_Implementation(FVector2D Input)
{
	PlayerInputDirection = Input;
	if (PlayerMovementState != PlayerMovementState::Slide)
	{
		FRotator MoveDirection = FRotator(0.0f, GetControlRotation().Yaw, GetControlRotation().Roll);
	
		GetMovementComponent()->AddInputVector(MoveDirection.RotateVector(FVector::ForwardVector) * Input.X);
		GetMovementComponent()->AddInputVector(MoveDirection.RotateVector(FVector::RightVector) * Input.Y);
	}
}

// Change the direction the player is facing
void APlayerCharacter::DoLook_Implementation(FVector2D Input)
{
	AddControllerYawInput(Input.X);
	AddControllerPitchInput(Input.Y);
}

// Make the player Jump
void APlayerCharacter::DoJumpUp_Implementation(bool Input)
{
	if (PlayerMovementState != PlayerMovementState::Slide)
	{
		Jump();	
	}
}


