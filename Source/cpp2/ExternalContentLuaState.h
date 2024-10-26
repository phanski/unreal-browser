 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomLuaStateBase.h"
#include "ExternalContentLuaState.generated.h"


 /**
 * 
 */
UCLASS()
class CPP2_API UExternalContentLuaState : public UCustomLuaStateBase
{
	GENERATED_BODY()
	
public:
	UExternalContentLuaState();

	

	UFUNCTION()
	FLuaValue CreateOrbitCamera(FLuaValue Centre, FLuaValue Distance);



	UFUNCTION()
	FLuaValue PreloadAssets(TArray<FLuaValue> Assets);

	UFUNCTION()
	FLuaValue AssignOnKeyPressedEvent(FLuaValue KeyName, FLuaValue Callback);



protected:

	

	TMap<FKey, TSharedPtr<FLuaSmartReference>> OnKeyDownCallbacks;
	 
	void OnKeyDownCallback(FKey key);

};
