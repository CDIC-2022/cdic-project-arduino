#include "RestoreButtonObserver.h"
void RestoreButtonObserver::restoreIfButtonIsPressed()
{
    if (switchModule.isOn())
    {
        // Log.noticeln("");
        Log.noticeln("전력 복구 버튼이 눌렸습니다. 전류가 연결됩니다.");
        relayModule.connectElect();
    }
}