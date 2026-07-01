#include "MyDiceGameMode.h"
#include "MyDicePawn.h"
#include "MyDicePlayerController.h"

AMyDiceGameMode::AMyDiceGameMode()
{
    // 기본 생성될 폰과 플레이어 컨트롤러를 우리가 만든 C++ 클래스로 강제 지정
    DefaultPawnClass = AMyDicePawn::StaticClass();
    PlayerControllerClass = AMyDicePlayerController::StaticClass();
}