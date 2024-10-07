#include "ImageObject.h"
#include "ResourceManager.h"
#include "KeyManager.h"

namespace MomDra
{
    ImageObject::ImageObject(const Vector2& pos, const Vector2& scale, const std::wstring& imgPath, const Layer& layer) : Object{ pos, scale, layer }
    {
        texture = ResourceManager::GetInstance().LoadTexture(imgPath);
    }

    void ImageObject::Render(const HDC& hdc) const noexcept
    {
        // �ؽ����� ���� ���� ���̸� �˾ƾ� ��
        int iWidth{ texture->GetWidth() };
        int iHeight{ texture->GetHeight() };

        const Vector2& pos{ GetPos() };

        //BitBlt(hdc, pos.X - (iWidth / 2), pos.Y - (iHeight / 2), iWidth, iHeight, texture->GetDC(), 0, 0, SRCCOPY);

        // �����ؾ� �� ������ �������� �־��ش�
        TransparentBlt(hdc, static_cast<int>(pos.X - (iWidth / 2)), static_cast<int>(pos.Y - (iHeight / 2)),
            iWidth, iHeight, texture->GetDC(), 0, 0, iWidth, iHeight, RGB(0, 0, 0));

        Object::Render(hdc);
    }

    void ImageObject::Update() noexcept
    {

    }
}
