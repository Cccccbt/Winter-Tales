#pragma once

#include <graphics.h>
#include <map>
#include <string>
#include <mmsystem.h>
#include <tchar.h>

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

// Lightweight audio helpers around the WinMM MCI API to keep MP3 playback
// working without COM dependencies while avoiding the blocking "wait"
// commands that previously caused hangs.
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

                ~Player()
                {
                        for (auto& entry : media_map_)
                        {
                                close_media(entry.second, entry.first);
                        }
                }

                void load(LPCTSTR path, LPCTSTR id)
                {
                        auto& media = media_map_[id];
                        std::basic_string<TCHAR> alias = id;
                        close_media(media, alias);
                        media.path = path;
                }

                void play(LPCTSTR id, bool is_loop)
                {
                        auto iter = media_map_.find(id);
                        if (iter == media_map_.end())
                        {
                                return;
                        }

                        Media& media = iter->second;
                        if (!ensure_media_open(iter->first, media))
                        {
                                return;
                        }

                        std::basic_string<TCHAR> seek_command = TEXT("seek ");
                        seek_command += iter->first;
                        seek_command += TEXT(" to start");
                        mciSendString(seek_command.c_str(), nullptr, 0, nullptr);

                        std::basic_string<TCHAR> command = TEXT("play ");
                        command += iter->first;
                        if (is_loop)
                        {
                                command += TEXT(" repeat");
                        }

                        mciSendString(command.c_str(), nullptr, 0, nullptr);
                }

                void stop(LPCTSTR id)
                {
                        auto iter = media_map_.find(id);
                        if (iter == media_map_.end() || !iter->second.is_open)
                        {
                                return;
                        }

                        std::basic_string<TCHAR> stop_command = TEXT("stop ");
                        stop_command += iter->first;
                        mciSendString(stop_command.c_str(), nullptr, 0, nullptr);

                        std::basic_string<TCHAR> seek_command = TEXT("seek ");
                        seek_command += iter->first;
                        seek_command += TEXT(" to start");
                        mciSendString(seek_command.c_str(), nullptr, 0, nullptr);
                }

        private:
                struct Media
                {
                        std::basic_string<TCHAR> path{};
                        bool is_open{ false };
                };

                bool ensure_media_open(const std::basic_string<TCHAR>& alias, Media& media)
                {
                        if (media.is_open)
                        {
                                return true;
                        }

                        if (media.path.empty())
                        {
                                return false;
                        }

                        std::basic_string<TCHAR> command = TEXT("open \"");
                        command += media.path;
                        command += TEXT("\" type mpegvideo alias ");
                        command += alias;

                        if (mciSendString(command.c_str(), nullptr, 0, nullptr) == 0)
                        {
                                media.is_open = true;
                                return true;
                        }

                        return false;
                }

                void close_media(Media& media, const std::basic_string<TCHAR>& alias)
                {
                        if (!media.is_open)
                        {
                                return;
                        }

                        std::basic_string<TCHAR> command = TEXT("close ");
                        command += alias;
                        mciSendString(command.c_str(), nullptr, 0, nullptr);
                        media.is_open = false;
                }

                std::map<std::basic_string<TCHAR>, Media, std::less<>> media_map_{};
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