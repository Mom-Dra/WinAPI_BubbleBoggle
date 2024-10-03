#pragma once
#include <array>
#include <string>

namespace MomDra
{
	class PathManager
	{
	private:
		static inline std::wstring path;
		static inline constexpr int pathLength{ 255 };

	public:
		//static PathManager& GetInstance() noexcept;
		static void Initialize() noexcept;
		static inline const std::wstring& GetContentPath() { return path; }

	private:
		explicit PathManager() = default;
		explicit PathManager(const PathManager& other) = delete;
		PathManager& operator=(const PathManager& other) = delete;
	};
}
