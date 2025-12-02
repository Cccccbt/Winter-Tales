#pragma once
#include "resource_manager.h"
#include "character_manager.h"
#include "magic_bear_ball.h"
#include "magic_bear_ray.h"

class MagicBear : public Character
{
public:
	MagicBear();
	~MagicBear();
	virtual void on_hurt() override;
	virtual void on_input(const ExMessage& msg) override;
	virtual void on_update(float delta) override;
	virtual void on_render() override;

	void on_ball();
	void on_ray();
	void on_bite();
private:
	const float GLOBAL_ATTACK_CD = 1.0f;
	const float BALL_ATTACK_CD = 3.0f;
	const float RAY_ATTACK_CD = 5.0f;
	const float BITE_ATTACK_CD = 2.0f;
	const float WALK_SPEED = 150.0f;
	const float CLOSE_RANGE = 100.0f;
	const float FAR_RANGE = 300.0f;
	const float MID_RANGE = 200.0f;
	bool is_balling = false;
	bool is_raying = false;
	bool is_biting = false;

	std::vector<MagicBearBall*> bear_ball_list;
	std::vector<MagicBearRay*> bear_ray_list;
};