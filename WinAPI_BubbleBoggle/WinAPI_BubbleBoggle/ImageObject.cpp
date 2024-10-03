#include "ImageObject.h"
#include "ImageCache.h"

using namespace MomDra;

ImageObject::ImageObject(const Vector2& pos, const Vector2& scale, const std::wstring& imgPath) : Object{ pos, scale }, texture{ imgPath }
{

}

void ImageObject::Render(const HDC& hdc) const noexcept
{
    // 텍스쳐의 가로 세로 길이를 알아야 함
    int iWidth{ texture.GetWidth() };
    int iHeight{ texture.GetHeight() };

    Vector2 pos{ GetPos() };

    pos.X = (iWidth / 2);
    pos.Y = (iHeight / 2);

    BitBlt(hdc, pos.X - (iWidth / 2), pos.Y - (iHeight / 2), iWidth, iHeight, texture.GetDC(), 0, 0, SRCCOPY);

    // 무시해야 할 색상을 마지막에 넣어준다
    //TransparentBlt(hdc, pos.X - (iWidth / 2), pos.Y - (iHeight / 2), iWidth, iHeight, texture.GetDC(), 0, 0, iWidth, iHeight, );
}

void ImageObject::Update() noexcept
{

}
