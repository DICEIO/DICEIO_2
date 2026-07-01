#include "MyDicePlayerController.h"
#include "MyDicePawn.h"

void AMyDicePlayerController::BeginPlay()
{
    Super::BeginPlay();

    bShowMouseCursor = true;
    bEnableClickEvents = true;
    bEnableMouseOverEvents = true;
}

void AMyDicePlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    // 마우스 왼쪽 버튼 클릭 마인딩 (옛날 방식인 BindAction을 사용하여 단순화)
    if (InputComponent)
    {
        InputComponent->BindAction("LeftClick", IE_Pressed, this, &AMyDicePlayerController::OnMainClickPressed);
        InputComponent->BindAction("LeftClick", IE_Released, this, &AMyDicePlayerController::OnMainClickReleased);
    }
}

bool AMyDicePlayerController::GetMouseWorldLocation(FVector& OutLocation)
{
    FVector MousePosition, MouseDirection;
    if (DeprojectMousePositionToWorld(MousePosition, MouseDirection))
    {
        // 탑다운이므로 가상의 평면(Z=0)과 마우스 레이캐스트가 만나는 지점을 계산합니다.
        if (FMath::IsNearlyZero(MouseDirection.Z) == false)
        {
            float T = -MousePosition.Z / MouseDirection.Z;
            OutLocation = MousePosition + MouseDirection * T;
            return true;
        }
    }
    return false;
}

void AMyDicePlayerController::OnMainClickPressed()
{
    if (GetMouseWorldLocation(DragStartLocation))
    {
        bIsDragging = true;
    }
}

void AMyDicePlayerController::OnMainClickReleased()
{
    if (!bIsDragging) return;
    bIsDragging = false;

    FVector DragEndLocation;
    if (GetMouseWorldLocation(DragEndLocation))
    {
        // 드래그 방향 벡터 계산 (Z축은 무시)
        FVector DragVector = DragEndLocation - DragStartLocation;
        DragVector.Z = 0.f;

        // 너무 짧은 드래그는 무시 (오클릭 방지)
        if (DragVector.Size() > 50.f)
        {
            DragVector.Normalize();

            // 제어 중인 폰(주사위)을 가져와 움직임을 명령합니다.
            AMyDicePawn* DicePawn = Cast<AMyDicePawn>(GetPawn());
            if (DicePawn)
            {
                // 주사위에게 날아갈 드래그 방향을 넘겨줍니다.
                DicePawn->RollInDirection(DragVector);
            }
        }
    }
}