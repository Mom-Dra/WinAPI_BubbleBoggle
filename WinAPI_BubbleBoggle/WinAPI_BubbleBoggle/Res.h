#pragma once
#include <string>

namespace MomDra
{
	class Res
	{
	private:
		std::wstring filePath; // ���ҽ� Ű

	public:
		explicit Res(const std::wstring& filePath) noexcept;
		virtual ~Res() = default;

		inline void SetFilePath(const std::wstring& filePath) { this->filePath = filePath; }
		inline const std::wstring& GetFilePath() { return filePath; }
	};
}
