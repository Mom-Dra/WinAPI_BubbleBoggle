#include "PathManager.h"
#include "framework.h"
#include "Core.h"

namespace MomDra
{
	/*PathManager& PathManager::GetInstance() noexcept
	{
		static PathManager instance;

		return instance;
	}*/

	void PathManager::Initialize() noexcept
	{
		contentPath.resize(pathLength);
		unsigned long size{ GetCurrentDirectory(pathLength, &contentPath[0]) };
		contentPath.resize(size);
		// 상위폴더로!
	
		contentPath.append(L"\\contents");

		//SetWindowText(Core::GetInstance().GetHwnd(), path.data());
	}

	std::wstring PathManager::GetRelativePath(const std::wstring& absolutePath)
	{
		std::wstring relativePath{ absolutePath.substr(contentPath.size(), absolutePath.size() - contentPath.size()) };

		return relativePath;
	}
}
