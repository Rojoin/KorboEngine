#pragma once

#include "..\src\Base Game\Engine.h"
#include "Shape/Triangle.h"

class Game final : public Korbo::Engine
{
private:
    Shape* redTriangle;
    
    Vec3 trianglePos;
    Vec3 triangleScale;
    Vec4 triangleColor;
    
    int windowWidth;
    int windowHeight;

public:
    Game(int windowWidth,int windowHeight);
    ~Game() override;
    void init() override;
    void update() override;
    void exit() override;
};
