// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LuaComponent.h"
#include "LuaInitialLoader.generated.h"

/**
 * 
 */
UCLASS()
class CPP2_API ULuaInitialLoader : public ULuaComponent
{
	GENERATED_BODY()
	

protected:
	UFUNCTION()
	virtual void BeginPlay() override;

};
