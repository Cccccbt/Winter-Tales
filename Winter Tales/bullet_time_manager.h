#pragma once
#include "util.h"

class BulletTimeManager
{
public:
	enum class Status
	{
		Entering,
		Exiting
	};

	static BulletTimeManager* instance();

	void post_process();
	void set_status(Status new_status);
	float on_update(float delta);
	
	float get_progress() const
	{
		return progress;
	}

	bool is_active() const
	{
		return progress > 0.01f;  // Use small threshold to avoid floating point issues
	}

	void set_speed_progress(float speed)
	{
		SPEED_PROGRESS = speed;
	}

private:
	static BulletTimeManager* manager;

	float progress = 0.0f;
	Status status = Status::Exiting;
	float SPEED_PROGRESS = 0.5f;
	const float DST_DELTA_FACTOR = 0.25f;
	const float DST_COLOR_FACTOR = 0.25f;

	BulletTimeManager();
	~BulletTimeManager();
};