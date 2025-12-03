#include "bullet_time_manager.h"

BulletTimeManager* BulletTimeManager::manager = nullptr;

BulletTimeManager* BulletTimeManager::instance()
{
	if (!manager)
	{
		manager = new BulletTimeManager();
	}
	return manager;
}

void BulletTimeManager::post_process()
{
	DWORD* buffer = GetImageBuffer();
	int w = getwidth(), h = getheight();
	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			int idx = y * w + x;
			DWORD& pixel = buffer[idx];
			BYTE a = (pixel >> 24) & 0xFF;
			BYTE r = (pixel >> 16) & 0xFF;
			BYTE g = (pixel >> 8) & 0xFF;
			BYTE b = pixel & 0xFF;
			r = static_cast<BYTE>GetRValue(pixel) * lerp(1.0f, DST_COLOR_FACTOR, progress);
			g = static_cast<BYTE>GetGValue(pixel) * lerp(1.0f, DST_COLOR_FACTOR, progress);
			b = static_cast<BYTE>GetBValue(pixel) * lerp(1.0f, DST_COLOR_FACTOR, progress);
			buffer[idx] = BGR(RGB(r, g, b)) | ((DWORD)(BYTE)(255) << 24);
		}
	}
}

void BulletTimeManager::set_status(Status new_status)
{
	status = new_status;
}

float BulletTimeManager::on_update(float delta)
{
	float delta_progress = SPEED_PROGRESS * delta;
	progress += (status == Status::Entering) ? delta_progress : -delta_progress;

	if (progress < 0.0f)
	{
		progress = 0.0f;
	}
	else if (progress > 1.0f)
	{
		progress = 1.0f;
	}

	return delta * lerp(1.0f, DST_DELTA_FACTOR, progress);
}

BulletTimeManager::BulletTimeManager() = default;
BulletTimeManager::~BulletTimeManager() = default;