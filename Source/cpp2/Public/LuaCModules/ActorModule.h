// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomLuaStateBase.h"
#include "glTFRuntimeAsset.h"
#include "LuaUserDataObject.h"
#include "ActorModule.generated.h"

/**
 * 
 */
UCLASS()
class CPP2_API UActorModule : public ULuaUserDataObject
{
	GENERATED_BODY()
public:
	UActorModule();

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
	FLuaValue DeleteActor(FLuaValue Actor);

	UFUNCTION()
	TWeakObjectPtr<UglTFRuntimeAsset>  LoadglTFAsset(FString path);
private:
	const FString BaseglTFLocalPath = FString("C:/Users/niami/Documents/assets/");
	UPROPERTY()
	TMap<FString, TWeakObjectPtr<UglTFRuntimeAsset>> glTFCache;

	UPROPERTY()
	TSubclassOf<UCustomLuaStateBase> ParentState;
};
