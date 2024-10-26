// Fill out your copyright notice in the Description page of Project Settings.


#include "LuaCModules/ActorModule.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "glTFRuntimeAssetActor.h"
#include "glTFRuntimeFunctionLibrary.h"
#include "LuaGlobalNameComponent.h"
#include "LuaBlueprintFunctionLibrary.h"

UActorModule::UActorModule()
{
	Table.Add("spawn_actor_scene", FLuaValue::Function(GET_FUNCTION_NAME_CHECKED(UActorModule, SpawnNewActorFull)));
	Table.Add("spawn_actor", FLuaValue::Function(GET_FUNCTION_NAME_CHECKED(UActorModule, SpawnNewActor)));
	Table.Add("delete_actor", FLuaValue::Function(GET_FUNCTION_NAME_CHECKED(UActorModule, DeleteActor)));

}

FLuaValue UActorModule::GetGlobalActor(FLuaValue name)
{
	FLuaValue res = ULuaBlueprintFunctionLibrary::LuaGetGlobal(GetWorld(), StaticClass(), name.String);
	return FLuaValue();
}

FLuaValue UActorModule::SetActorLocation(FLuaValue Actor, FLuaValue Location)
{
	AActor* ActorObject = Cast<AActor>(Actor.Object);
	if (ActorObject)
	{
		ActorObject->SetActorLocation(GetLuaStateInstance()->LuaValueToBaseStruct<FVector>(Location), false);
	}
	return FLuaValue();
}

FLuaValue UActorModule::GetActorLocation(FLuaValue Actor)
{
	AActor* ActorObject = Cast<AActor>(Actor.Object);
	if (ActorObject)
	{
		FVector Location = ActorObject->GetActorLocation();
		FLuaValue VTable = GetLuaStateInstance()->CreateLuaTable();
		
		VTable.SetField("x", FLuaValue(Location.X));
		VTable.SetField("y", FLuaValue(Location.Y));
		VTable.SetField("z", FLuaValue(Location.Z));

		return VTable;
	}
	return FLuaValue();
}

FLuaValue UActorModule::SpawnNewActor(FLuaValue Location, FLuaValue Scale, FLuaValue AssetName, FLuaValue ActorName)
{
	FglTFRuntimeConfig config = FglTFRuntimeConfig();

	UglTFRuntimeAsset* glTFAsset = LoadglTFAsset(AssetName.String).Get();
	if (glTFAsset) {
		FVector move = GetLuaStateInstance()->LuaValueToBaseStruct<FVector>(Location);
		FVector scale = GetLuaStateInstance()->LuaValueToBaseStruct<FVector>(Scale);

		FTransform trans = FTransform(FRotator(0, 0, 0), FVector(move.X, move.Y, move.Z), scale);
		AglTFRuntimeAssetActor* pActor = GetWorld()->SpawnActorDeferred<AglTFRuntimeAssetActor>(AglTFRuntimeAssetActor::StaticClass(), trans);
		if (pActor)
		{
			for (int i = 0; i < glTFAsset->GetNumMeshes(); i++) {
				UStaticMesh* loadedMesh = glTFAsset->LoadStaticMesh(i, FglTFRuntimeStaticMeshConfig());
				if (loadedMesh) {
					UStaticMeshComponent* Mesh = NewObject<UStaticMeshComponent>(pActor, UStaticMeshComponent::StaticClass(), FName(FString::Printf(TEXT("%d"), i)));
					Mesh->SetStaticMesh(loadedMesh);
					Mesh->RegisterComponent();
					Mesh->AttachToComponent(pActor->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
				}
			}

			ULuaGlobalNameComponent* globalName = NewObject<ULuaGlobalNameComponent>(pActor, ULuaGlobalNameComponent::StaticClass(), TEXT("GlobalName"));
			pActor->AddOwnedComponent(globalName);
			globalName->LuaGlobalName = FString(ActorName.String);
			globalName->LuaState = GetLuaState();
			globalName->RegisterComponent();

			UGameplayStatics::FinishSpawningActor(pActor, trans);
			pActor->AddActorWorldOffset(move);
			pActor->SetActorScale3D(scale);

			return FLuaValue(pActor);
		}
	}
	return FLuaValue();
}

FLuaValue UActorModule::SpawnNewActorFull(FLuaValue Location, FLuaValue Scale, FLuaValue AssetName, FLuaValue ActorName)
{
	FglTFRuntimeConfig config = FglTFRuntimeConfig();

	UglTFRuntimeAsset* glTFAsset = LoadglTFAsset(AssetName.String).Get();
	if (glTFAsset) {
		FVector move = GetLuaStateInstance()->LuaValueToBaseStruct<FVector>(Location);
		FVector scale = GetLuaStateInstance()->LuaValueToBaseStruct<FVector>(Scale);

		

		FTransform trans = FTransform(FRotator(0, 0, 0), FVector(move.X, move.Y, move.Z), scale);
		AglTFRuntimeAssetActor* pActor = GetWorld()->SpawnActorDeferred<AglTFRuntimeAssetActor>(AglTFRuntimeAssetActor::StaticClass(), trans);
		if (pActor)
		{
			pActor->Asset = glTFAsset;

			ULuaGlobalNameComponent* globalName = NewObject<ULuaGlobalNameComponent>(pActor, ULuaGlobalNameComponent::StaticClass(), TEXT("GlobalName"));
			pActor->AddOwnedComponent(globalName);
			globalName->LuaGlobalName = FString(ActorName.String);
			globalName->LuaState = StaticClass();
			globalName->RegisterComponent();



			UGameplayStatics::FinishSpawningActor(pActor, trans);
			pActor->AddActorWorldOffset(move);
			pActor->SetActorScale3D(scale);

			return FLuaValue(pActor);

		}
	}

	return FLuaValue();
}


FLuaValue UActorModule::DeleteActor(FLuaValue Actor)
{
	AActor* actor = Cast<AActor>(Actor.Object);
	if (actor) {
		actor->Destroy();
	}
	return FLuaValue();
}

TWeakObjectPtr<UglTFRuntimeAsset> UActorModule::LoadglTFAsset(FString assetPath) {
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

