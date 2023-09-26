#include "Game.h"

// Crear un triangulo Rojo
// Mover El Triangulo en Diagonal
// Rotar El Triangulo En sentido AntiHoriario

Game::Game(int windowWidth,int windowHeight) : Engine(windowWidth,windowHeight)
{
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
    init();
}

Game::~Game()
{
    exit();
}

void Game::init() 
{

    
    triangleScale.x = 100.0f;
    triangleScale.y = 100.0f;
    triangleScale.z = 100.0f;

    trianglePos.x = 0.0f;
    trianglePos.y = 0.0f;
    trianglePos.z = 0.0f;

    triangleColor.x = 1.0f;
    triangleColor.y = 0.0f;
    triangleColor.z = 0.0f;
    triangleColor.w = 1.0f;

    redTriangle = new Triangle(getRenderer(),triangleColor,trianglePos,triangleScale);
}

void Game::update()
{
    trianglePos.x = trianglePos.x + 0.05f;
    trianglePos.y = trianglePos.y + 0.05f;
    
    redTriangle->Draw();
    redTriangle->SetPosition(trianglePos);
    redTriangle->SetRotationZ(5.0f);
}

void Game::exit() 
{
    delete redTriangle;
}