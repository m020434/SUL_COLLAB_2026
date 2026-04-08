
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SUL_COLLAB_2026/BaseWildcard.h"
#include "PlayerCharacter.generated.h"

class AWeapon;
class UCameraComponent;
class UInputAction;
class UHealthComponent;

#pragma region Type Declarations
	//Slide events
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSlideStart);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSlideEnd);

	//State Machine Enum
	UENUM(BlueprintType)
	enum PlayerMovementState
	{
		Walk UMETA(DisplayName = "Walk"),
		Slide UMETA(DisplayName = "Slide"),
		Dash UMETA(DisplayName = "Dash")
	};
#pragma endregion

UCLASS()
class SUL_COLLAB_2026_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	//Initialisation stuff
	APlayerCharacter();

#pragma region Delegates
		UPROPERTY(BlueprintAssignable)
		FOnSlideStart OnSlideStart;
		UPROPERTY(BlueprintAssignable)
		FOnSlideEnd OnSlideEnd;
		
		//TODO: Dash events
	#pragma endregion
	
protected:
	//Initialisation stuff
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION()
	void OnCharDestroyed(AActor* actor);
	
	
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

		//Dash methods
		void EndDash();
		void ResetDash();

		//Slide methods
		bool CheckCanSlide();
		void UpdateSlide();
		void EndSlide();
		void ReachMinimumSlide();
		void ResetSlide();
	#pragma endregion

	#pragma region Gun Methods
		bool CheckHasGun();
		
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void DoShoot(bool Input);
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void DoReload(bool Input);
	#pragma endregion

	#pragma region WildCard Methods
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void DoUseWildCard(bool Input);
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void PickUpWildCard(ABaseWildcard* WildCard);
	#pragma endregion
	
	UFUNCTION()
	void OnDeath();

	// Variable Definitions start here ---------------------------------------------------------------------------------

	#pragma region Components
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UCameraComponent* CamComp;
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UHealthComponent* HealthComp;
		
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Gun")
		AWeapon* Gun;
	#pragma endregion
	
	#pragma region Input
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
		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
		UInputAction* UseWildCardAction;
	#pragma endregion

	#pragma region Dash Designer Variables
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dash")
		FTimerHandle DashTimer;
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dash")
		FTimerHandle DashCooldownTimer;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
		float DashTime;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
		float DashSpeed;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dash")
		float DashCooldownTime;
	#pragma endregion
	
	#pragma region Slide Designer Variables
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Slide")
		FTimerHandle SlideTimer;
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Slide")
		FTimerHandle EndSlideTimer;
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Slide")
		FTimerHandle SlideCooldownTimer;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slide")
		float MinSlideTime;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slide")
		float SlideForce;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slide")
		float SlideCooldownTime;
	#pragma endregion
	
	// Last WASD movement the player received, used for dash and slide.
	FVector2D PlayerInputDirection = FVector2D::Zero();

	// Dash Variables
	bool CanDash = true;
	float StoredSpeed;
	float StoredGravityScale;

	// Player Movement State
	PlayerMovementState PlayerMovementState = PlayerMovementState::Walk;

	// Slide Variables
	bool PlayerSlideHeld = false;
	bool CanSlide = true;
	bool MinSlide = false;
	float StoredFriction;
	FVector SlidingForce;
	FVector BrakingForce;
	float LastSlideHeight;

	// WildCard Variable
	ABaseWildcard* CurrentWildcard;
};
