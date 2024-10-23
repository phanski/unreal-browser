// Fill out your copyright notice in the Description page of Project Settings.

#include "LuaInitialLoader.h"
//#include "LuaInitialLoaderStatea.h"
#include "LuaBlueprintFunctionLibrary.h"

void ULuaInitialLoader::BeginPlay() {
	//Super::BeginPlay();

	//UWorld* world = GetWorld();
	//FLuaValue InitSuccessful = ULuaBlueprintFunctionLibrary::LuaRunFile(world, ULuaInitialLoaderStatea::StaticClass(), FString("lua/init.lua"), false);
	//if (!InitSuccessful.Bool) {
		//UE_LOG(LogTemp, Display, TEXT("Failed to load Lua init file"));

		 //TODO Add on screen error alerting user to failed init
		//return;
	//}



	//ULuaBlueprintFunctionLibrary::LuaGlobalCall(world, ULuaInitialLoaderStatea::StaticClass(), FString("Main"), TArray<FLuaValue>());
		


}