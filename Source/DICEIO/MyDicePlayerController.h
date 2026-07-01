#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyDicePlayerController.generated.h"

UCLASS()
class DICEIO_API AMyDicePlayerController : public APlayerController
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

    // 마우스 버튼 입력 처리 함수
    void OnMainClickPressed();
    void OnMainClickReleased();

private:
    // 드래그 시작점과 끝점을 저장할 변수
    FVector DragStartLocation;
    bool bIsDragging = false;

    // 마우스 커서 아래의 바닥(월드) 공간 좌표를 계산하는 함수
    bool GetMouseWorldLocation(FVector& OutLocation);
};