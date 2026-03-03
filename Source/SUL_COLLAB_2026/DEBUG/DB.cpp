#include "DB.h"

#pragma region Print
	void UDB::Print(const AActor* obj)
	{
		UDB::Print(obj->GetName());
	}

	void UDB::Print( const FString& str)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *str);
	}

	void UDB::Print( const char* str)
	{
		UE_LOG(LogTemp, Warning, TEXT("%hs"), str);
	}

	void UDB::Print(const FVector& vec)
	{
		UE_LOG(LogTemp, Warning, TEXT("%f %f %f"), vec.X, vec.Y, vec.Z);
	}

	void UDB::Print(const float& numFloat)
	{
		UE_LOG(LogTemp, Warning, TEXT("%f"), numFloat);
	}

	void UDB::Print(const double& numDoub)
	{
		UE_LOG(LogTemp, Warning, TEXT("%f"), numDoub);
	}

	void UDB::Print(const int& numInt)
	{
		UE_LOG(LogTemp, Warning, TEXT("%d"), numInt);
	}

	void UDB::Print(const bool& bValue)
	{
		//TODO: Could be wrong.
		UE_LOG(LogTemp, Warning, TEXT("%hhd"), bValue);
	}
#pragma endregion