// Fill out your copyright notice in the Description page of Project Settings.


#include "Sickle.h"

#include "Kismet/GameplayStatics.h"
#include "Project_Monsters/CharacterControllerComponent/BaseCharacterController.h"

ASickle::ASickle()
{
	mesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	mesh->SetSkeletalMesh(sickleMesh);
	damage = 0;
	Strength = C;
	Dexterity = C;
	Arcane = None;
}

void ASickle::BeginPlay()
{
	Super::BeginPlay();
	UpdateDamage();
}
