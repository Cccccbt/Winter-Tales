#pragma once

#include <graphics.h>
#include <map>
#include <string>
#include <mmsystem.h>

#include "camera.h"

#pragma comment(lib, "WINMM.lib")
#pragma comment(lib, "MSIMG32.lib")

// Basic rectangle helper used by rendering and collision utilities.
struct Rect
{
	int x, y;
	int w, h;
};

// Draw an IMAGE with alpha transparency at the given position.
inline void putimage_alpha(int dst_x, int dst_y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();

	AlphaBlend(
		GetImageHDC(NULL),
		dst_x, dst_y, w, h,
		GetImageHDC(img),
		0, 0, w, h,
		{ AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}

// Draw an IMAGE with optional source/destination rectangles and alpha blending.
inline void putimage_ex(IMAGE* img, const Rect* rect_dst, const Rect* rect_src = nullptr)
{
	static BLENDFUNCTION blend_func = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	AlphaBlend(
		GetImageHDC(GetWorkingImage()), rect_dst->x, rect_dst->y, rect_dst->w, rect_dst->h,
		GetImageHDC(img), rect_src ? rect_src->x : 0, rect_src ? rect_src->y : 0, rect_src ? rect_src->w : img->getwidth(), rect_src ? rect_src->h : img->getheight(),
		blend_func);
}

inline void putimage_ex_camera(IMAGE* img, const Rect* rect_dst, const Rect* rect_src = nullptr)
{
	Camera* camera = Camera::instance();
	static BLENDFUNCTION blend_func = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	AlphaBlend(
		GetImageHDC(GetWorkingImage()), 
		rect_dst->x - static_cast<int>(camera->get_position().x), 
		rect_dst->y - static_cast<int>(camera->get_position().y), 
		rect_dst->w, rect_dst->h,
		GetImageHDC(img), 
		rect_src ? rect_src->x : 0, 
		rect_src ? rect_src->y : 0, 
		rect_src ? rect_src->w : img->getwidth(), 
		rect_src ? rect_src->h : img->getheight(),
		blend_func);
}

// Lightweight audio helpers around the WinMM PlaySound API to avoid MCI
// hangs without introducing COM dependencies that may be missing on some
// systems.
namespace audio
{
        class Player
        {
        public:
                static Player& instance()
                {
                        static Player self;
                        return self;
                }

                void load(LPCTSTR path, LPCTSTR id)
                {
                        media_map_[id] = path;
                }

                void play(LPCTSTR id, bool is_loop)
                {
                        auto iter = media_map_.find(id);
                        if (iter == media_map_.end())
                        {
                                return;
                        }

                        current_path_ = iter->second;
                        UINT flags = SND_FILENAME | SND_ASYNC;
                        if (is_loop)
                        {
                                flags |= SND_LOOP;
                        }

                        PlaySound(current_path_.c_str(), nullptr, flags);
                }

                void stop(LPCTSTR /*id*/)
                {
                        PlaySound(nullptr, nullptr, 0);
                }

        private:
                std::map<std::basic_string<TCHAR>, std::basic_string<TCHAR>, std::less<>> media_map_{};
                std::basic_string<TCHAR> current_path_{};
        };
} // namespace audio

inline void load_audio(LPCTSTR path, LPCTSTR id)
{
        audio::Player::instance().load(path, id);
}

inline void play_audio(LPCTSTR id, bool is_loop = false)
{
        audio::Player::instance().play(id, is_loop);
}

inline void stop_audio(LPCTSTR id)
{
        audio::Player::instance().stop(id);
}

// Return a random integer within the inclusive [min_num, max_num] range.
inline int range_random(int min_num, int max_num)
{
	return min_num + rand() % (max_num - min_num + 1);
}

inline float lerp(float a, float b, float t)
{
	return a + t * (b - a);
}