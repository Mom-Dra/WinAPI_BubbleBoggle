#include "Animation.h"
#include "Object.h"
#include "Camera.h"
#include <fstream>
#include "PathManager.h"
#include "ResourceManager.h"

namespace MomDra
{
	Animation::Animation(const std::wstring& name, Animator* animator, const Vector2& scale) noexcept : name{ name }, animator{ animator }, scale{ scale }, currFrame{ 0 }, time{ 0.0f }, isFinish{ false }
	{

	}

	Animation::Animation(Animator* animator, const Vector2& scale) noexcept : animator{ animator }, scale{ scale }, currFrame{ 0 }, time{ 0.0f }, isFinish{ false }
	{

	}

	void Animation::Update() noexcept
	{
		if (isFinish) return;

		time += TimeManager::GetInstance().GetDeltaTime();

		if (frames[currFrame].duration < time)
		{
			time = time - frames[currFrame].duration;

			++currFrame;

			if (frames.size() == currFrame)
			{
				currFrame = -1;
				time = 0.0f;
				isFinish = true;
			}
		}
	}

	void Animation::Render(const HDC& hdc) const noexcept
	{
		if (isFinish) return;

		Object* owner{ animator->GetOwner() };
		Vector2 pos{ owner->GetPos() };
		
		const Vector2 offSet{ frames[currFrame].offSet };
		const Vector2 slice{ frames[currFrame].slice };
		const Vector2 leftTop{ frames[currFrame].leftTop };

		pos += offSet; // Offset만큼 추가 위치 이동

		pos = Camera::GetInstance().GetRenderPos(pos);


		TransparentBlt(hdc, static_cast<int>(pos.X - slice.X / 2.0f * scale.X), static_cast<int>(pos.Y - slice.Y / 2.0f * scale.Y), static_cast<int>(slice.X * scale.X), static_cast<int>(slice.Y * scale.Y), texture->GetDC(), static_cast<int>(leftTop.X), static_cast<int>(leftTop.Y), static_cast<int>(slice.X), static_cast<int>(slice.Y), RGB(255, 0, 255));
		// Left 코드
		//TransparentBlt(hdc, static_cast<int>(pos.X - slice.X / 2.0f * scale.X), static_cast<int>(pos.Y - slice.Y / 2.0f * scale.Y), static_cast<int>(slice.X * scale.X), static_cast<int>(slice.Y * scale.Y), texture->GetDC(), texture->GetWidth() - static_cast<int>(leftTop.X) - static_cast<int>(slice.X), static_cast<int>(leftTop.Y), static_cast<int>(slice.X), static_cast<int>(slice.Y), RGB(255, 0, 255));
		//TransparentBlt(hdc, static_cast<int>(pos.X - slice.X / 2.0f), static_cast<int>(pos.Y - slice.Y / 2.0f), static_cast<int>(slice.X), static_cast<int>(slice.Y), texture->GetDC(), static_cast<int>(leftTop.X), static_cast<int>(leftTop.Y), static_cast<int>(slice.X), static_cast<int>(slice.Y), RGB(255, 255, 255));
	}

	void Animation::Create(std::shared_ptr<Texture> texture, const Vector2& leftTop, const Vector2& sliceSize, const Vector2& step, float duration, unsigned int frameCount)
	{
		this->texture = texture;

		for (unsigned int i{ 0 }; i < frameCount; ++i)
		{
			AnimationFrame frame;
			frame.duration = duration;
			frame.slice = sliceSize;
			frame.leftTop = leftTop + step * static_cast<float>(i);

			frames.emplace_back(frame);
		}
	}

	void Animation::Create(std::shared_ptr<Texture> texture, const Vector2& leftTop, const Vector2& sliceSize, const Vector2& step, const std::initializer_list<float>& durations, unsigned int frameCount)
	{
		this->texture = texture;

		auto it{ durations.begin() };

		for (unsigned int i{ 0 }; i < frameCount; ++i)
		{
			AnimationFrame frame;
			frame.duration = *it++;
			frame.slice = sliceSize;
			frame.leftTop = leftTop + step * static_cast<float>(i);

			frames.emplace_back(frame);
		}
	}

	void Animation::Create(std::shared_ptr<Texture> texture, const std::initializer_list<Vector2>& leftTops, const Vector2& sliceSize, const std::initializer_list<float>& durations, unsigned int frameCount)
	{
		this->texture = texture;

		auto it{ durations.begin() };
		auto it2{ leftTops.begin() };

		for (unsigned int i{ 0 }; i < frameCount; ++i)
		{
			AnimationFrame frame;
			frame.duration = *it++;
			frame.slice = sliceSize;
			frame.leftTop = (*it2++);

			frames.emplace_back(frame);
		}
	}

	void Animation::Create(std::shared_ptr<Texture> texture, const std::initializer_list<Vector2>& leftTops, const std::initializer_list<Vector2>& sliceSize, float duration, unsigned int frameCount)
	{
		this->texture = texture;

		auto it2{ leftTops.begin() };
		auto it3{ sliceSize.begin() };

		for (unsigned int i{ 0 }; i < frameCount; ++i)
		{
			AnimationFrame frame;
			frame.duration = duration;
			frame.slice = *it3++;
			frame.leftTop = (*it2++);

			frames.emplace_back(frame);
		}
	}

	void Animation::Save(const std::wstring& relativePath)
	{	
		std::wstring path{ PathManager::GetContentPath() };
		path.append(relativePath);

		std::wofstream out{ path, std::ios::binary };

		out << name << L'\n';
		out << frames.size() << L'\n';
		
		for (const AnimationFrame& frame : frames)
			out << frame << L'\n';

		out << texture->GetFilePath();
	}

	void Animation::Load(const std::wstring& relativePath)
	{
		std::wstring path{ PathManager::GetContentPath() };
		path.append(relativePath);

		std::wifstream in{ path, std::ios::binary };

		in >> name;

		unsigned int size;
		in >> size;

		frames.reserve(size);

		for (unsigned int i{ 0 }; i < size; ++i)
		{
			AnimationFrame frame;
			in >> frame;

			frames.emplace_back(frame);
		}

		std::wstring textureKey;
		in >> textureKey;

		texture = ResourceManager::GetInstance().LoadTexture(textureKey);
	}
}
