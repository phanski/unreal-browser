// Fill out your copyright notice in the Description page of Project Settings.


#include "LuaRunner.h"
//#include "LuaMachine.h"
#include "LuaState.h"
#include "LuaMachine/Public/LuaBlueprintFunctionLibrary.h"
#include "ExternalContentLuaState.h"
#include "LuaInitialLoaderStateBase.h"
#include "MyGameStateBase.h"


// Sets default values for this component's properties
ULuaRunner::ULuaRunner()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 0.1;
	PrimaryComponentTick.bStartWithTickEnabled = true;
	// ...
	
}


void ULuaRunner::BeginPlay()
{
	Super::BeginPlay();
	

	FString urlValue;

	if (FParse::Value(FCommandLine::Get(), TEXT("URL="), urlValue))
	{
		GEngine->AddOnScreenDebugMessage(-1, 200, FColor::Red, urlValue);
	}

	UWorld* world = GetWorld();
	FLuaValue InitSuccessful = ULuaBlueprintFunctionLibrary::LuaRunFile(
		world, 
		ULuaInitialLoaderStateBase::StaticClass(), 
		FString("lua/init.lua"), 
		false
	);

	if (!InitSuccessful.Bool) {
		UE_LOG(LogTemp, Display, TEXT("Failed to load Lua init file"));

		//TODO Add on screen error alerting user to failed init
		return;
	}

	ULuaBlueprintFunctionLibrary::LuaGlobalCall(
		world, 
		ULuaInitialLoaderStateBase::StaticClass(), 
		FString("Main"), 
		TArray<FLuaValue> { FLuaValue::FunctionOfObject(this, FName("OnInitComplete")) }
	);
}


FLuaValue ULuaRunner::OnInitComplete()
{
	UWorld* world = GetWorld();
	FLuaValue FoundExternalMain = ULuaBlueprintFunctionLibrary::LuaRunFile(
		world, 
		UExternalContentLuaState::StaticClass(), 
		FString("lua/External/Main.lua"), 
		false
	);

	if (!FoundExternalMain.Bool)
	{
		UE_LOG(LogTemp, Display, TEXT("Failed to pass control to external content"));

		//TODO Add on screen error alerting user to failed init
		return FLuaValue();
	}

	ULuaBlueprintFunctionLibrary::LuaGlobalCall(world, UExternalContentLuaState::StaticClass(), FString("Main"), TArray<FLuaValue>());
	return FLuaValue();
}


// Called every frame
void ULuaRunner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// ...
}

