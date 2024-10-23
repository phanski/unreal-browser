// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActorComponent.h"

// Sets default values for this component's properties
UMyActorComponent::UMyActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMyActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMyActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* parent = this->GetOwner();
	if (!parent) {
		GEngine->AddOnScreenDebugMessage(1, 200, FColor::Blue, FString("Failed to get parent"));
		return;
	}

	USceneComponent* root = parent->GetRootComponent();
	if (!root) {
		GEngine->AddOnScreenDebugMessage(2, 200, FColor::Blue, FString("Failed to get roott"));
		return;
	}

	FQuat rot = FQuat(FVector(0,0,1),0.01);
	root->AddWorldRotation(rot);


	// ...
}

