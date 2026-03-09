
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"


class UCameraComponent;
class UInputAction;
class UHealthComponent;

UCLASS()
class SUL_COLLAB_2026_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCameraComponent* CamComp;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")	
	UInputAction* MoveInputAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")	
	UInputAction* LookInputAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")	
	UInputAction* JumpInputAction;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Input")
	UInputAction* DashInputAction;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UHealthComponent* HealthComp;

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
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool CanDash = true;
	bool InDash = false;
	float StoredSpeed;
	float StoredGravityScale;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DoMove(FVector2D Input);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DoLook(FVector2D Input);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DoJumpUp(bool Input);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DoDash(bool Input);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Dash();

	void EndDash();
	void ResetDash();
};
