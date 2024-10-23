// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LuaUserDataObject.h"
#include "IWebSocket.h"
#include "LuaWebsocketConnection.generated.h"

/**
 * 
 */
UCLASS()
class CPP2_API ULuaWebsocketConnection : public ULuaUserDataObject
{
	GENERATED_BODY()

public:
	ULuaWebsocketConnection();
	virtual ~ULuaWebsocketConnection() override;

	UFUNCTION()
	void Connect(FLuaValue Url, FLuaValue InOnConnectedCallback, FLuaValue InOnConnectionErrorCallback);

	UFUNCTION()
	void Disconnect();

	UFUNCTION()
	void Send(FLuaValue Message);

	UFUNCTION()
	FLuaValue ToLuaString();

	UFUNCTION()
	void Close(FLuaValue Code, FLuaValue Reason);

protected:
	TSharedPtr<IWebSocket> WebSocketConnection;
	TSharedPtr<FLuaSmartReference> OnConnectedCallback;
	TSharedPtr<FLuaSmartReference> OnConnectionErrorCallback;

	void OnMessageDelegate(const FString& Message);
	void OnClosedDelegate(int32 Code, const FString& Reason, bool bUserClose);

	void OnConnectedDelegate(TWeakPtr<FLuaSmartReference> OnConnectedCallbackRef);
	void OnConnectionErrorDelegate(const FString& Message, TWeakPtr<FLuaSmartReference> OnConnectionErrorCallbackRef);

	FString CurrentUrl;
};
