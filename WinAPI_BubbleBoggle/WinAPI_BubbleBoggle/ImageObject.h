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
        explicit ImageObject(const Vector2& pos, const Vector2& scale, const std::wstring& imgPath, const Layer& layer = Layer::DEFAULT);
        virtual ~ImageObject() = default;

        virtual void Update() noexcept override;
        virtual void Render(const HDC& hdc) const noexcept override;
    };
}
