#pragma once
#include "atlas.h"
#include "util.h"
#include "timer.h"
#include "vector2.h"
class Animation
{
public:
	enum class AnchorMode
	{
		Centered,
		BottomCentered
	};

	Animation()
	{
		timer.set_one_shot(false);
		timer.set_callback
		([&]()
			{
				idx_frame++;

				if (idx_frame >= frame_list.size())
				{
					idx_frame = is_loop ? 0 : frame_list.size() - 1;
				}

				if (on_finished && !is_loop)
				{
					on_finished();
				}
			}
		);
	};

	~Animation() = default;

	void reset()
	{
		idx_frame = 0;
		timer.reset();
	}

	void set_position(const Vector2& pos)
	{
		position = pos;
	}

	void set_AnchorMode(AnchorMode mode)
	{
		anchor_mode = mode;
	}

	void set_is_loop(bool loop)
	{
		is_loop = loop;
	}

	void set_on_finished(const std::function<void()>& cb)
	{
		on_finished = cb;
	}

	void set_interval(float interval)
	{
		timer.set_wait_time(interval);
	}

	void add_frame(IMAGE* img, int num_w)
	{
		int width = img->getwidth();
		int height = img->getheight();
		int width_frame = width / num_w;

		for (int i = 0; i < num_w; i++)
		{
			Rect rect_src;

			rect_src.x = i * width_frame;
			rect_src.y = 0;
			rect_src.w = width_frame;
			rect_src.h = height;

			frame_list.emplace_back(img, rect_src);
		}
	}

	void add_frame(IMAGE* img, int num_w, int num_h)
	{
		Rect rect_src;
		int width_frame = img->getwidth() / num_w;
		int height_frame = img->getheight() / num_h;

		for (int h = 0; h < num_h; h++)
		{
			for (int w = 0; w < num_w; w++)
			{
				rect_src.x = width_frame * w;
				rect_src.y = height_frame * h;

				rect_src.w = width_frame;
				rect_src.h = height_frame;

				frame_list.emplace_back(img, rect_src);
			}
		}
	}

	void add_frame(Atlas* atlas)
	{
		Rect rect_src;
		for (int i = 0; i < atlas->get_size(); i++)
		{
			rect_src.x = 0;
			rect_src.y = 0;
			rect_src.w = atlas->get_image(i)->getwidth();
			rect_src.h = atlas->get_image(i)->getheight();
			frame_list.emplace_back(atlas->get_image(i), rect_src);
		}
	}

	void on_update(float delta)
	{
		timer.on_update(delta);
	}

	void on_render()
	{
		Rect rect_dst;
		rect_dst.x = (int)(position.x - frame_list[idx_frame].rect_src.w / 2);
		rect_dst.y = (AnchorMode::Centered == anchor_mode) ? (int)(position.y - frame_list[idx_frame].rect_src.h / 2) : (int)(position.y - frame_list[idx_frame].rect_src.h);
		rect_dst.w = frame_list[idx_frame].rect_src.w;
		rect_dst.h = frame_list[idx_frame].rect_src.h;

		putimage_ex(frame_list[idx_frame].image, &rect_dst, &frame_list[idx_frame].rect_src);
	}

private:
	struct Frame
	{
		Rect rect_src;
		IMAGE* image = nullptr;
		
		Frame() = default;
		Frame(IMAGE* image, const Rect& rect_src)
			:image(image), rect_src(rect_src) 
		{

		};

		~Frame() = default;
	};

	Timer timer;
	Vector2 position;
	int idx_frame = 0;
	bool is_loop = false;
	std::vector<Frame> frame_list;
	std::function<void()> on_finished;
	AnchorMode anchor_mode = AnchorMode::Centered;
};