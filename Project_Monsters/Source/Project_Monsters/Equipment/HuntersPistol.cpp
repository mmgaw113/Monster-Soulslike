// Fill out your copyright notice in the Description page of Project Settings.


#include "HuntersPistol.h"
#include "Kismet/GameplayStatics.h"
#include "Project_Monsters/CharacterControllerComponent/BaseCharacterController.h"

AHuntersPistol::AHuntersPistol()
{
	mesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	mesh->SetSkeletalMesh(pistolMesh);
	damage = 0;
	Dexterity = D;
	Arcane = B;
	Strength = None;
}

void AHuntersPistol::BeginPlay()
{
	Super::BeginPlay();
	
	UpdateDamage();
}
