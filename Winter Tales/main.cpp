#include <graphics.h>
#include <chrono>
#include <thread>
#include <iostream>
#include "animation.h"
#include "atlas.h"
#include "resource_manager.h"
#include "character_manager.h"
#include "timer.h"
#include "util.h"
#include "vector2.h"
#include "player.h"
#include "collision_manager.h"

int main()
{
	using namespace std::chrono;

	//HWND hwnd = initgraph(1280, 720, EW_SHOWCONSOLE);
	HWND hwnd = initgraph(576, 324);
	SetWindowText(hwnd, _T("Winter Tale"));

	try
	{
		ResourceManager::instance()->load();
	}

	catch (const LPCTSTR id)
	{
		TCHAR err_message[512];
		_stprintf_s(err_message, _T("Fail to load: %s"), id);
		MessageBox(hwnd, err_message, _T("Fail to Load File"), MB_OK | MB_ICONERROR);
		return -1;
	}

	const nanoseconds frame_duration(1000000000 / 60);
	steady_clock::time_point last_tick = steady_clock::now();

	ExMessage msg;
	bool running = true;

	BeginBatchDraw();

	
	/*
	Animation test;
	test.add_frame(ResourceManager::instance()->find_image("little_match_girl"), 22);
	test.set_interval(1.0f / 12.0f);
	test.set_is_loop(true);
	test.set_on_finished(
		[]()
		{
			std::cout << "Test\n";
		}
	);
	*/

	/*
	Player playerTest;
	playerTest.set_position(Vector2(400, 400));
	playerTest.set_enable_gravity(true);
	*/

	//Game Loop
	while (running)
	{

		while (peekmessage(&msg))
		{
			//Process User Input
			CharacterManager::instance()->on_input(msg);
		}

		steady_clock::time_point frame_start = steady_clock::now();
		duration<float> delta = duration<float>(frame_start - last_tick);

		//Process update
		CharacterManager::instance()->on_update(delta.count());
		CollisionManager::instance()->process_collide();

		setbkcolor(RGB(0, 0, 0));
		cleardevice();

		putimage(0, 0, ResourceManager::instance()->find_image("background"));
		CharacterManager::instance()->on_render();
		CollisionManager::instance()->on_debug_render();

		/*
		playerTest.on_update(delta.count());
		playerTest.on_render();
		*/
		/*
		test.set_position(Vector2(400, 400));
		test.on_update(delta.count());
		test.on_render();
		*/


		FlushBatchDraw();

		last_tick = frame_start;
		nanoseconds sleep_duration = frame_duration - (steady_clock::now() - frame_start);
		while (sleep_duration > nanoseconds(1000000000 / 60))
		{
			std::this_thread::sleep_for(sleep_duration);
		}
	}

	EndBatchDraw();

	return 0;
}