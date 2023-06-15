// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "Internationalization/Text.h"
#include "CharacterController.h"
#include "Blueprint/WidgetLayoutLibrary.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Object Mesh"));
	ObjectMesh->SetSimulatePhysics(true);
	RootComponent = ObjectMesh;

	bHolding = false;
	bGravity = true;
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
	MyCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
	PlayerCamera = MyCharacter->FindComponentByClass<UCameraComponent>();

	TArray<USceneComponent*> Components;
	MyCharacter->GetComponents(Components);

	if (Components.Num() > 0) {
		for (auto& comp : Components) {
			if (comp->GetName() == "HoldingComponent") {
				HoldingComp = Cast<USceneComponent>(comp);
			}
			
		}
	}
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickup::RotateActor()
{
	ControlRotation = GetWorld()->GetFirstPlayerController()->GetControlRotation();
	SetActorRotation(FQuat(ControlRotation));
}

void APickup::Pickup()
{
	bHolding = !bHolding;
	ObjectMesh->SetEnableGravity(bGravity);
	ObjectMesh->SetSimulatePhysics(bGravity ? false : true);
	ObjectMesh->SetCollisionEnabled(bHolding ? ECollisionEnabled::NoCollision : ECollisionEnabled::QueryAndPhysics);

	if (HoldingComp && bHolding) {
		ObjectMesh->AttachToComponent(HoldingComp, FAttachmentTransformRules::KeepWorldTransform);
		SetActorLocation(HoldingComp->GetComponentLocation());
	}

	if (!bHolding)
	{
		ObjectMesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		ObjectMesh->SetRelativeLocationAndRotation(InitialLocation, InitialRotation);
	}
}

void APickup::OnInteract()
{
	FString pickup = FString::Printf(TEXT("Picked up: &s"), *ObjectName.ToString());

	ACharacterController* player = Cast<ACharacterController>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (player) {
		Show(false);

		player->AddToInventory(this);
	}
	GEngine->AddOnScreenDebugMessage(1, 3, FColor::White, *ObjectName.ToString());
}

void APickup::Show(bool visible) {

	ECollisionEnabled::Type collision = visible ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision;

	this->SetActorTickEnabled(visible);

	this->ObjectMesh->SetVisibility(visible);
	this->ObjectMesh->SetCollisionEnabled(collision);
	
}

