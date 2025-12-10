#include <chrono>
#include <graphics.h>
#include <iostream>
#include <memory>
#include <thread>
#include "camera.h"
#include "animation.h"
#include "atlas.h"
#include "resource_manager.h"
#include "bullet_time_manager.h"
#include "character_manager.h"
#include "collision_manager.h"
#include "magic_bear_ball.h"
#include "magic_bear_ray.h"
#include "player.h"
#include "scene_manager.h"
#include "game_scene.h"
#include "timer.h"
#include "util.h"
#include "vector2.h"

// Entry point: bootstraps resources, runs the main game loop, and delegates
// updates and rendering to the managers that own scene objects.
int main()
{
        using namespace std::chrono;

        HWND hwnd = initgraph(576, 324);
        SetWindowText(hwnd, _T("Winter Tale"));

        // Load all images, atlases, and audio before starting the game loop.
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

        SceneManager* scene_manager = SceneManager::instance();
        scene_manager->register_scene("game", std::make_unique<GameScene>());
        scene_manager->switch_to("game");

        const nanoseconds frame_duration(1000000000 / 60);
        steady_clock::time_point last_tick = steady_clock::now();
	
	ExMessage msg;
	bool running = true;

        BeginBatchDraw();

        // Game Loop
        while (running)
        {
                // Process any pending input messages and pass them to the active scene.
                while (peekmessage(&msg))
                {
                        scene_manager->on_input(msg);
                }

		        steady_clock::time_point frame_start = steady_clock::now();
		        duration<float> delta = duration<float>(frame_start - last_tick);
		        float scaled_delta = BulletTimeManager::instance()->on_update(delta.count());
                        //Process update

                        scene_manager->on_update(scaled_delta);

                scene_manager->on_render();
                // CollisionManager::instance()->on_debug_render();

                FlushBatchDraw();

                // Cap to a fixed 60 FPS; sleep for the remaining frame budget.
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
