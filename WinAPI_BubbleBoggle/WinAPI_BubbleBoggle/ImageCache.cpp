#include "ImageCache.h"

namespace MomDra
{
	std::shared_ptr<Bitmap> ImageCache::LoadImg(const std::wstring& path)
	{
		auto it{ imageMap.find(path) };

		if (it != imageMap.end())
		{
			return it->second;
		}

		std::shared_ptr<Bitmap> bitMap{ std::make_shared<Bitmap>(path.data()) };

		if (bitMap)
		{
			imageMap[path] = bitMap;
		}

		return bitMap;
	}

	void ImageCache::InitGDIPlus()
	{
		GdiplusStartupInput gdiplusStartupInput;
		ULONG_PTR gdiplusToken;
		GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

		ImageCache::gdiplusToken = gdiplusToken;
	}

	void ImageCache::ShutDown()
	{
		GdiplusShutdown(gdiplusToken);
	}
}
