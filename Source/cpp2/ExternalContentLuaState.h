 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LuaState.h"
#include "ExternalContentLuaState.generated.h"


 /**
 * 
 */
UCLASS()
class CPP2_API UExternalContentLuaState : public ULuaState
{
	GENERATED_BODY()
	
public:
	UExternalContentLuaState();

	UFUNCTION()
	FLuaValue SetActorLocation(FLuaValue Actor, FLuaValue Location);
	
	UFUNCTION()
	FLuaValue GetActorLocation(FLuaValue Actor);

	UFUNCTION()
	FLuaValue SpawnNewActor(FLuaValue Location, FLuaValue Scale, FLuaValue AssetName, FLuaValue ActorName);

	UFUNCTION()
	FLuaValue SpawnNewActorFull(FLuaValue Location, FLuaValue Scale, FLuaValue AssetName, FLuaValue ActorName);

	UFUNCTION()
	FLuaValue GetGlobalActor(FLuaValue name);

	UFUNCTION()
	FLuaValue CreateOrbitCamera(FLuaValue Centre, FLuaValue Distance);

	UFUNCTION()
	TWeakObjectPtr<UglTFRuntimeAsset>  LoadglTFAsset(FString path);

	UFUNCTION()
	FLuaValue PreloadAssets(TArray<FLuaValue> Assets);

	UFUNCTION()
	FLuaValue AssignOnKeyPressedEvent(FLuaValue KeyName, FLuaValue Callback);

	UFUNCTION()
	FLuaValue DeleteActor(FLuaValue Actor);


protected:
	const FString BaseglTFLocalPath = FString("C:/Users/niami/Documents/assets/");

	UPROPERTY()
	TMap<FString, TWeakObjectPtr<UglTFRuntimeAsset>> glTFCache;

	TMap<FKey, TSharedPtr<FLuaSmartReference>> OnKeyDownCallbacks;
	 
	void OnKeyDownCallback(FKey key);

};
