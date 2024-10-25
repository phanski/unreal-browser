// Fill out your copyright notice in the Description page of Project Settings.


#include "LuaInitialLoaderStateBase.h"
#include "LuaBlueprintFunctionLibrary.h"
#include "LuaCModules/LuaHTTPClient.h"
#include "LuaCModules/LuaWebsocketConnection.h"
#include "LuaCModules/LuaJson.h"
#include "LuaCModules/LuaFileAccess.h"
#include "HAL/FileManager.h"

ULuaInitialLoaderStateBase::ULuaInitialLoaderStateBase()
{
	Table.Add("get_module", FLuaValue::Function(GET_FUNCTION_NAME_CHECKED(ULuaInitialLoaderStateBase, GetLuaModule)));
	Table.Add("get_internal_module", FLuaValue::Function(GET_FUNCTION_NAME_CHECKED(ULuaInitialLoaderStateBase, GetCModuleSingleton)));

	CModuleClassMap = TMap<FString, TSubclassOf<ULuaUserDataObject>>();
	CModuleClassMap.Add(FString("http"), ULuaHTTPClient::StaticClass());
	CModuleClassMap.Add(FString("websocket"), ULuaWebsocketConnection::StaticClass());
	CModuleClassMap.Add(FString("json"), ULuaJson::StaticClass());
	CModuleClassMap.Add(FString("files"), ULuaFileAccess::StaticClass());
}

FLuaValue ULuaInitialLoaderStateBase::GetCModuleSingleton(FLuaValue ModuleName)
{
	if (!CModuleClassMap.Contains(ModuleName.String)) return FLuaValue();
	const TSubclassOf<ULuaUserDataObject> ModuleClass = CModuleClassMap[ModuleName.String];
	if (!ModuleClass->IsChildOf(ULuaUserDataObject::StaticClass())) return FLuaValue();

	if (!CModulePtrMap.Contains(ModuleClass))
	{
		ULuaUserDataObject* CModule = NewObject<ULuaUserDataObject>(this, ModuleClass);
		CModulePtrMap.Add(ModuleClass, CModule);
	}
	return FLuaValue(CModulePtrMap[ModuleClass]);
}

FLuaValue ULuaInitialLoaderStateBase::GetLuaModule(FLuaValue ModuleName) const
{
	TArray<FLuaValue> Results;
	TArray<FString> Filenames;
	IFileManager::Get().FindFilesRecursive(Filenames, *(FPaths::ProjectContentDir().Append("/lua/Libraries")), *(FString(ModuleName.String).Append(TEXT(".lua"))), true, false);

	if (Filenames.Num() == 0) return FLuaValue();

	return FLuaValue(ULuaBlueprintFunctionLibrary::LuaRunNonContentFile(GetWorld(), StaticClass(), Filenames[0], false));
}