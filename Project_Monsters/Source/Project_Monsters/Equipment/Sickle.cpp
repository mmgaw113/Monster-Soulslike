// Fill out your copyright notice in the Description page of Project Settings.


#include "Sickle.h"

ASickle::ASickle()
{
	mesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	mesh->SetSkeletalMesh(sickleMesh);
	Strength = C;
	Dexterity = C;
	Arcane = E;
}
