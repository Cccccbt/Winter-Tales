#include "bullet_time_manager.h"
#include <iostream>

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
	
	if (!buffer || w <= 0 || h <= 0)
		return;

	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			int idx = y * w + x;
			DWORD pixel = buffer[idx];

			// Extract ARGB components from the pixel
			// In Windows GDI: pixel = 0xAABBGGRR (AA=alpha, BB=blue, GG=green, RR=red)
			BYTE r = (pixel >> 0) & 0xFF;
			BYTE g = (pixel >> 8) & 0xFF;
			BYTE b = (pixel >> 16) & 0xFF;
			BYTE a = (pixel >> 24) & 0xFF;

			// Apply color factor
			r = static_cast<BYTE>(r * lerp(1, DST_COLOR_FACTOR, progress)); // You said you replaced lerp with 1
			g = static_cast<BYTE>(g * lerp(1, DST_COLOR_FACTOR, progress));
			b = static_cast<BYTE>(b * lerp(1, DST_COLOR_FACTOR, progress));

			// Reconstruct pixel in ARGB format (no BGR/RGB macro needed)
			buffer[idx] = (a << 24) | (b << 16) | (g << 8) | r;
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