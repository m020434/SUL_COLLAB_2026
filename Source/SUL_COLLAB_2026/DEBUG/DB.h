#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DB.generated.h"


UCLASS()
class SUL_COLLAB_2026_API UDB : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	#pragma region Print
		static void Print(const AActor* obj);
		static void Print( const FString& str );
		static void Print( const char* str );
		static void Print( const FVector& vec );
		static void Print( const float& numFloat );
		static void Print( const double& numDoub );
		static void Print( const int& numInt);
		static void Print( const bool& bValue);
	#pragma endregion
};
