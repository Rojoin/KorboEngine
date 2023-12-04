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

    Player = new Sprite(getRenderer(), {1, 1, 1, 1}, {windowWidth / 6.0f, windowHeight / 4.5f, 0.0f}, {100, 100, 0},
                     filePath,GL_NEAREST);

    background = new Sprite(getRenderer(), {1, 1, 1, 1}, {windowWidth / 2.0f, windowHeight / 2.0f, 0.0f},
                      {(float)windowWidth, (float)windowHeight, 0},
                      filePath2,GL_NEAREST);

    obstacle = new Sprite(getRenderer(), {1, 1, 1, 1}, {windowWidth - 90.0f, windowHeight / 4.5f, 0.0f}, {100, 100, 0},
                          filePath,GL_NEAREST);


    obj1 = new Square(getRenderer(), {1, 1, 1, 1}, {windowWidth / 4.0f, windowHeight / 2.0f, 0.0f}, {100, 100, 0});
    obj2 = new Square(getRenderer(), {1, 1, 0, 1}, {windowWidth / 2.0f, windowHeight / 2.0f, 0.0f}, {100, 100, 0});


    Animation animationPlayerRight = Animation(268, (465 / 6) * 4, 5, 1.2f, 830, 465, 36, 44);
    Animation animationPlayerLeft = Animation(268, (465 / 6) * 4, 5, 1.2f, -830, 465, 36, 44);
    Animation animationPlayerIdle = Animation(47, (465 / 6) * 4.6, 3, 1.0f, 830, 465, 33, 45);
    Animation animationObstacle = Animation(132, (465 / 6) * 7.2, 5, 1.0f, 830, 465, 49, 52);

    Animator.insert_or_assign("Right", animationPlayerRight);
    Animator.insert_or_assign("Left", animationPlayerLeft);
    Animator.insert_or_assign("Idle", animationPlayerIdle);
    AnimatorObstacle.insert_or_assign("ObstacleIdle", animationObstacle);
}

void Game::update()
{
    Vec3 newPos = {Player->GetPosition().x, Player->GetPosition().y, Player->GetPosition().z};
    Vec3 newPos2 = {0, 0, 0};
    float speed = 5.0f;

    bool hasBeenPressed = false;
    if (input->isKeyPressed(KeyKode::KEY_A))
    {
        newPos.x -= speed;
        Player->SetPosition(newPos);
        Player->ChangeAnimation(Animator["Left"]);
        hasBeenPressed = true;
        Colitions::CheckCollitions(Player, obstacle);
    }
    if (input->isKeyPressed(KeyKode::KEY_W))
    {
        newPos.y += speed;
        Player->SetPosition(newPos);
        Player->ChangeAnimation(Animator["Right"]);
        hasBeenPressed = true;
        Colitions::CheckCollitions(Player, obstacle);
    }
    if (input->isKeyPressed(KeyKode::KEY_S))
    {
        newPos.y -= speed;
        Player->SetPosition(newPos);
        Player->ChangeAnimation(Animator["Right"]);
        hasBeenPressed = true;
        Colitions::CheckCollitions(Player, obstacle);
    }
    if (input->isKeyPressed(KeyKode::KEY_D))
    {
        newPos.x += speed;
        Player->SetPosition(newPos);
        Player->ChangeAnimation(Animator["Right"]);
        hasBeenPressed = true;
        Colitions::CheckCollitions(Player, obstacle);
    }

    if (!hasBeenPressed)
    {
        Player->ChangeAnimation(Animator["Idle"]);
    }

    if (input->isKeyPressed(KeyKode::KEY_RIGHT))
    {
        newPos2.x = Player->GetPosition().x + speed;
        Player->SetPosition(newPos2);
        Colitions::CheckCollitions(Player, obstacle);
    }

    if (input->isKeyPressed(KeyKode::KEY_LEFT))
    {
        newPos2.x = Player->GetPosition().x - speed;
        Player->SetPosition(newPos2);
        Colitions::CheckCollitions(Player, obstacle);
    }

    if (Colitions::CheckCollitions(obstacle, Player))
    {
        cout << "Collision" << endl;
    }

    obstacle->ChangeAnimation(AnimatorObstacle["ObstacleIdle"]);


    background->Draw();
    Player->UpdateAnimation();
    Player->Draw();
    obstacle->Draw();
    obstacle->UpdateAnimation();
}

void Game::exit()
{
    delete background;
    delete Player;
    delete obstacle;
    delete obj1;
    delete obj2;
}
