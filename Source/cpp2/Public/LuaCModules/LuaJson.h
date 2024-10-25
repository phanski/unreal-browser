// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LuaUserDataObject.h"
#include "LuaJson.generated.h"

/**
 * 
 */
UCLASS()
class CPP2_API ULuaJson : public ULuaUserDataObject
{
	GENERATED_BODY()
public:
	ULuaJson();

	UFUNCTION()
	FLuaValue ToJson(FLuaValue Value);

	UFUNCTION()
	FLuaValue FromJson(FLuaValue Value);
};
