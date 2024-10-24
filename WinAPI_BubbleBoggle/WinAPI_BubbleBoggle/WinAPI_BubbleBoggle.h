#pragma once

#include "resource.h"
#include "SceneManager.h"
#include "Animator.h"
#include "ResourceManager.h"

namespace MomDra
{
    INT_PTR CALLBACK AnimationProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
    {
        static std::wstring fileName;
        static std::wstring animationName;

        static std::array<Vector2, 7> leftTops;
        static std::array<Vector2, 7> slices;

        static float duration;
        static int frameCount;
        static bool isInitial{ false };

        UNREFERENCED_PARAMETER(lParam);
        switch (message)
        {
        case WM_INITDIALOG:
        {
            if (isInitial)
            {
                for (int i = 0; i < frameCount; ++i)
                {
                    SetDlgItemText(hDlg, IDC_EDIT1_X1 + i * 2, &std::to_wstring(leftTops[i].X)[0]);
                    SetDlgItemText(hDlg, IDC_EDIT1_X1 + i * 2 + 1, &std::to_wstring(leftTops[i].Y)[0]);

                    SetDlgItemText(hDlg, IDC_EDIT1_X8 + i * 2, &std::to_wstring(slices[i].X)[0]);
                    SetDlgItemText(hDlg, IDC_EDIT1_X8 + i * 2 + 1, &std::to_wstring(slices[i].Y)[0]);
                }

                SetDlgItemText(hDlg, IDC_DURATIOJN, &std::to_wstring(duration)[0]);
                SetDlgItemText(hDlg, IDC_FRAME_COUNT, &std::to_wstring(frameCount)[0]);
                SetDlgItemText(hDlg, IDC_FILE_NAME, &fileName[0]);
                SetDlgItemText(hDlg, IDC_ANIMATION_NAME, &animationName[0]);
            }
        }
            return (INT_PTR)TRUE;

        case WM_COMMAND:

            switch (LOWORD(wParam))
            {
            case IDCANCEL:
                EndDialog(hDlg, LOWORD(wParam));
                return (INT_PTR)TRUE;

            case ID_SAVE:
            {
                const std::vector<std::unique_ptr<Object>>& objects{
                    SceneManager::GetInstance().GetCurrentScene()->GetLayerObject(Layer::Default) };

                Animator* animator{ objects[0]->GetAnimator() };

                std::wstring buffer;
                buffer.resize(256);

                HWND hwndEdit{ GetDlgItem(hDlg, IDC_FRAME_COUNT) };
                GetWindowText(hwndEdit, &buffer[0], buffer.size());
                
                frameCount = std::stoi(buffer);

                buffer.clear();
                buffer.resize(256);


                hwndEdit = GetDlgItem(hDlg, IDC_DURATIOJN);
                GetWindowText(hwndEdit, &buffer[0], buffer.size());

                duration = std::stof(buffer);

                
                buffer.clear();
                buffer.resize(256);
                
                
                // 7개가 아니라 frameCount
                for (int i = 0; i < frameCount; ++i)
                {
                    hwndEdit = GetDlgItem(hDlg, IDC_EDIT1_X1 + i * 2);
                    GetWindowText(hwndEdit, &buffer[0], buffer.size());
                    leftTops[i].X = std::stof(buffer);

                    buffer.clear();
                    buffer.resize(256);

                    hwndEdit = GetDlgItem(hDlg, IDC_EDIT1_X1 + i * 2 + 1);
                    GetWindowText(hwndEdit, &buffer[0], buffer.size());
                    leftTops[i].Y = std::stof(buffer);
                }

                for (int i = 0; i < frameCount; ++i)
                {
                    hwndEdit = GetDlgItem(hDlg, IDC_EDIT1_X8 + i * 2);
                    GetWindowText(hwndEdit, &buffer[0], buffer.size());
                    slices[i].X = std::stof(buffer);

                    buffer.clear();
                    buffer.resize(256);

                    hwndEdit = GetDlgItem(hDlg, IDC_EDIT1_X8 + i * 2 + 1);
                    GetWindowText(hwndEdit, &buffer[0], buffer.size());
                    slices[i].Y = std::stof(buffer);
                }

                int size;

                fileName.resize(256);
                animationName.resize(256);

                hwndEdit = GetDlgItem(hDlg, IDC_FILE_NAME);
                size = GetWindowText(hwndEdit, &fileName[0], fileName.size());
                fileName.resize(size);

                hwndEdit = GetDlgItem(hDlg, IDC_ANIMATION_NAME);
                size = GetWindowText(hwndEdit, &animationName[0], animationName.size());
                animationName.resize(size);
                
                std::shared_ptr<Texture> animTexture{ ResourceManager::GetInstance().LoadTexture(fileName) };

                animator->CreateAnimation(animationName, animTexture, leftTops,
                    slices, duration, frameCount);

                animator->Play(animationName, true);

                std::wstring animationFilePath{ L"\\animation\\" };
                animationFilePath.append(animationName);
                animationFilePath.append(L".anim");

                animator->FindAnimation(animationName)->Save(animationFilePath);

                isInitial = true;
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
}
