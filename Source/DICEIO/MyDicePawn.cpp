#include "MyDicePawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "UObject/ConstructorHelpers.h"

AMyDicePawn::AMyDicePawn()
{
    PrimaryActorTick.bCanEverTick = true;

    DiceMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DiceMesh"));
    RootComponent = DiceMesh;

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMeshRef(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (CubeMeshRef.Succeeded())
    {
        DiceMesh->SetStaticMesh(CubeMeshRef.Object);
        DiceMesh->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
    }

    // ==========================================
    // [중요] 주사위 물리 시뮬레이션 활성화
    // ==========================================
    DiceMesh->SetSimulatePhysics(true);
    DiceMesh->SetEnableGravity(true);
    // 주사위가 바닥에서 미끄러지지 않고 묵직하게 굴러가도록 질량/마찰 조절 가능

    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->TargetArmLength = 1200.f;
    SpringArm->SetRelativeRotation(FRotator(-70.f, 0.f, 0.f));
    SpringArm->bDoCollisionTest = false;
    // 카메라는 주사위 물리 회전에 따라 뱅글뱅글 돌지 않도록 상속을 해제합니다.
    SpringArm->bUsePawnControlRotation = false;
    SpringArm->bInheritPitch = false;
    SpringArm->bInheritYaw = false;
    SpringArm->bInheritRoll = false;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

    AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void AMyDicePawn::BeginPlay() { Super::BeginPlay(); }
void AMyDicePawn::Tick(float DeltaTime) { Super::Tick(DeltaTime); }

void AMyDicePawn::RollInDirection(FVector Direction)
{
    if (DiceMesh)
    {
        // 드래그 방향으로 튕겨 나가는 힘(충격량)을 줍니다.
        float ImpulseForce = 800.0f;
        DiceMesh->AddImpulse(Direction * ImpulseForce * DiceMesh->GetMass());

        // 굴러가는 시각적 효과를 극대화하기 위해 90도 회전 방향에 토크(회전력)도 추가로 줍니다.
        FVector TorqueAxis = FVector::CrossProduct(FVector::UpVector, Direction);
        float TorqueForce = 50000.0f;
        DiceMesh->AddTorqueInRadians(TorqueAxis * TorqueForce, NAME_None, true);
    }
}