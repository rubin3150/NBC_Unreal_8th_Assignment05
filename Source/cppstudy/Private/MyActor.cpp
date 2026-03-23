// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Engine/Engine.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	// UE_LOG(LogTemp, Warning, TEXT("Change Test34444"));
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (count >= 10)
		return;

	timer += DeltaTime;

	if (timer >= 1.0f)
	{
		timer -= 1.0f;
		count++;

		Move();
		Turn();

		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, FString::Printf(TEXT("현재 %d번째 이동입니다."), count));
	}

	if (count == 10)
	{
		GEngine->AddOnScreenDebugMessage(-1, 500.0f, FColor::Cyan, FString::Printf(TEXT("움직인 모든 거리의 합계: %.1f"), totalDistance));
		GEngine->AddOnScreenDebugMessage(-1, 500.0f, FColor::Cyan, FString::Printf(TEXT("총 이벤트 발생 횟수: %d"), eventCount));
	}
}

void AMyActor::Move()
{
	if (FMath::RandRange(0, 1))
	{
		FVector originLocation = GetActorLocation();
		SetActorLocation(FVector(FMath::RandRange(1, 100), FMath::RandRange(1, 100), FMath::RandRange(1, 100)));
		FVector location = GetActorLocation();
		FString locStr = FString::Printf(TEXT("Location: X=%.1f, Y=%.1f, Z=%.1f"), location.X, location.Y, location.Z);
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, locStr);
		totalDistance += FVector::Dist(originLocation, location);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("이번 회차에 이동하지 못했습니다!")));
		eventCount++;
	}
}

void AMyActor::Turn()
{
	if (FMath::RandRange(0, 1))
	{
		SetActorRotation(FRotator(FMath::RandRange(1, 100), FMath::RandRange(1, 100), FMath::RandRange(1, 100)));
		FRotator rotation = GetActorRotation();
		FString rotStr = FString::Printf(TEXT("Rotation: P=%.1f, Y=%.1f, R=%.1f"), rotation.Pitch, rotation.Yaw, rotation.Roll);
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, rotStr);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("이번 회차에 회전하지 못했습니다!")));
		eventCount++;
	}
}