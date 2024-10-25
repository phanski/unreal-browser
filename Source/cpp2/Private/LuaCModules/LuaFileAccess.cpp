// Fill out your copyright notice in the Description page of Project Settings.


#include "LuaCModules/LuaFileAccess.h"

ULuaFileAccess::ULuaFileAccess() {
    Table.Add("write_file", FLuaValue::Function(GET_FUNCTION_NAME_CHECKED(ULuaFileAccess, WriteToFile)));
}

FLuaValue ULuaFileAccess::WriteToFile(FLuaValue contentFilePath, FLuaValue data)
{
    return FFileHelper::SaveStringToFile(data.String, *FPaths::Combine(FPaths::ProjectContentDir(), contentFilePath.String));
}
