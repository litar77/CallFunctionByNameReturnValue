// Copyright Epic Games, Inc. All Rights Reserved.


#include "CallFunctionGameModeBase.h"
PRAGMA_DISABLE_OPTIMIZATION
FFeedBack ACallFunctionGameModeBase::CallMe(FCallMessage ReceiveMessage)
{
	UE_LOG(LogTemp,Warning,TEXT("Recieve Message %s"), *ReceiveMessage.Message);
	FFeedBack fb;
	fb.Sender=TEXT("TDY");
	fb.Message=FString::Printf(TEXT("Hello,%s,your Number is %d"), *ReceiveMessage.Name, ReceiveMessage.Number);
	return fb;
}

FString ACallFunctionGameModeBase::CallCallMe(FString ParamString)
{
	FString FuncName = TEXT("CallMe ") + ParamString;
	CallFunctionByNameWithArguments(*FuncName, *GLog, NULL, true);
	return ReturnStr;
}



void ACallFunctionGameModeBase::ProcessEvent(UFunction* Function, void* Parms)
{
	Super::ProcessEvent(Function, Parms);

	FString FuncName;
	Function->GetName(FuncName);
	if (FuncName.Compare(TEXT("CallMe")) == 0)
	{
		//处理函数调用返回值
		const bool bHasReturnParam = Function->ReturnValueOffset != MAX_uint16;
		if (bHasReturnParam)
		{
			uint8* ReturnValueAddress = ((uint8*)Parms + Function->ReturnValueOffset);

			// find the last parameter
			FProperty* Parameter = nullptr;
			for (TFieldIterator<FProperty> ParamIt(Function); ParamIt; ++ParamIt)
			{
				Parameter = *ParamIt;
				// Skip the return value; it never has data on the bytecode stack and was added to the output params chain before this loop
				if (Parameter->HasAnyPropertyFlags(CPF_ReturnParm))
				{
					ReturnStr.Empty();
					Parameter->ExportTextItem(ReturnStr, ReturnValueAddress, nullptr, nullptr, PPF_None);
					break;
				}
			}

			//GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Yellow, ReturnStr);
		}
	}
	
}
PRAGMA_ENABLE_OPTIMIZATION
