#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyDicePawn.generated.h"

class UStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class DICEIO_API AMyDicePawn : public APawn
{
    GENERATED_BODY()

public:
    AMyDicePawn();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // 플레이어 컨트롤러가 호출해 줄 주사위 굴리기 함수
    void RollInDirection(FVector Direction);

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dice")
    UStaticMeshComponent* DiceMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    UCameraComponent* Camera;
};