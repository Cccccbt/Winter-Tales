#pragma once

#include <functional>

// Simple game timer that triggers a callback after a configured wait time.
class Timer
{
public:
        Timer() = default;
        ~Timer() = default;

        // Reset elapsed time and allow the timer to fire again.
        void restart()
        {
                pass_time = 0;
                shotted = false;
        }

        void set_wait_time(float time)
        {
                wait_time = time;
        }

        void set_one_shot(bool os)
        {
                one_shot = os;
        }

        // Register a function to invoke when the timer expires.
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

        // Advance the timer and fire the callback when the wait time elapses.
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
