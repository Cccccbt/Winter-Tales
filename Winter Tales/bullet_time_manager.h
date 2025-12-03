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
        bool is_active() const;

private:
	static BulletTimeManager* manager;

        float progress = 0.0f;
	Status status = Status::Exiting;
	const float SPEED_PROGRESS = 2.0f;
	const float DST_DELTA_FACTOR = 0.25f;
        const float DST_COLOR_FACTOR = 0.25f;

	BulletTimeManager();
	~BulletTimeManager();

	
};