// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LuaUserDataObject.h"
#include "LuaFileAccess.generated.h"

/**
 * 
 */
UCLASS()
class CPP2_API ULuaFileAccess : public ULuaUserDataObject
{
	GENERATED_BODY()
	
public:
	ULuaFileAccess();

	UFUNCTION()
	FLuaValue WriteToFile(FLuaValue contentFilePath, FLuaValue data);
};
