#include "ImageObject.h"
#include "ImageCache.h"

using namespace MomDra;

ImageObject::ImageObject(const Vector2& pos, const Vector2& scale, const std::wstring& imgPath) : Object{ pos, scale }, bitMap{ ImageCache::LoadImg(imgPath) }
{

}

ImageObject::ImageObject(const Vector2& pos, const Vector2& scale, const std::shared_ptr<Bitmap>& bitMap) : Object{ pos, scale }, bitMap{ bitMap }
{

}

ImageObject::ImageObject(ImageObject&& other) noexcept : bitMap{ other.bitMap }
{
    other.bitMap = nullptr;
}

ImageObject& ImageObject::operator=(ImageObject&& other) noexcept
{
    if (this != &other)
    {
        this->bitMap = other.bitMap;
        other.bitMap = nullptr;
    }
    
    return *this;
}

void ImageObject::Render(const HDC& hdc) const noexcept
{
    Graphics graphics{ hdc };
    graphics.DrawImage(bitMap.get(), 0, 0, bitMap->GetWidth(), bitMap->GetHeight());
}

void ImageObject::LoadImageFromFile(const std::wstring& imgPath)
{

}

void ImageObject::Update() noexcept
{
   
}
