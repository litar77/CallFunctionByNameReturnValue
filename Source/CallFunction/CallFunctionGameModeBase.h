// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CallFunctionGameModeBase.generated.h"


USTRUCT()
struct CALLFUNCTION_API FCallMessage
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY()
	FString Name;

	UPROPERTY()
	int Number;

	UPROPERTY()
	FString Message;
};

USTRUCT()
struct CALLFUNCTION_API FFeedBack
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FString Sender;

	 UPROPERTY()
	FString Message;
};

/**
 * 
 */
UCLASS()
class CALLFUNCTION_API ACallFunctionGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	UFUNCTION(Exec)
	FFeedBack CallMe(FCallMessage ReceiveMessage);

	/** 采用CallFunctionByNameWithArguments函数，通过字符串来调用函数，然后返回函数的返回值 */
	UFUNCTION(BlueprintCallable)
	FString CallCallMe(FString ParamString); 

	/** Called by VM to execute a UFunction with a filled in UStruct of parameters */
	virtual void ProcessEvent(UFunction* Function, void* Parms) override;

	UPROPERTY()
	FString ReturnStr;
};
