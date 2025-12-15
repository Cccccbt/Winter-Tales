#include <chrono>
#include <cmath>
#include <graphics.h>
#include <iostream>
#include <thread>
#include "camera.h"
#include "animation.h"
#include "atlas.h"
#include "bullet_time_manager.h"
#include "character_manager.h"
#include "collision_manager.h"
#include "magic_bear_ball.h"
#include "magic_bear_ray.h"
#include "player.h"
#include "resource_manager.h"
#include "timer.h"
#include "util.h"
#include "vector2.h"

namespace
{
        void draw_sun(float time_seconds)
        {
                constexpr double PI = 3.14159265358979323846;
                constexpr double TWO_PI = PI * 2.0;

                const int center_x = getwidth() - 84;
                const int center_y = 68;

                const double pulse = std::sin(time_seconds * 1.25) * 2.5;
                const int core_radius = static_cast<int>(24 + pulse);
                const int glow_radius = core_radius + 6;

                setfillcolor(RGB(255, 236, 188));
                solidcircle(center_x, center_y, glow_radius);

                setfillcolor(RGB(255, 210, 124));
                solidcircle(center_x, center_y, core_radius);

                setfillcolor(RGB(255, 188, 92));
                solidcircle(center_x, center_y, core_radius - 6);

                setlinecolor(RGB(255, 205, 140));
                setlinestyle(PS_SOLID, 2);

                const int ray_count = 12;
                for (int i = 0; i < ray_count; ++i)
                {
                        double angle = time_seconds * 0.6 + TWO_PI * i / ray_count;
                        int inner = glow_radius + 6;
                        int outer = glow_radius + 16;

                        int x1 = center_x + static_cast<int>(std::cos(angle) * inner);
                        int y1 = center_y + static_cast<int>(std::sin(angle) * inner);
                        int x2 = center_x + static_cast<int>(std::cos(angle) * outer);
                        int y2 = center_y + static_cast<int>(std::sin(angle) * outer);

                        line(x1, y1, x2, y2);
                }

                setlinestyle(PS_SOLID, 1);
        }
}

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


        const nanoseconds frame_duration(1000000000 / 60);
        steady_clock::time_point last_tick = steady_clock::now();

        ExMessage msg;
        bool running = true;
        bool debug_mode = false;
        float ambient_time = 0.0f;
        BeginBatchDraw();

        // Game Loop
        while (running)
        {
                // Process any pending input messages and pass them to characters.
                while (peekmessage(&msg))
                {
                        if (msg.message == WM_KEYDOWN && msg.vkcode == 0x51)
                        {
                                debug_mode = !debug_mode;
                        }
                        CharacterManager::instance()->on_input(msg);
                }

                steady_clock::time_point frame_start = steady_clock::now();
                duration<float> delta = duration<float>(frame_start - last_tick);
                float scaled_delta = BulletTimeManager::instance()->on_update(delta.count());
                //Process update

                Camera::instance()->on_update(scaled_delta);
                CharacterManager::instance()->on_update(scaled_delta);
                CollisionManager::instance()->process_collide();
                ambient_time += scaled_delta;

                setbkcolor(RGB(0, 0, 0));
                cleardevice();

                putimage(0, 0, ResourceManager::instance()->find_image("background"));
                draw_sun(ambient_time);

                CharacterManager::instance()->on_render();
                if (debug_mode) CollisionManager::instance()->on_debug_render();

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
