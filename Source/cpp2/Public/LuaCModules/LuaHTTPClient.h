// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LuaUserDataObject.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"

#include "LuaHTTPClient.generated.h"

/**
 * 
 */
UCLASS()
class CPP2_API ULuaHTTPClient : public ULuaUserDataObject
{
	GENERATED_BODY()
public:
	ULuaHTTPClient();
	
	UFUNCTION()
	FLuaValue HttpGetCallback(FLuaValue URL, FLuaValue Callback);
};
