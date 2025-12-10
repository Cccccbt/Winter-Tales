#pragma once

#include <graphics.h>
#include <iterator>
#include <mmsystem.h>
#include <tchar.h>
#include <windows.h>

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

// Lightweight audio helpers around the Windows MCI API.
inline bool send_mci_command(LPCTSTR command, HWND notify_hwnd = NULL)
{
	MCIERROR error_code = mciSendString(command, NULL, 0, notify_hwnd);
	if (error_code != 0)
	{
		TCHAR error_buffer[256] = { 0 };
		if (mciGetErrorString(error_code, error_buffer, static_cast<UINT>(std::size(error_buffer))))
		{
			OutputDebugString(error_buffer);
			OutputDebugString(_T("\n"));
		}
		return false;
	}
	return true;
}

inline void load_audio(LPCTSTR path, LPCTSTR id)
{
	static TCHAR str_cmd[512];
	_stprintf_s(str_cmd, _T("close %s"), id);
	send_mci_command(str_cmd);  // Ensure old alias is released before reopening.

	_stprintf_s(str_cmd, _T("open %s alias %s"), path, id);
	send_mci_command(str_cmd);
}

inline void play_audio(LPCTSTR id, bool is_loop = false)
{
	static TCHAR str_cmd[512];
	_stprintf_s(str_cmd, _T("play %s %s from 0 notify"), id, is_loop ? _T("repeat") : _T(""));
	send_mci_command(str_cmd, GetHWnd());  // Use async notification to avoid blocking the UI thread.
}

inline void stop_audio(LPCTSTR id)
{
	static TCHAR str_cmd[512];
	_stprintf_s(str_cmd, _T("stop %s"), id);
	send_mci_command(str_cmd);
}

inline void close_audio(LPCTSTR id)
{
	static TCHAR str_cmd[512];
	_stprintf_s(str_cmd, _T("close %s"), id);
	send_mci_command(str_cmd);
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