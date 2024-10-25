// Fill out your copyright notice in the Description page of Project Settings.


#include "LuaCModules/LuaJson.h"
#include "LuaBlueprintFunctionLibrary.h"

ULuaJson::ULuaJson()
{
	Table.Add("to_json", FLuaValue::Function(GET_FUNCTION_NAME_CHECKED(ULuaJson, ToJson)));
	Table.Add("from_json", FLuaValue::Function(GET_FUNCTION_NAME_CHECKED(ULuaJson, FromJson)));
}

FLuaValue ULuaJson::FromJson(FLuaValue Value)
{
	FLuaValue ReturnValue;
	ULuaBlueprintFunctionLibrary::LuaValueFromJson(GetWorld(), GetLuaState(), Value.ToString(), ReturnValue);
	return ReturnValue;
}

FLuaValue ULuaJson::ToJson(FLuaValue Value)
{
	return(ULuaBlueprintFunctionLibrary::LuaValueToJson(Value));
}