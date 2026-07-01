#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyDicePawn.generated.h"

UCLASS()
class DICIO_API AMyDicePawn : public APawn
{
    GENERATED_BODY()

public:
    AMyDicePawn();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // C++에서 컴포넌트를 선언하고 블루프린트에서 디테일을 볼 수 있도록 설정
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dice")
    class UStaticMeshComponent* DiceMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    class USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
    class UCameraComponent* Camera;
};