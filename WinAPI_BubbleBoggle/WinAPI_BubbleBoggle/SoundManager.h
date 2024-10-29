#pragma once

#include <mmsystem.h>
#include <dsound.h>
#include <dinput.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dsound.lib")

namespace MomDra
{
	class Sound;

	class SoundManager
	{
	private:
		LPDIRECTSOUND8 sound; // 사운드 카드 대표 객체
		std::shared_ptr<Sound> bgm; // 현재 지정된 BGM Sound

	public:
		static inline SoundManager& GetInstance()
		{
			static SoundManager instance;
			return instance;
		}

		int Initialize();
		inline LPDIRECTSOUND8 GetSoundDevice() { return sound; }
		void RegisterToBGM(std::shared_ptr<Sound> sound);

	private:
		explicit SoundManager() noexcept = default;
		explicit SoundManager(const SoundManager& other) noexcept = delete;
		explicit SoundManager(SoundManager&& other) noexcept = delete;

		SoundManager& operator=(const SoundManager& other) noexcept = delete;
		SoundManager& operator=(SoundManager&& other) noexcept = delete;
	};
}
