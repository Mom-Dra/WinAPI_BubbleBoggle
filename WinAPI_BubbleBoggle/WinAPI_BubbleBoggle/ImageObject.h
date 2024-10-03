#pragma once
#include "Object.h"
#include "Texture.h"
#include <string>
#include <memory>

class ImageObject : public Object
{
private:
    Texture texture;

public:
    explicit ImageObject(const Vector2& pos, const Vector2& scale, const std::wstring& imgPath);

    //explicit ImageObject(ImageObject&& other) noexcept;

    //explicit ImageObject(const ImageObject& other) noexcept = delete;
    virtual ~ImageObject() = default;

    //ImageObject& operator=(ImageObject&& other) noexcept;

    void Render(const HDC& hdc) const noexcept override;
    virtual void Update() noexcept override;
};
