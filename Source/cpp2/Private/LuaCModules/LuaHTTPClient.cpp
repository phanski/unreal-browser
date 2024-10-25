// Fill out your copyright notice in the Description page of Project Settings.

#include "LuaCModules/LuaHTTPClient.h"
#include "LuaBlueprintFunctionLibrary.h"

ULuaHTTPClient::ULuaHTTPClient() {
    Table.Add("Get", FLuaValue::Function(GET_FUNCTION_NAME_CHECKED(ULuaHTTPClient, HttpGetCallback)));
}

FLuaValue ULuaHTTPClient::HttpGetCallback(FLuaValue URL, FLuaValue Callback) {
    FHttpModule* http = &FHttpModule::Get();
    TSharedRef<IHttpRequest> request = http->CreateRequest();
   
    request->SetURL(URL.String);
    request->SetVerb(FString("GET"));
    request->OnProcessRequestComplete().BindLambda([Callback, this](FHttpRequestPtr requesta, FHttpResponsePtr response, bool success) {
        if (success) {
            TArray<FLuaValue> Args = { FLuaValue(response->GetContentAsString())};
            ULuaBlueprintFunctionLibrary::LuaValueCallIfNotNil(Callback, Args);
        }
    });
    request->ProcessRequest();

    return FLuaValue(true);
}

//void ULuaHTTPClient::HTTPCallback(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, FLuaValue callback) {
    //TArray<FLuaValue> Args = { FLuaValue(this) };
    //ULuaBlueprintFunctionLibrary::LuaValueCallIfNotNil(callback, Args);
//}