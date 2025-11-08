#pragma once
#include <functional>

class Timer
{
public:
	Timer() = default;
	~Timer() = default;

	void restart()
	{
		pass_time = 0;
		wait_time = 0;
	}

	void set_wait_time(float time)
	{
		wait_time = time;
	}

	void set_one_shot(bool os)
	{
		one_shot = os;
	}

	void set_callback(const std::function<void()>& cb)
	{
		callback = cb;
	}

	void pause()
	{
		paused = true;
	}

	void resume()
	{
		paused = false;
	}

	void on_update(float delta_time)
	{
		if (paused)
			return;

		pass_time += delta_time;
		if (pass_time >= wait_time)
		{
			if (callback && (!one_shot || (one_shot && !shotted)))
			{
				callback();
				shotted = true;
			}

			pass_time = 0;
			shotted = true;
		}
	}

private:
	float pass_time = 0;
	float wait_time = 0;
	bool one_shot = false;
	bool shotted = false;
	bool paused = false;
	std::function<void()> callback;
};