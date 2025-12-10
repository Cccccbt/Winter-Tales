#include "game_scene.h"

void GameScene::on_input(const ExMessage& msg)
{
        CharacterManager::instance()->on_input(msg);
}

void GameScene::on_update(float delta)
{
        Camera::instance()->on_update(delta);
        CharacterManager::instance()->on_update(delta);
        CollisionManager::instance()->process_collide();
}

void GameScene::on_render()
{
        setbkcolor(RGB(0, 0, 0));
        cleardevice();

        putimage(0, 0, ResourceManager::instance()->find_image("background"));

        CharacterManager::instance()->on_render();
}
