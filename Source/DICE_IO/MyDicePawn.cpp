#include "MyDicePawn.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

AMyDicePawn::AMyDicePawn()
{
    PrimaryActorTick.bCanEverTick = true;

    // 1. 주사위 메쉬 생성 및 루트 설정
    DiceMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DiceMesh"));
    RootComponent = DiceMesh;

    // 2. 스프링암 생성 및 부착
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->TargetArmLength = 1000.f; // 카메라 거리
    SpringArm->SetRelativeRotation(FRotator(-70.f, 0.f, 0.f)); // 위에서 아래를 내려다보는 각도
    SpringArm->bDoCollisionTest = false; // 카메라가 장애물에 가려도 당겨지지 않게 설정

    // 3. 카메라 생성 및 스프링암에 부착
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

void AMyDicePawn::BeginPlay() { Super::BeginPlay(); }
void AMyDicePawn::Tick(float DeltaTime) { Super::Tick(DeltaTime); }