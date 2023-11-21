#include "Game.h"
#include "Input/Input.h"
#include "Sprite/Sprite.h"

Game::Game(int windowWidth, int windowHeight) : Engine(windowWidth, windowHeight)
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
    const char* filePath = "../res/images/Sonic_Mania_Sprite_Sheet.png";
    const char* filePath2 = "../res/images/SonicFondo.png";

    aux = new Sprite(getRenderer(), {1, 1, 1, 1}, {windowWidth / 6.0f, windowHeight / 4.5f, 0.0f}, {100, 100, 0},
                     filePath,GL_NEAREST);

    aux2 = new Sprite(getRenderer(), {1, 1, 1, 1}, {windowWidth / 2.0f, windowHeight / 2.0f, 0.0f},
                      {(float)windowWidth, (float)windowHeight, 0},
                      filePath2,GL_NEAREST);

    obstacle = new Sprite(getRenderer(), {1, 1, 1, 1}, {windowWidth - 90.0f, windowHeight / 4.5f, 0.0f}, {100, 100, 0},
                          filePath,GL_NEAREST);


    obj1 = new Square(getRenderer(), {1, 1, 1, 1}, {windowWidth / 4.0f, windowHeight / 2.0f, 0.0f}, {100, 100, 0});
    obj2 = new Square(getRenderer(), {1, 1, 0, 1}, {windowWidth / 2.0f, windowHeight / 2.0f, 0.0f}, {100, 100, 0});


    Animation animationPlayerRight = Animation(268, (465 / 6) * 4, 5, 1.2f, 830, 465, 36, 44);
    Animation animationPlayerIdle = Animation(47, (465 / 6) * 4.6, 3, 1.0f, 830, 465, 33, 45);
    Animation animationObstacle = Animation(132, (465 / 6) * 7.2, 5, 1.0f, 830, 465, 49, 52);

    Animator.insert_or_assign("Right", animationPlayerRight);
    Animator.insert_or_assign("Idle", animationPlayerIdle);
    AnimatorObstacle.insert_or_assign("ObstacleIdle", animationObstacle);
}

void Game::update()
{
    Vec3 newPos = {aux->GetPosition().x, aux->GetPosition().y, aux->GetPosition().z};
    Vec3 newPos2 = {0, 0, 0};

    bool hasBeenPressed = false;
    if (input->isKeyPressed(KeyKode::KEY_A))
    {
        newPos.x -= 2.0f;
        aux->SetPosition(newPos);
        aux->ChangeAnimation(Animator["Right"]);
        hasBeenPressed = true;
    }
    if (input->isKeyPressed(KeyKode::KEY_W))
    {
        newPos.y += 2.0f;
        aux->SetPosition(newPos);
        aux->ChangeAnimation(Animator["Right"]);
        hasBeenPressed = true;
    }
    if (input->isKeyPressed(KeyKode::KEY_S))
    {
        newPos.y -= 2.0f;
        aux->SetPosition(newPos);
        aux->ChangeAnimation(Animator["Right"]);
        hasBeenPressed = true;
    }
    if (input->isKeyPressed(KeyKode::KEY_D))
    {
        newPos.x += 2.0f;
        aux->SetPosition(newPos);
        aux->ChangeAnimation(Animator["Right"]);
        hasBeenPressed = true;
    }

    if (!hasBeenPressed)
    {
        aux->ChangeAnimation(Animator["Idle"]);
    }

    if (input->isKeyPressed(KeyKode::KEY_RIGHT))
    {
        newPos2.x = aux->GetPosition().x + 1.0f;
        aux->SetPosition(newPos2);
    }

    if (input->isKeyPressed(KeyKode::KEY_LEFT))
    {
        newPos2.x = aux->GetPosition().x - 1.0f;
        aux->SetPosition(newPos2);
    }

    if (Colitions::CheckCollitions(aux, obstacle))
    {
        cout << "Collision" << endl;
    }

    obstacle->ChangeAnimation(AnimatorObstacle["ObstacleIdle"]);


    aux2->Draw();
    aux->UpdateAnimation();
    aux->Draw();
    obstacle->Draw();
    obstacle->UpdateAnimation();
}

void Game::exit()
{
    delete aux;
    delete aux2;
    delete obj1;
    delete obj2;
}
