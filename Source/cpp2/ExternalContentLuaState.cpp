// Fill out your copyright notice in the Description page of Project Settings.


#include "ExternalContentLuaState.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "MyActor.h"
#include "GameFramework/Actor.h"
#include "glTFRuntimeAssetActor.h"
#include "glTFRuntimeFunctionLibrary.h"
#include "LuaGlobalNameComponent.h"
#include "Components/BoxComponent.h"
#include "LuaMachine/Public/LuaBlueprintFunctionLibrary.h"
#include "MyGameStateBase.h"
#include "GameFramework/SpringArmComponent.h"

UExternalContentLuaState::UExternalContentLuaState() {
	Table.Add("set_actor_location", FLuaValue::Function(GET_FUNCTION_NAME_CHECKED(UExternalContentLuaState, SetActorLocation)));
	Table.Add("get_actor_location", FLuaValue::Function(GET_FUNCTION_NAME_CHECKED(UExternalContentLuaState, GetActorLocation)));
	Table.Add("spawn_actor", FLuaValue::Function(GET_FUNCTION_NAME_CHECKED(UExternalContentLuaState, SpawnNewActor)));
	Table.Add("spawn_actor_scene", FLuaValue::Function(GET_FUNCTION_NAME_CHECKED(UExternalContentLuaState, SpawnNewActorFull)));
	Table.Add("delete_actor", FLuaValue::Function(GET_FUNCTION_NAME_CHECKED(UExternalContentLuaState, DeleteActor)));

	Table.Add("get_actor", FLuaValue::Function(GET_FUNCTION_NAME_CHECKED(UExternalContentLuaState, GetGlobalActor)));
	Table.Add("spawn_orbit_camera", FLuaValue::Function(GET_FUNCTION_NAME_CHECKED(UExternalContentLuaState, CreateOrbitCamera)));
	Table.Add("preload_assets", FLuaValue::Function(GET_FUNCTION_NAME_CHECKED(UExternalContentLuaState, PreloadAssets)));
	Table.Add("on_key_down", FLuaValue::Function(GET_FUNCTION_NAME_CHECKED(UExternalContentLuaState, AssignOnKeyPressedEvent)));

}

FLuaValue UExternalContentLuaState::GetGlobalActor(FLuaValue name)
{
	FLuaValue res = ULuaBlueprintFunctionLibrary::LuaGetGlobal(GetWorld(), UExternalContentLuaState::StaticClass(), name.String);
	return FLuaValue();
}

FLuaValue UExternalContentLuaState::SetActorLocation(FLuaValue Actor, FLuaValue Location) 
{
	AActor* ActorObject = Cast<AActor>(Actor.Object);
	if (ActorObject)
	{
		ActorObject->SetActorLocation(LuaValueToBaseStruct<FVector>(Location), false);
	}
	return FLuaValue();
}

FLuaValue UExternalContentLuaState::GetActorLocation(FLuaValue Actor)
{
	AActor* ActorObject = Cast<AActor>(Actor.Object);
	if (ActorObject)
	{
		FVector Location = ActorObject->GetActorLocation();
		FLuaValue VTable = CreateLuaTable();
		VTable.SetField("x", FLuaValue(Location.X));
		VTable.SetField("y", FLuaValue(Location.Y));
		VTable.SetField("z", FLuaValue(Location.Z));

		return VTable;
	}
	else {
		UE_LOG(LogTemp, Display, TEXT(":("));
	}
	return FLuaValue();
}

FLuaValue UExternalContentLuaState::SpawnNewActor(FLuaValue Location, FLuaValue Scale, FLuaValue AssetName, FLuaValue ActorName)
{
	FglTFRuntimeConfig config = FglTFRuntimeConfig();

	UglTFRuntimeAsset* glTFAsset = LoadglTFAsset(AssetName.String).Get();
	if (glTFAsset) {
		FVector move = LuaValueToBaseStruct<FVector>(Location);
		FVector scale = LuaValueToBaseStruct<FVector>(Scale);
		
		FTransform trans = FTransform(FRotator(0, 0, 0), FVector(move.X, move.Y, move.Z), scale);
		AglTFRuntimeAssetActor* pActor = GetWorld()->SpawnActorDeferred<AglTFRuntimeAssetActor>(AglTFRuntimeAssetActor::StaticClass(), trans);
		if (pActor)
		{
			for (int i = 0; i < glTFAsset->GetNumMeshes(); i++) {
				UStaticMesh* loadedMesh = glTFAsset->LoadStaticMesh(i, FglTFRuntimeStaticMeshConfig());
				if (loadedMesh) {
					class UStaticMeshComponent* Mesh = NewObject<UStaticMeshComponent>(pActor, UStaticMeshComponent::StaticClass(), FName(FString::Printf(TEXT("%d"), i)));
					Mesh->SetStaticMesh(loadedMesh);
					Mesh->RegisterComponent();
					Mesh->AttachToComponent(pActor->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
				}
			}

			class ULuaGlobalNameComponent* globalName = NewObject<ULuaGlobalNameComponent>(pActor, ULuaGlobalNameComponent::StaticClass(), TEXT("GlobalName"));
			pActor->AddOwnedComponent(globalName);
			globalName->LuaGlobalName = FString(ActorName.String);
			globalName->LuaState = UExternalContentLuaState::StaticClass();
			globalName->RegisterComponent();

			UGameplayStatics::FinishSpawningActor(pActor, trans);
			pActor->AddActorWorldOffset(move);
			pActor->SetActorScale3D(scale);

			return FLuaValue(pActor);
		}
	}
	return FLuaValue();
}

FLuaValue UExternalContentLuaState::SpawnNewActorFull(FLuaValue Location, FLuaValue Scale, FLuaValue AssetName, FLuaValue ActorName)
{
	FglTFRuntimeConfig config = FglTFRuntimeConfig();

	UglTFRuntimeAsset* glTFAsset = LoadglTFAsset(AssetName.String).Get();
	if (glTFAsset) {
		FVector move = LuaValueToBaseStruct<FVector>(Location);
		FVector scale = LuaValueToBaseStruct<FVector>(Scale);

		FTransform trans = FTransform(FRotator(0, 0, 0), FVector(move.X, move.Y, move.Z), scale);
		AglTFRuntimeAssetActor* pActor = GetWorld()->SpawnActorDeferred<AglTFRuntimeAssetActor>(AglTFRuntimeAssetActor::StaticClass(), trans);
		if (pActor)
		{
			pActor->Asset = glTFAsset;

			class ULuaGlobalNameComponent* globalName = NewObject<ULuaGlobalNameComponent>(pActor, ULuaGlobalNameComponent::StaticClass(), TEXT("GlobalName"));
			pActor->AddOwnedComponent(globalName);
			globalName->LuaGlobalName = FString(ActorName.String);
			globalName->LuaState = UExternalContentLuaState::StaticClass();
			globalName->RegisterComponent();



			UGameplayStatics::FinishSpawningActor(pActor, trans);
			pActor->AddActorWorldOffset(move);
			pActor->SetActorScale3D(scale);

			return FLuaValue(pActor);

		}
	}

	return FLuaValue();
}

FLuaValue UExternalContentLuaState::CreateOrbitCamera(FLuaValue Centre, FLuaValue Distance) {
	FVector move = LuaValueToBaseStruct<FVector>(Centre);

	FTransform trans = FTransform(FVector(move.X,move.Y,move.Z));

	AMyGameStateBase* GameState = GetWorld()->GetGameState<AMyGameStateBase>();

	AActor* OrbitCameraActor = GetWorld()->SpawnActor<AActor>(GameState->OrbitCameraBP, trans);

	OrbitCameraActor->GetComponentByClass<USpringArmComponent>()->TargetArmLength = Distance.Number;

	APlayerController* controller = GetWorld()->GetFirstPlayerController();
	if (controller && OrbitCameraActor) {
		controller->Possess(Cast<APawn>(OrbitCameraActor));
	}
	return FLuaValue();
}

FLuaValue UExternalContentLuaState::DeleteActor(FLuaValue Actor) 
{
	AActor* actor = Cast<AActor>(Actor.Object);
	if (actor) {
		actor->Destroy();
	}
	return FLuaValue();
}

TWeakObjectPtr<UglTFRuntimeAsset> UExternalContentLuaState::LoadglTFAsset(FString assetPath) {
	FglTFRuntimeConfig config = FglTFRuntimeConfig();

	if (glTFCache.Contains(assetPath)) {
		if (glTFCache[assetPath].IsValid())
		{
			return glTFCache[assetPath];
		}
		else {
			glTFCache.Remove(assetPath);
		}
	}


	TWeakObjectPtr<UglTFRuntimeAsset> gltfAsset = nullptr;
	if (assetPath.StartsWith(FString("http"))) {
		// TODO
		// Load from http server
	}
	else
	{
		gltfAsset = UglTFRuntimeFunctionLibrary::glTFLoadAssetFromFilename(FString(BaseglTFLocalPath).Append(FString(assetPath)), false, config);
	}
	
	if (gltfAsset.IsValid()) {
		glTFCache.Add(assetPath, gltfAsset); 
	}
	else {
		return nullptr;
	}

	return gltfAsset;
}

FLuaValue UExternalContentLuaState::PreloadAssets(TArray<FLuaValue> Assets) {
	for (int i = 0; i < Assets.Num(); i++) {
		LoadglTFAsset(Assets[i].String);
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