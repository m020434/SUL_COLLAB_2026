
//Generated
#include "PlayerCharacter.h"
#include "GameFramework/PawnMovementComponent.h"
//Components
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SUL_COLLAB_2026/Component/HealthComponent.h"
//Other
#include "SUL_COLLAB_2026/Weapon/Weapon.h"
#include "InputAction.h"
#include "SUL_COLLAB_2026/GameLogic/GameManager.h"
//Libraries
#include "Kismet/KismetMathLibrary.h"
#include "SUL_COLLAB_2026/DEBUG/DB.h"
#include "SUL_COLLAB_2026/GameLogic/GameManagement.h"



#pragma region Initialisation
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
		
		this->OnDestroyed.AddDynamic(this, &APlayerCharacter::OnCharDestroyed);
	}
	
	void APlayerCharacter::OnCharDestroyed(AActor* actor)
	{
		//Clean up our objects
		if(Gun != nullptr)
		{
			Gun->Destroy();
		}
	}
	
	// Called when the game starts or when spawned
	void APlayerCharacter::BeginPlay()
	{
		Super::BeginPlay();
	
		StoredFriction = GetCharacterMovement()->GroundFriction;
		StoredGravityScale = GetCharacterMovement()->GravityScale;
		
		HealthComp->OnDead.AddDynamic(this, &APlayerCharacter::OnDeath); 
	}

	// Called to bind functionality to input
	void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
	{
		Super::SetupPlayerInputComponent(PlayerInputComponent);

		if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
		{
			#pragma region Movement
				EIC->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, FName("DoMove"));
				EIC->BindAction(MoveInputAction,ETriggerEvent::Completed, this, FName("StopMove"));
				EIC->BindAction(LookInputAction, ETriggerEvent::Triggered, this, FName("DoLook"));
				EIC->BindAction(JumpInputAction, ETriggerEvent::Started, this, FName("DoJumpUp"));
				
				//Dash
				EIC->BindAction(DashInputAction, ETriggerEvent::Started, this, FName("DoDash"));
				EIC->BindAction(DashInputAction, ETriggerEvent::Completed, this, FName("StopDash"));
				
				//Slide
				EIC->BindAction(SlideInputAction, ETriggerEvent::Started, this, FName("DoSlide"));
				EIC->BindAction(SlideInputAction, ETriggerEvent::Completed, this, FName("StopSlide"));
			#pragma endregion
			
			//Gun
			EIC->BindAction(ShootInputAction, ETriggerEvent::Triggered, this, FName("DoShoot"));
			EIC->BindAction(ReloadInputAction, ETriggerEvent::Started, this, FName("DoReload"));
		}
	}
#pragma endregion

#pragma region Shooting
	bool APlayerCharacter::CheckHasGun() //Error if we lack a gun.
	{
		if(Gun == nullptr)
		{
			GEngine->AddOnScreenDebugMessage(2, 1, FColor::Red, "No Gun");
			return false;
		}
		
		return true;
	}

	void APlayerCharacter::DoShoot_Implementation(bool Input)
	{
		if(!CheckHasGun()) return;
		Gun->Shoot();
	}

	void APlayerCharacter::DoReload_Implementation(bool Input)
	{
		if(!CheckHasGun()) return;		
		Gun->Reloading();
	}
#pragma endregion

#pragma region Slide
	bool APlayerCharacter::CheckCanSlide()
	{
		return PlayerMovementState == PlayerMovementState::Walk && !GetCharacterMovement()->IsFalling() && PlayerInputDirection.X > 0 && CanSlide;
	}

	void APlayerCharacter::DoSlide_Implementation(bool Input)
	{
		if(!CheckCanSlide()) return;
		
		PlayerSlideHeld = true;
		Slide();
	}

	void APlayerCharacter::Slide_Implementation()
	{
		#pragma region Slide & Brake forces
			//Calculate Force Dir
			FVector Force = (GetActorForwardVector() * PlayerInputDirection.X) + (GetActorRightVector() * PlayerInputDirection.Y);
			Force = UKismetMathLibrary::Normal(Force);
			
			//scale by designer value, always downward
			Force *= SlideForce;
			Force.Z = -1;
			SlidingForce = Force; //TODO: "SlidingForce" and "SlideForce" are 2 completely different variables. The name needs to be improved (e.g. SlideForceVec)
			
			//Brake opposite our slide, always down still.
			BrakingForce = -SlidingForce*0.1f;
			BrakingForce.Z = -1;
			//NOTE: Slightly different behaviour from before, but I'm pretty sure the previous was a mistake & this still works fine in testing.
		#pragma endregion
		
		//Set state
		CanSlide = false;
		MinSlide = false;
		PlayerMovementState = PlayerMovementState::Slide;
		LastSlideHeight = GetActorLocation().Z; //For calculating height delta in update
		
		//Set slide values
		GetCharacterMovement()->GroundFriction = 0.5f;	//TODO: Magic number, that 0.5f should be a designer-exposed variable
		GetCharacterMovement()->AddForce(Force);

		//Set Timers
		//TODO: Shouldn't this start when our slide ends (if we even want a cooldown)?
		GetWorldTimerManager().SetTimer(SlideCooldownTimer, this, &APlayerCharacter::ResetSlide, SlideCooldownTime); //Delay until we can slide again.
		GetWorldTimerManager().SetTimer(EndSlideTimer, this, &APlayerCharacter::ReachMinimumSlide, MinSlideTime);
		GetWorldTimerManager().SetTimer(SlideTimer, this, &APlayerCharacter::UpdateSlide,GetWorld()->GetDeltaSeconds(), true);
		
		if(OnSlideStart.IsBound())
		{
			OnSlideStart.Broadcast();
		}
	}
	
	void APlayerCharacter::UpdateSlide()
	{
		float ChangeinHeight = GetActorLocation().Z - LastSlideHeight;
	
		//Brake if we've gone upwards, apply slide force otherwise.
		if (ChangeinHeight > 0.001f)
		{
			GetCharacterMovement()->AddForce(BrakingForce * ChangeinHeight);
		}
		else if (ChangeinHeight < -0.001f && !GetCharacterMovement()->IsFalling())
		{
			GetCharacterMovement()->AddForce(SlidingForce);
		}
	
		LastSlideHeight = GetActorLocation().Z;
	}

	void APlayerCharacter::EndSlide()
	{
		/*		// ?
		FRotator MoveDirection = FRotator(0.0f, GetControlRotation().Yaw, GetControlRotation().Roll);
		GetMovementComponent()->AddInputVector(MoveDirection.RotateVector(FVector::ForwardVector) * PlayerInputDirection.X);
		GetMovementComponent()->AddInputVector(MoveDirection.RotateVector(FVector::RightVector) * PlayerInputDirection.Y);
		*/
		
		//Reset state
		GetCharacterMovement()->GroundFriction = StoredFriction;
		PlayerMovementState = PlayerMovementState::Walk;
		GetWorldTimerManager().PauseTimer(SlideTimer);
		
		if(OnSlideEnd.IsBound())
		{
			OnSlideEnd.Broadcast();
		}
	}

	void APlayerCharacter::ReachMinimumSlide()
	{
		MinSlide = true;
		if(!PlayerSlideHeld)	//TODO: Would be better if this & StopSlide were a method
		{
			EndSlide();
		}
	}

	void APlayerCharacter::StopSlide_Implementation()
	{
		PlayerSlideHeld = false;
		if (PlayerMovementState == PlayerMovementState::Slide && MinSlide) //TODO: Would be better if this & ReachMinimumSlide were a method
		{
			EndSlide();
		}
	}
	
	void APlayerCharacter::ResetSlide() //End of cooldown
	{
			CanSlide = true;
	}
#pragma endregion

#pragma region Dash
	// The response to the dash input Press
	void APlayerCharacter::DoDash_Implementation(bool Input)
	{
		if(!(PlayerMovementState == PlayerMovementState::Walk && CanDash && GetCharacterMovement()->MovementMode != MOVE_Walking) ) return;
		
		Dash();
	}
	
	//Dash cancels all existing momentum and launches the player in the direction they're moving (or directly forward if they aren't moving)
	void APlayerCharacter::Dash_Implementation()
	{
		//Set State
		CanDash = false;
		PlayerMovementState = PlayerMovementState::Dash;
		
		//Values to reset to
		StoredSpeed = GetCharacterMovement()->Velocity.Size();
		
		//Kill velocity / gravity
		GetCharacterMovement()->Velocity = FVector(0, 0, 0);
		GetCharacterMovement()->GravityScale = 0;

		#pragma region Calculate Dash Force
			FVector PlayerVelocity = FVector::Zero();
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
		#pragma endregion
		
		LaunchCharacter(PlayerVelocity, false, false);
		
		GetWorldTimerManager().SetTimer(DashTimer, this, &APlayerCharacter::EndDash, DashTime);
	}

	// End the dash, Reset velocity, turn on gravity, set a cooldown timer
	void APlayerCharacter::EndDash()
	{
		//Return to the speed we had before dashing, but in our new direction.
		FVector VelNormal = UKismetMathLibrary::Normal(GetCharacterMovement()->Velocity);
		GetCharacterMovement()->Velocity = VelNormal*StoredSpeed;
		
		//Reset state
		GetCharacterMovement()->GravityScale = StoredGravityScale;
		PlayerMovementState = PlayerMovementState::Walk;
		
		//Cooldown
		//GetWorldTimerManager().SetTimer(DashCooldownTimer, this, &APlayerCharacter::ResetDash, DashCooldownTime);
	}

	// Reset the dash so the player can dash again
	void APlayerCharacter::ResetDash()
	{
		CanDash = true;
	}

	void APlayerCharacter::StopDash_Implementation()
	{
	}
#pragma endregion

#pragma region General Movement/Input
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
	// Set the player input to zero for the dashes
	void APlayerCharacter::StopMove_Implementation(FVector2D Input)
	{
		PlayerInputDirection = FVector2D::Zero();
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
		Jump();	
		if (PlayerMovementState == PlayerMovementState::Slide)
			EndSlide();
	}
#pragma endregion


void APlayerCharacter::OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PreviousMovementMode, PreviousCustomMode);
	
	if(GetCharacterMovement()->MovementMode == MOVE_Walking)
	{
		ResetDash();
	}
}

void APlayerCharacter::OnDeath()
{
	UGameManager* manager = UGameManagement::GetGameManager();
	manager->OnPlayerDied(this);
}
