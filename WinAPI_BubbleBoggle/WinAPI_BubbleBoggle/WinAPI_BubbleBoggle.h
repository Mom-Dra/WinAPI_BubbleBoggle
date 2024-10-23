#pragma once

#include "resource.h"

INT_PTR CALLBACK AnimationProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    static std::array<Vector2, 7> leftTops;
    static std::array<Vector2, 7> slices;

    static float duration;
    static int frameCount;


    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:

        switch (LOWORD(wParam))
        {
        case IDCANCEL:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;

        case ID_SAVE:
            for (int i{ 0 }; i < frameCount; ++i)
            {

            }

            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;

        case ID_PLAY:



            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
    }
    return (INT_PTR)FALSE;
}