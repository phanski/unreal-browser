// Fill out your copyright notice in the Description page of Project Settings.


#include "LuaCModules/LuaWebsocketConnection.h"
#include "LuaBlueprintFunctionLibrary.h"
#include "WebSocketsModule.h"


ULuaWebsocketConnection::ULuaWebsocketConnection()
{
	Table.Add("connect", FLuaValue::Function(GET_FUNCTION_NAME_CHECKED(ULuaWebsocketConnection, Connect)));
	Table.Add("disconnect", FLuaValue::Function(GET_FUNCTION_NAME_CHECKED(ULuaWebsocketConnection, Disconnect)));
	Table.Add("send", FLuaValue::Function(GET_FUNCTION_NAME_CHECKED(ULuaWebsocketConnection, Send)));
	Table.Add("close", FLuaValue::Function(GET_FUNCTION_NAME_CHECKED(ULuaWebsocketConnection, Close)));

	Metatable.Add("__tostring", FLuaValue::Function(GET_FUNCTION_NAME_CHECKED(ULuaWebsocketConnection, ToLuaString)));

	bImplicitSelf = true;
}

ULuaWebsocketConnection::~ULuaWebsocketConnection()
{
	Disconnect();
	UE_LOG(LogLuaMachine, Log, TEXT("Websocket Destroyed"));
}

void ULuaWebsocketConnection::Connect(FLuaValue Url, FLuaValue InOnConnectedCallback, FLuaValue InOnConnectionErrorCallback)
{
	Disconnect();

	CurrentUrl = Url.ToString();

	WebSocketConnection = FWebSocketsModule::Get().CreateWebSocket(Url.ToString(), TEXT("ws"));
	WebSocketConnection->OnMessage().AddUObject(this, &ULuaWebsocketConnection::OnMessageDelegate);
	WebSocketConnection->OnClosed().AddUObject(this, &ULuaWebsocketConnection::OnClosedDelegate);

	OnConnectedCallback = AddLuaSmartReference(InOnConnectedCallback);
	OnConnectionErrorCallback = AddLuaSmartReference(InOnConnectionErrorCallback);

	WebSocketConnection->OnConnectionError().AddUObject(this, &ULuaWebsocketConnection::OnConnectionErrorDelegate, TWeakPtr<FLuaSmartReference>(OnConnectionErrorCallback));
	WebSocketConnection->OnConnected().AddUObject(this, &ULuaWebsocketConnection::OnConnectedDelegate, TWeakPtr<FLuaSmartReference>(OnConnectedCallback));
	WebSocketConnection->Connect();
}

void ULuaWebsocketConnection::Disconnect()
{
	OnConnectedCallback.Reset();
	OnConnectionErrorCallback.Reset();

	if (WebSocketConnection.IsValid())
	{
		WebSocketConnection->Close();
		WebSocketConnection.Reset();
	}
}

void ULuaWebsocketConnection::Send(FLuaValue Message)
{
	if (WebSocketConnection.IsValid() && WebSocketConnection->IsConnected())
	{
		WebSocketConnection->Send(Message.ToString());
	}
}

void ULuaWebsocketConnection::Close(FLuaValue Code, FLuaValue Reason)
{
	if (WebSocketConnection.IsValid() && WebSocketConnection->IsConnected())
	{
		WebSocketConnection->Close(Code.Integer, Reason.ToString());
	}
}

FLuaValue ULuaWebsocketConnection::ToLuaString()
{
	if (WebSocketConnection.IsValid() && WebSocketConnection->IsConnected())
	{
		return FLuaValue(FString::Printf(TEXT("WebSocket Connected to %s"), *CurrentUrl));
	}
	return FLuaValue("Unconnected WebSocket");
}

void ULuaWebsocketConnection::OnMessageDelegate(const FString& Message)
{
	FLuaValue Callback = LuaGetField("on_message");
	TArray<FLuaValue> Args = { FLuaValue(this), FLuaValue(Message) };
	ULuaBlueprintFunctionLibrary::LuaValueCallIfNotNil(Callback, Args);
}

void ULuaWebsocketConnection::OnClosedDelegate(int32 Code, const FString& Reason, bool bUserClose)
{
	FLuaValue Callback = LuaGetField("on_closed");
	TArray<FLuaValue> Args = { FLuaValue(this), FLuaValue(Code), FLuaValue(Reason), FLuaValue(bUserClose) };
	ULuaBlueprintFunctionLibrary::LuaValueCallIfNotNil(Callback, Args);
}

void ULuaWebsocketConnection::OnConnectedDelegate(TWeakPtr<FLuaSmartReference> OnConnectedCallbackRef)
{
	if (!OnConnectedCallbackRef.IsValid())
		return;

	TArray<FLuaValue> Args = { FLuaValue(this) };
	ULuaBlueprintFunctionLibrary::LuaValueCallIfNotNil(OnConnectedCallbackRef.Pin()->Value, Args);
}

void ULuaWebsocketConnection::OnConnectionErrorDelegate(const FString& Message, TWeakPtr<FLuaSmartReference> OnConnectionErrorCallbackRef)
{
	if (!OnConnectionErrorCallbackRef.IsValid())
		return;

	TArray<FLuaValue> Args = { FLuaValue(this), FLuaValue(Message) };
	ULuaBlueprintFunctionLibrary::LuaValueCallIfNotNil(OnConnectionErrorCallbackRef.Pin()->Value, Args);
}