#pragma once
#include <string>

class Res
{
private:
	std::wstring keyStr; // ���ҽ� Ű
	std::wstring relativePathStr; // ���ҽ� ��� ���

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
