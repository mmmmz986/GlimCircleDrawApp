#include "pch.h"
#include "RandomMoveThread.h"
#include "MainController.h"
#include "Define.h"
#include "GlimCircleDrawAppDlg.h"

UINT RandomMoveThreadProc(LPVOID pParam)
{
    MainController* pController = reinterpret_cast<MainController*>(pParam);

    if (pController == nullptr)
        return 0;

    CRect boundary(20, 20, 700, 500);

    pController->RandomMoveCount = 0;

    for (int i = 0; i < RANDOM_MOVE_REPEAT; i++)
    {
		pController->RandomMoveStep(boundary);

		pController->RandomMoveCount++;

        Sleep(RANDOM_MOVE_INTERVAL_MS);
    }

    return 0;
}