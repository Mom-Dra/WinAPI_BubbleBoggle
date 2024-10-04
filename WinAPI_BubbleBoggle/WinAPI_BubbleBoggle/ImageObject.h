#pragma once
#include "Object.h"
#include "Texture.h"
#include <string>
#include <memory>

namespace MomDra
{
    class ImageObject : public Object
    {
    private:
        std::shared_ptr<Texture> texture;

    public:
        explicit ImageObject(const Vector2& pos, const Vector2& scale, const std::wstring& imgPath);
        virtual ~ImageObject() = default;

        void Render(const HDC& hdc) const noexcept override;
        virtual void Update() noexcept override;
    };
}
