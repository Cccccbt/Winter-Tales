#include "resource_manager.h"

struct ImageResInfo
{
	std::string id;
	LPCTSTR path;
};

struct AtlasResInfo
{
	std::string id;
	LPCTSTR path;
	int num_frame = 0;
};

ResourceManager* ResourceManager::resource_manager = nullptr;

ResourceManager* ResourceManager::instance()
{
	if (!resource_manager)
	{
		resource_manager = new ResourceManager();
	}

	return resource_manager;
}

static const std::vector<ImageResInfo> image_info_list =
{
	{"little_match_girl", _T("resources\\little_match_girl.png")},
	{"little_match_girl_attack_A_right", _T("resources\\little_match_girl_attack_A.png")},
	{"little_match_girl_attack_B_right", _T("resources\\little_match_girl_attack_B.png")},
	{"little_match_girl_idle_right", _T("resources\\little_match_girl_idle.png")},
	{"little_match_girl_roll_right", _T("resources\\little_match_girl_roll.png")},

	{"player_attack_1_right",_T("resources\\new\\pyromancer-character-sprite-sheets-pixel-art\\Pyromancer_1\\Attack_1.png")},
	{"player_attack_2_right",_T("resources\\new\\pyromancer-character-sprite-sheets-pixel-art\\Pyromancer_1\\Attack_2.png")},
	{"player_attack_3_right", _T("resources\\new\\pyromancer-character-sprite-sheets-pixel-art\\Pyromancer_1\\Attack_3.png")},
	{"player_idle_right",_T("resources\\new\\pyromancer-character-sprite-sheets-pixel-art\\Pyromancer_1\\Idle.png")},
	{"player_idle_2_right",_T("resources\\new\\pyromancer-character-sprite-sheets-pixel-art\\Pyromancer_1\\Idle_2.png")},
	{"player_run_right",_T("resources\\new\\pyromancer-character-sprite-sheets-pixel-art\\Pyromancer_1\\Run.png")},
	{"player_hurt_right",_T("resources\\new\\pyromancer-character-sprite-sheets-pixel-art\\Pyromancer_1\\Hurt.png")},
	{"player_dead_right",_T("resources\\new\\pyromancer-character-sprite-sheets-pixel-art\\Pyromancer_1\\Dead.png")},
	{"player_jump_right",_T("resources\\new\\pyromancer-character-sprite-sheets-pixel-art\\Pyromancer_1\\Jump.png")},
	{"player_charge_right", _T("resources\\new\\pyromancer-character-sprite-sheets-pixel-art\\Pyromancer_1\\Charge.png")},
	{"player_roll_right", _T("resources\\new\\pyromancer-character-sprite-sheets-pixel-art\\Pyromancer_1\\Roll.png")},
	{"background", _T("resources\\new\\snow-2d-game-tileset-pixel-art\\2 Background\\background.png")}
};

static const std::vector<AtlasResInfo> atlas_info_list =
{
	//{"enemy_attack_left", _T(_R"(resources\enemy\attack\%d.png)"), 9},
	//......
};

Atlas* ResourceManager::find_atlas(const std::string id) const
{
	const auto& itor = atlas_pool.find(id);

	if (itor == atlas_pool.end())
		return nullptr;

	return itor->second;
}

IMAGE* ResourceManager::find_image(const std::string id) const
{
	const auto& itor = image_pool.find(id);

	if (itor == image_pool.end())
		return nullptr;

	return itor->second;
}



static inline bool check_image_valid(IMAGE* image)
{
	return GetImageBuffer(image);
}

void ResourceManager::load()
{
	for (const auto& info : image_info_list)
	{
		IMAGE* img = new IMAGE();

		loadimage(img, info.path);

		if (!check_image_valid(img))
			throw info.path;
		image_pool[info.id] = img;
	}

	for (const auto& info : atlas_info_list)
	{
		Atlas* atlas = new Atlas();

		atlas->load(info.path, info.num_frame);

		for (int i = 0; i < atlas->get_size(); i++)
		{
			if (!check_image_valid(atlas->get_image(i)))
			{
				throw info.path;
			}
		}

		atlas_pool[info.id] = atlas;
	}

	//flipimage
	flip_image("little_match_girl_attack_A_right", "little_match_girl_attack_A_left");
	flip_image("little_match_girl_attack_B_right", "little_match_girl_attack_B_left");
	flip_image("little_match_girl_idle_right", "little_match_girl_idle_left");
	flip_image("little_match_girl_roll_right", "little_match_girl_roll_left");

	// Player sprite flips
	flip_image("player_attack_1_right", "player_attack_1_left", 9);
	flip_image("player_attack_2_right", "player_attack_2_left", 14);
	flip_image("player_attack_3_right", "player_attack_3_left", 6);
	flip_image("player_idle_right", "player_idle_left", 6);
	flip_image("player_idle_2_right", "player_idle_2_left", 18);
	flip_image("player_run_right", "player_run_left", 10);
	flip_image("player_hurt_right", "player_hurt_left", 4);
	flip_image("player_dead_right", "player_dead_left", 4);
	flip_image("player_jump_right", "player_jump_left", 12);
	flip_image("player_charge_right", "player_charge_left", 6);
	flip_image("player_roll_right", "player_roll_left", 16);
	
	//flipatlas
	// 
	//load_audio(_T(R"(resources\audio\bgm.mp3)"), _T("bgm"));
}

void ResourceManager::flip_image(IMAGE* src_image, IMAGE* dst_image, int num_h)
{
	int w = src_image->getwidth();
	int h = src_image->getheight();
	int w_frame = w / num_h;

	Resize(dst_image, w, h);

	DWORD* src_buffer = GetImageBuffer(src_image);
	DWORD* dst_buffer = GetImageBuffer(dst_image);

	for (int i = 0; i < num_h; i++)
	{
		for (int y = 0; y < h; y++)
		{
			for (int x = 0; x < w_frame; x++)
			{
				int src_idx = y * w + i * w_frame + x;
				int dst_idx = y * w + i * w_frame + w_frame - 1 - x;

				dst_buffer[dst_idx] = src_buffer[src_idx];
			}
		}
	}
}

void ResourceManager::flip_image(const std::string& src_id, const std::string& dst_id, int num_h)
{
	IMAGE* dst_img = new IMAGE();

	flip_image(image_pool[src_id], dst_img, num_h);

	image_pool[dst_id] = dst_img;
}

void ResourceManager::flip_atlas(const std::string& src_id, const std::string& dst_id)
{
	Atlas* dst_atlas = new Atlas();
	Atlas* src_atlas = atlas_pool[src_id];
	for (int i = 0; i < src_atlas->get_size(); i++)
	{
		IMAGE* img = new IMAGE();

		flip_image(src_atlas->get_image(i), img);

		dst_atlas->add_image(*img);
	}

	atlas_pool[dst_id] = dst_atlas;
}


ResourceManager::ResourceManager() = default;
ResourceManager::~ResourceManager() = default;
