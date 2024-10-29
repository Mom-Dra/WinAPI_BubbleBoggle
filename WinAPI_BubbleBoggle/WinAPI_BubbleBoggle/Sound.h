#pragma once
#include "ResourceManager.h"
#include "SoundManager.h"

namespace MomDra
{
	class Sound : public Res, public std::enable_shared_from_this<Sound>
	{
	private:
		LPDIRECTSOUNDBUFFER soundBuffer;
		DSBUFFERDESC buffInfo;
		int volume;

	public:
		explicit Sound(const std::wstring& filePath);
		virtual ~Sound();

		int Load(const std::wstring& path);

		// 일반 재생
		void Play(bool loop = false);

		// BGM 으로 재생
		void PlayToBGM(bool loop = false);

		void Stop(bool reset = false);

		// 볼륨 범위 (0 ~ 100)
		void SetVolume(float volume);

		// 음악파일 위치 조정
		// 0 ~ 100 사이
		void SetPosition(float position);

	private:
		bool LoadWaveSound(const std::wstring& path);
		int GetDecibel(float volume);
	};
}
