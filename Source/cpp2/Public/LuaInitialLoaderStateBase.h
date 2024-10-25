// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LuaState.h"
#include "LuaInitialLoaderStateBase.generated.h"

/**
 * 
 */
UCLASS()
class CPP2_API ULuaInitialLoaderStateBase : public ULuaState
{
    GENERATED_BODY()
public:
    ULuaInitialLoaderStateBase();

    UFUNCTION()
    FLuaValue GetCModuleSingleton(FLuaValue ModuleName);

    UFUNCTION()
    FLuaValue GetLuaModule(FLuaValue ModuleName) const;

protected:

    UPROPERTY()
    TMap<TSubclassOf<ULuaUserDataObject>, ULuaUserDataObject*> CModulePtrMap;
    UPROPERTY()
    TMap<FString, TSubclassOf<ULuaUserDataObject>> CModuleClassMap;
};