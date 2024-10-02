#pragma once
#include "Object.h"
#include <string>
#include <memory>

class ImageObject : public Object
{
private:
    std::shared_ptr<Bitmap> bitMap;

public:
    explicit ImageObject(const Vector2& pos, const Vector2& scale, const std::wstring& imgPath);
    explicit ImageObject(const Vector2& pos, const Vector2& scale, const std::shared_ptr<Bitmap>& bitMap);
    explicit ImageObject(ImageObject&& other) noexcept;
    virtual ~ImageObject() = default;

    ImageObject& operator=(ImageObject&& other) noexcept;

    void Render(const HDC& hdc) const noexcept override;
    virtual void Update() noexcept override;
    void LoadImageFromFile(const std::wstring& imgPath);
};
