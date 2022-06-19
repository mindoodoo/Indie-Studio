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
    RL::Drawable2D *coin = new RL::Drawable2D("./Source/PowerUps/icon.png");

    _allIcons.push_back(bombUp);
    _allIcons.push_back(fireUp);
    _allIcons.push_back(speedUp);
    _allIcons.push_back(wallPass);
    _allIcons.push_back(coin);
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

void UIManager::createBombUp(UIPos uiPos, int amount, bool continueToRight) {
    if (continueToRight)
        uiPos.x += (amount - 1) * offset;
    else
        uiPos.x -= (amount - 1) * offset;
    RL::Drawable2D *bombUp = makeDrawable2DPointer(*_allIcons[0], uiPos);
    _window->queueDrawable(bombUp);
}

void UIManager::createFireUp(UIPos uiPos, int amount, bool continueToRight) {
    if (continueToRight)
        uiPos.x += (amount - 2) * offset;
    else
        uiPos.x -= (amount - 2) * offset;
    uiPos.y += offset;
    RL::Drawable2D *fireUp = makeDrawable2DPointer(*_allIcons[1], uiPos);
    _window->queueDrawable(fireUp);
}

void UIManager::createSpeedUp(UIPos uiPos, int amount, bool continueToRight) {
    if (continueToRight)
        uiPos.x += (amount - 1) * offset;
    else
        uiPos.x -= (amount - 1) * offset;
    uiPos.y += 2 * offset;
    RL::Drawable2D *speedUp = makeDrawable2DPointer(*_allIcons[2], uiPos);
    _window->queueDrawable(speedUp);
}

void UIManager::createWallPass(UIPos uiPos) {
    uiPos.y += 3 * offset;
    RL::Drawable2D *wallPass = makeDrawable2DPointer(*_allIcons[3], uiPos);
    _window->queueDrawable(wallPass);
}

void UIManager::createCoin(UIPos uiPos, int amount, bool continueToRight) {
    int sub = 0;
    if (amount > 15) {
        uiPos.y += 1 * offset;
        sub = 15;
    } else if (amount > 10) {
        uiPos.y += 2 * offset;
        sub = 10;
    } else if (amount > 5) {
        uiPos.y += 2 * offset;
        sub = 5;
    }
    if (continueToRight)
        uiPos.x += (amount - sub - 1) * offset;
    else
        uiPos.x -= (amount - sub - 1) * offset;
    RL::Drawable2D *coin = makeDrawable2DPointer(*_allIcons[4], uiPos);
    _window->queueDrawable(coin);
}
