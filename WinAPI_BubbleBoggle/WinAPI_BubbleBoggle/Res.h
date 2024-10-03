#pragma once
#include <string>

class Res
{
private:
	std::wstring keyStr; // 리소스 키
	std::wstring relativePathStr; // 리소스 상대 경로

public:
	virtual ~Res() = default;

	inline void SetKey(const std::wstring& key)
	{
		keyStr = key;
	}

	inline void SetRelativePath(const std::wstring& path)
	{
		relativePathStr = path;
	}

	inline const std::wstring& GetKey()
	{
		return keyStr;
	}

	inline const std::wstring& GetRelativePath()
	{
		return relativePathStr;
	}
};
