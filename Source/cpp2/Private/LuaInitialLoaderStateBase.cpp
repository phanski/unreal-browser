// Fill out your copyright notice in the Description page of Project Settings.


#include "LuaInitialLoaderStateBase.h"
#include "HAL/FileManager.h"

ULuaInitialLoaderStateBase::ULuaInitialLoaderStateBase()
{
	ModuleLoadingClass = this->StaticClass();
}
