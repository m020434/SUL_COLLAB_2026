
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SUL_COLLAB_2026/BaseWildcard.h"
#include "PlayerCharacter.generated.h"

class AWeapon;
class UCameraComponent;
class UInputAction;
class UHealthComponent;

UENUM(BlueprintType)
enum PlayerMovementState
{
	Walk UMETA(DisplayName = "Walk"),
	Slide UMETA(DisplayName = "Slide"),
	Dash UMETA(DisplayName = "Dash")
};


UCLASS()
class SUL_COLLAB_2026_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCameraComponent* CamComp;
	

	// Input
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")	
	UInputAction* MoveInputAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")	
	UInputAction* LookInputAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")	
	UInputAction* JumpInputAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	UInputAction* DashInputAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	UInputAction* ShootInputAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	UInputAction* ReloadInputAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	UInputAction* SlideInputAction;

	
	// Health Component
	UPROPERTY(BlueprintReadOnly)
	UHealthComponent* HealthComp;

	// Modifier for the Dash
	UPROPERTY(VisibleAnywhere, Category = "Dash")
	FTimerHandle DashTimer;
	UPROPERTY(VisibleAnywhere, Category = "Dash")
	FTimerHandle DashCooldownTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
	float DashTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
	float DashSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
	float DashCooldownTime;

	// Modifier for the Dash
	UPROPERTY(VisibleAnywhere, Category = "Slide")
	FTimerHandle SlideTimer;
	UPROPERTY(VisibleAnywhere, Category = "Slide")
	FTimerHandle EndSlideTimer;
	UPROPERTY(VisibleAnywhere, Category = "Slide")
	FTimerHandle SlideCooldownTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slide")
	float MinSlideTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slide")
	float SlideForce;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slide")
	float SlideCooldownTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float DefaultHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
	AWeapon* Gun;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gun")
	bool HaveGun = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WildCard")
	ABaseWildcard* WildCard;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
	// Allow the player to have the reference to move input and movement button.
	// Used for the dash and Slide
	FVector2D PlayerInputDirection = FVector2D::Zero();
	bool PlayerMovementAction = false;

	// Variable that allow the player to know if they can use the dash
	bool CanDash = true;

	// Player Movement State
	PlayerMovementState PlayerMovementState = PlayerMovementState::Walk;

	// Variable for dash.
	float StoredSpeed;
	float StoredGravityScale;
	FVector PlayerVelocity = FVector::Zero();

	// Variable for Slide for player Designer
	bool MinSlide = false;
	bool CanSlide = true;
	float StoredFriction;
	float SlideTimeOnFloor = 0;
	FVector SlidingForce;
	FVector BrakingForce;
	FHitResult HitResultOfGround;
	float SlideHeight;
	
public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	#pragma region Movement Methods
		//Generic Movement Inputs
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void DoMove(FVector2D Input);
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void StopMove(FVector2D Input);
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void DoLook(FVector2D Input);
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void DoJumpUp(bool Input);
		
		//Input to dash/slide
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void DoDash(bool Input);
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void StopDash();
		
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void DoSlide(bool Input);
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void StopSlide();
		
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void Dash();
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void Slide();

		UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void ChangeToSlideHeight();
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void ChangeToDefaultHeight();
		
		//Dash methods
		void EndDash();
		void ResetDash();

		//Slide methods
		void CheckSlide();
		void EndSlide();
		void ReachMinimumSlide();
		void ResetSlide();
	#pragma endregion

	#pragma region Gun Methods
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void DoShoot(bool Input);
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void DoReload(bool Input);
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void CreateGun();
	#pragma endregion

	
};
