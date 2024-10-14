#pragma once
#include <array>
#include <string>

namespace MomDra
{
	class PathManager
	{
	private:
		static inline std::wstring contentPath;
		static inline constexpr int pathLength{ 256 };

	public:
		//static PathManager& GetInstance() noexcept;
		static void Initialize() noexcept;
		static inline const std::wstring& GetContentPath() { return contentPath; }
		static std::wstring GetRelativePath(const std::wstring& absolutePath);

	private:
		explicit PathManager() = default;
		explicit PathManager(const PathManager& other) = delete;
		PathManager& operator=(const PathManager& other) = delete;
	};
}
