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
		path.resize(pathLength);
		unsigned long size{ GetCurrentDirectory(pathLength, &path[0]) };
		path.resize(size);
		// 상위폴더로!
	
		path.append(L"\\contents");

		//SetWindowText(Core::GetInstance().GetHwnd(), path.data());
	}
}
