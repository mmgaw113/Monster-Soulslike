// Fill out your copyright notice in the Description page of Project Settings.


#include "HuntersPistol.h"

AHuntersPistol::AHuntersPistol()
{
	mesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	mesh->SetSkeletalMesh(blunderBussMesh);
}
