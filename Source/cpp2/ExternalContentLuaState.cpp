// Fill out your copyright notice in the Description page of Project Settings.


#include "ExternalContentLuaState.h"

#include "LuaBlueprintFunctionLibrary.h"
#include "MyGameStateBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "LuaCModules/ActorModule.h"


UExternalContentLuaState::UExternalContentLuaState() {
	ModuleLoadingClass = this->StaticClass();

	Table.Add("spawn_orbit_camera", FLuaValue::Function(GET_FUNCTION_NAME_CHECKED(UExternalContentLuaState, CreateOrbitCamera)));
	Table.Add("on_key_down", FLuaValue::Function(GET_FUNCTION_NAME_CHECKED(UExternalContentLuaState, AssignOnKeyPressedEvent)));

	CModuleClassMap.Add("Actor", UActorModule::StaticClass());
}

FLuaValue UExternalContentLuaState::CreateOrbitCamera(FLuaValue Centre, FLuaValue Distance) {
	FVector move = LuaValueToBaseStruct<FVector>(Centre);

	FTransform trans = FTransform(FVector(move.X, move.Y, move.Z));

	AMyGameStateBase* GameState = GetWorld()->GetGameState<AMyGameStateBase>();

	AActor* OrbitCameraActor = GetWorld()->SpawnActor<AActor>(GameState->OrbitCameraBP, trans);

	OrbitCameraActor->GetComponentByClass<USpringArmComponent>()->TargetArmLength = Distance.Number;

	APlayerController* controller = GetWorld()->GetFirstPlayerController();
	if (controller && OrbitCameraActor) {
		controller->Possess(Cast<APawn>(OrbitCameraActor));
	}
	return FLuaValue();
}

FLuaValue UExternalContentLuaState::AssignOnKeyPressedEvent(FLuaValue KeyName, FLuaValue Callback) {
	OnKeyDownCallbacks.Add(FKey(FName(KeyName.String)), AddLuaSmartReference(Callback));

	GetWorld()->GetFirstPlayerController()->InputComponent->BindKey(FKey(FName(KeyName.String)), EInputEvent::IE_Pressed, this, &UExternalContentLuaState::OnKeyDownCallback);
	return FLuaValue();

}

void UExternalContentLuaState::OnKeyDownCallback(FKey key) {
	if (OnKeyDownCallbacks.Contains(key)) {
		TArray<FLuaValue> Args = { FLuaValue(this), FLuaValue("Message") };
		ULuaBlueprintFunctionLibrary::LuaValueCallIfNotNil(TWeakPtr<FLuaSmartReference>(OnKeyDownCallbacks[key]).Pin()->Value, Args);
	}
}
