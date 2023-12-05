#pragma once
#include <map>

#include "Base Game/Engine.h"
#include "Shape/Triangle.h"
#include "Shape/Square.h"
#include "Sprite/Sprite.h"

class Game final : public Korbo::Engine
{
private:
    Sprite* Player;
    Sprite* Player2;
    Sprite* background;
    Sprite* obstacle;
    Sprite* logo1;
    Sprite* logo2;
    Entity2D* obj1;
    Entity2D* obj2;
    map<string, Animation> Animator;
    map<string, Animation> AnimatorObstacle;
    map<string, Animation> AnimatorP2;
    
    int windowWidth = 800;
    int windowHeight = 400;
public:
    Game(int windowWidth,int windowHeight);
    ~Game() override;
    void init() override;
    void update() override;
    void exit() override;
};
