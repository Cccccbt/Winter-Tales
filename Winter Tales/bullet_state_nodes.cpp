#include "bullet_state_nodes.h"
#include "bullet.h"

Bullet_Moving::Bullet_Moving()
{
	timer.set_wait_time(0.3f);
	timer.set_one_shot(false);
}

Bullet_Moving::~Bullet_Moving()
{
	
}

void Bullet_Moving::on_enter()
{

}

void Bullet_Moving::on_update(float delta)
{

}

void Bullet_Moving::on_exit()
{
	
}

Bullet_Destroyed::Bullet_Destroyed()
{
	
}

Bullet_Destroyed::~Bullet_Destroyed()
{
	
}

void Bullet_Destroyed::on_enter()
{
	
}

void Bullet_Destroyed::on_update(float delta)
{

}

void Bullet_Destroyed::on_exit()
{
	
}