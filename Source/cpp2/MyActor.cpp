// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
//#include "RealtimeMeshSimple.h"
//#include "RealtimeMeshComponent.h"
#include "Components/BoxComponent.h"
#include "MyActorComponent.h"
#include "Components/ArrowComponent.h"
#include "glTFRuntime.h"
#include "glTFRuntimeAsset.h"
#include "glTFRuntimeAssetActor.h"
#include "glTFRuntimeClasses.h"
#include "glTFRuntimeFunctionLibrary.h"
#include <Kismet/GameplayStatics.h>
#include "Components/StaticMeshComponent.h"
#include "LuaRunner.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*URealtimeMeshComponent:*/

	
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	//class UBoxComponent* CollisionMesh = NewObject<UBoxComponent>(this, UBoxComponent::StaticClass(), TEXT("Mesh"));
	
	//FVector bounds = FVector(32, 32, 32);

	//CollisionMesh->InitBoxExtent(bounds);
	//CollisionMesh->SetCollisionProfileName(UCollisionProfile::BlockAllDynamic_ProfileName);
	//CollisionMesh->AddLocalOffset(FVector(0,0,10));
	//CollisionMesh->RegisterComponent();


	//class UStaticMeshComponent* sMesh = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass(), TEXT("ViewMesh"));
	//sMesh->RegisterComponent();
	//SetRootComponent(sMesh);

	//SetRootComponent(CollisionMesh);

	//class UMyActorComponent* moveComp = NewObject<UMyActorComponent>(this, UMyActorComponent::StaticClass(), TEXT("Mover"));
	//moveComp->RegisterComponent();
	//this->AddOwnedComponent(moveComp);

	


	//FglTFRuntimeConfig config = FglTFRuntimeConfig();

	//UglTFRuntimeAsset* cube = UglTFRuntimeFunctionLibrary::glTFLoadAssetFromFilename(FString("C:/Users/niami/Documents/cube.gltf"), false, config);
	//if (cube) {
		//UWorld* world = GetWorld();
		//if (world) {
		//	
		//	//world->SpawnActor<AglTFRuntimeAssetActor>(AglTFRuntimeAssetActor::StaticClass(), this->GetTransform());
		//	AglTFRuntimeAssetActor* pActor = GetWorld()->SpawnActorDeferred<AglTFRuntimeAssetActor>(AglTFRuntimeAssetActor::StaticClass(), this->GetActorTransform());
		//	GEngine->AddOnScreenDebugMessage(-1, 200, FColor::Blue, FString("Spawning actor 1"));
		//	if (pActor)
		//	{
		//		GEngine->AddOnScreenDebugMessage(-1, 200, FColor::Blue, FString("Spawning actor 2"));
		//		//...setstuff here..then finish spawn..
		//		pActor->Asset = cube;

		//		UGameplayStatics::FinishSpawningActor(pActor, this->GetActorTransform());
		//		pActor->AddActorLocalOffset(FVector(0, 0, 320));
		//	}
		//		
		//}
		//UStaticMesh* cubeMesh = cube->LoadStaticMesh(0, FglTFRuntimeStaticMeshConfig());
		//if (cubeMesh) {
			//sMesh->SetStaticMesh(cubeMesh);
		//}
	//}

	//this->AddActorWorldOffset(FVector(0, 0, 150));

	/*TArray<USceneComponent*> a;
	

	if (GetRootComponent()) {
		this->GetRootComponent()->GetChildrenComponents(true, a);
	}
	

	GEngine->AddOnScreenDebugMessage(-1, 200, FColor::Red, FString::Printf(TEXT("Length: %d	"), a.Num()));


	GEngine->AddOnScreenDebugMessage(-1, 200, FColor::Green, FString(CollisionMesh->GetCollisionProfileName().ToString()));*/
}
//void AMyActor::OnGenerateMesh_Implementation()
//{
//
//	
//
//	// Initialize to a simple mesh, this behaves the most like a ProceduralMeshComponent
//	// Where you can set the mesh data and forget about it.
//	URealtimeMeshSimple* RealtimeMesh = this->GetComponentByClass<URealtimeMeshComponent>()->InitializeRealtimeMesh<URealtimeMeshSimple>();
//
//	// The most important part of the mesh data is the StreamSet, it contains the individual buffers,
//	// like position, tangents, texcoords, triangles etc. 
//	FRealtimeMeshStreamSet StreamSet;
//
//	// For this example we'll use a helper class to build the mesh data
//	// You can make your own helpers or skip them and use individual TRealtimeMeshStreamBuilder,
//	// or skip them entirely and copy data directly into the streams
//	TRealtimeMeshBuilderLocal<uint16, FPackedNormal, FVector2DHalf, 1> Builder(StreamSet);
//
//	// here we go ahead and enable all the basic mesh data parts
//	Builder.EnableTangents();
//	Builder.EnableTexCoords();
//	Builder.EnableColors();
//
//	// Poly groups allow us to easily create a single set of buffers with multiple sections by adding an index to the triangle data
//	Builder.EnablePolyGroups();
//
//	// Add our first vertex
//	int32 V0 = Builder.AddVertex(FVector3f(-50.0f, 0.0f, 0.0f))
//		.SetNormalAndTangent(FVector3f(0.0f, -1.0f, 0.0f), FVector3f(1.0f, 0.0f, 0.0f))
//		.SetColor(FColor::Red)
//		.SetTexCoord(FVector2f(0.0f, 0.0f));
//
//	// Add our second vertex
//	int32 V1 = Builder.AddVertex(FVector3f(0.0f, 0.0f, 100.0f))
//		.SetNormalAndTangent(FVector3f(0.0f, -1.0f, 0.0f), FVector3f(1.0f, 0.0f, 0.0f))
//		.SetColor(FColor::Green)
//		.SetTexCoord(FVector2f(0.5f, 1.0f));
//
//	// Add our third vertex
//	int32 V2 = Builder.AddVertex(FVector3f(50.0, 0.0, 0.0))
//		.SetNormalAndTangent(FVector3f(0.0f, -1.0f, 0.0f), FVector3f(1.0f, 0.0f, 0.0f))
//		.SetColor(FColor::Blue)
//		.SetTexCoord(FVector2f(1.0f, 0.0f));
//
//	// Add our triangle, placing the vertices in counter clockwise order
//	Builder.AddTriangle(V0, V1, V2, 0/* This is the polygroup index */);
//
//	// For this example we'll add the triangle again using reverse order so we can see the backface.
//	// Usually you wouldn't want to do this, but in this case of a single triangle,
//	// without it you'll only be able to see from a single side
//	Builder.AddTriangle(V2, V1, V0, 1/* This is the polygroup index */);
//
//	// Setup the two material slots
//	RealtimeMesh->SetupMaterialSlot(0, "PrimaryMaterial");
//	RealtimeMesh->SetupMaterialSlot(1, "SecondaryMaterial");
//
//	// Now create the group key. This is a unique identifier for the section group
//	// A section group contains one or more sections that all share the underlying buffers
//	// these sections can overlap the used vertex/index ranges depending on use case.
//	const FRealtimeMeshSectionGroupKey GroupKey = FRealtimeMeshSectionGroupKey::Create(0, FName("TestTriangle"));
//
//	// Now create the section key, this is a unique identifier for a section within a group
//	// The section contains the configuration for the section, like the material slot,
//	// and the draw type, as well as the range of the index/vertex buffers to use to render.
//	// Here we're using the version to create the key based on the PolyGroup index
//	const FRealtimeMeshSectionKey PolyGroup0SectionKey = FRealtimeMeshSectionKey::CreateForPolyGroup(GroupKey, 0);
//	const FRealtimeMeshSectionKey PolyGroup1SectionKey = FRealtimeMeshSectionKey::CreateForPolyGroup(GroupKey, 1);
//
//	// Now we create the section group, since the stream set has polygroups, this will create the sections as well
//	RealtimeMesh->CreateSectionGroup(GroupKey, StreamSet);
//
//	// Update the configuration of both the polygroup sections.
//	RealtimeMesh->UpdateSectionConfig(PolyGroup0SectionKey, FRealtimeMeshSectionConfig(ERealtimeMeshSectionDrawType::Static, 0));
//	RealtimeMesh->UpdateSectionConfig(PolyGroup1SectionKey, FRealtimeMeshSectionConfig(ERealtimeMeshSectionDrawType::Static, 1));

	//Super::OnGenerateMesh_Implementation();
//}
// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}