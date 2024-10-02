#pragma once
#include "framework.h"
#include <unordered_map>
#include <string>
#include <memory>

namespace MomDra
{
	class ImageCache
	{
	private:
		static inline std::unordered_map<std::wstring, std::shared_ptr<Bitmap>> imageMap;
		static inline ULONG_PTR gdiplusToken{ 0 };

	public:
		static std::shared_ptr<Bitmap> LoadImg(const std::wstring& path);
		static inline const std::wstring playerImgPath{ L"../img/player/player.png" };
		//static inline const std::wstring monsterImgPath{}

		static void InitGDIPlus();
		static void ShutDown();

	private:
		explicit ImageCache() = default;
		~ImageCache() = default;
	};
}
