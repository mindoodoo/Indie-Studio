/*
** EPITECH PROJECT, 2022
** B-YEP-400-BER-4-1-indiestudio-josefine.mende
** File description:
** UIManager
*/

#include "UIManager.hpp"

UIManager::UIManager(std::shared_ptr<RL::Window> window) : _window(window)
{
    RL::Drawable2D *bombUp = new RL::Drawable2D("./Source/PowerUps/BombUp.png");
    RL::Drawable2D *fireUp = new RL::Drawable2D("./Source/PowerUps/PowerUp.png");
    RL::Drawable2D *speedUp = new RL::Drawable2D("./Source/PowerUps/Speed.png");
    RL::Drawable2D *wallPass = new RL::Drawable2D("./Source/PowerUps/WallsWalkable.png");

    _allIcons.push_back(bombUp);
    _allIcons.push_back(fireUp);
    _allIcons.push_back(speedUp);
    _allIcons.push_back(wallPass);
    for (RL::Drawable2D *powerUp : _allIcons)
        powerUp->resize({20, 20});
    offset = 23;
}

UIManager::~UIManager()
{
}

RL::Drawable2D* makeDrawable2DPointer(RL::Drawable2D Model, UIPos uiPos)
{
    RL::Drawable2D *ModelPointer = new RL::Drawable2D(Model.getTexture(), uiPos.x, uiPos.y);
    return ModelPointer;
}

void UIManager::createBombUp(UIPos uiPos, int amount) {
    uiPos.x += (amount - 1) * offset;
    RL::Drawable2D *bombUp = makeDrawable2DPointer(*_allIcons[0], uiPos);
    std::cout << "bomb up amount  " << amount << std::endl;
    _window->queueDrawable(bombUp);
}

void UIManager::createFireUp(UIPos uiPos, int amount) {
    uiPos.x += (amount - 2) * offset;
    uiPos.y += offset;
    RL::Drawable2D *fireUp = makeDrawable2DPointer(*_allIcons[1], uiPos);
    _window->queueDrawable(fireUp);
}

void UIManager::createSpeedUp(UIPos uiPos, int amount) {
    uiPos.x += (amount - 1) * offset;
    uiPos.y += 2 * offset;
    RL::Drawable2D *speedUp = makeDrawable2DPointer(*_allIcons[2], uiPos);
    _window->queueDrawable(speedUp);
}

void UIManager::createWallPass(UIPos uiPos) {
    uiPos.y += 3 * offset;
    RL::Drawable2D *wallPass = makeDrawable2DPointer(*_allIcons[3], uiPos);
    _window->queueDrawable(wallPass);
}
