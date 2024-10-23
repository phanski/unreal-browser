// Fill out your copyright notice in the Description page of Project Settings.


#include "LuaRunner.h"
//#include "LuaMachine.h"
#include "LuaState.h"
#include "LuaMachine/Public/LuaBlueprintFunctionLibrary.h"
#include "NewLuaState.h"
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


// Called when the game starts
void ULuaRunner::BeginPlay()
{
	Super::BeginPlay();
	
	//FLuaValue result = ULuaBlueprintFunctionLibrary::LuaRunFile(GetWorld(), UNewLuaState::StaticClass(), FString("hello.lua"), false);
	//GEngine->AddOnScreenDebugMessage(-1, 200, FColor::Red, result.String);

	//ULuaBlueprintFunctionLibrary::LuaSetGlobal(GetWorld(), UNewLuaState::StaticClass(), FString("OrbitCamera"), FLuaValue(this->OrbitCamera->StaticClass()));
	


	FString urlValue;

	if (FParse::Value(FCommandLine::Get(), TEXT("URL="), urlValue))
	{
		GEngine->AddOnScreenDebugMessage(-1, 200, FColor::Red, urlValue);
	}
	//TArray<FLuaValue> inp = TArray<FLuaValue>();
	//inp.Empty();
	
	//GEngine->AddOnScreenDebugMessage(-1, 200, FColor::Red, res2.String);
	TArray<FLuaValue> inp = TArray<FLuaValue>();
	//inp.Add(FLuaValue(this->GetOwner())`);
	//ULuaBlueprintFunctionLibrary::LuaGlobalCall(GetWorld(), UNewLuaState::StaticClass(), FString("spawn"), inp);
	ULuaBlueprintFunctionLibrary::LuaGlobalCall(GetWorld(), UNewLuaState::StaticClass(), FString("Main"), inp);
	//ULuaBlueprintFunctionLibrary::LuaGlobalCall(GetWorld(), UNewLuaState::StaticClass(), FString("spawncamera"), inp);


}


// Called every frame
void ULuaRunner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// ...
}

