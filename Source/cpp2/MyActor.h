// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class CPP2_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//virtual void OnGenerateMesh_Implementation();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
