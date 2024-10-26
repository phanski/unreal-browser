// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LuaUserDataObject.h"
#include "CustomLuaStateBase.generated.h"

/**
 * 
 */
UCLASS()
class CPP2_API UCustomLuaStateBase : public ULuaState
{
	GENERATED_BODY()
public:
    UCustomLuaStateBase();

    UFUNCTION()
    FLuaValue GetCModuleSingleton(FLuaValue ModuleName);

    UFUNCTION()
    FLuaValue GetLuaModuleSingleton(FLuaValue ModuleName) const;

protected:

    UPROPERTY()
    TMap<TSubclassOf<ULuaUserDataObject>, ULuaUserDataObject*> CModulePtrMap;
    UPROPERTY()
    TMap<FString, TSubclassOf<ULuaUserDataObject>> CModuleClassMap;
    UPROPERTY()
    TSubclassOf<UCustomLuaStateBase> ModuleLoadingClass;
};
