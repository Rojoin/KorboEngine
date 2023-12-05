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
    const char* filePath3 = "../res/images/pikachu.png";
    const char* filePath2 = "../res/images/SonicFondo.png";

    Player = new Sprite(getRenderer(), {1, 1, 1, 1}, {windowWidth / 6.0f, windowHeight / 4.5f, 0.0f}, {100, 100, 0},
                     filePath,GL_NEAREST);

    Player2 = new Sprite(getRenderer(), {1, 1, 1, 1}, {windowWidth / 2.0f, windowHeight / 2.5f, 0.0f}, {100, 100, 0},
                     filePath3,GL_NEAREST);

    background = new Sprite(getRenderer(), {1, 1, 1, 1}, {windowWidth / 2.0f, windowHeight / 2.0f, 0.0f},
                      {(float)windowWidth, (float)windowHeight, 0},
                      filePath2,GL_NEAREST);

    obstacle = new Sprite(getRenderer(), {1, 1, 1, 1}, {windowWidth - 90.0f, windowHeight / 4.5f, 0.0f}, {100, 100, 0},
                          filePath,GL_NEAREST);

    logo1 = new Sprite(getRenderer(), {1, 1, 1, 1}, {50.0f, windowHeight - 30.0f, 0.0f}, {100, 100, 0},
                          filePath3,GL_NEAREST);

    logo2 = new Sprite(getRenderer(), {1, 1, 1, 1}, {windowWidth - 90.0f, windowHeight / 10.0f, 0.0f}, {250, 100, 0},
                          filePath3,GL_NEAREST);


    obj1 = new Square(getRenderer(), {1, 1, 1, 1}, {windowWidth / 4.0f, windowHeight / 2.0f, 0.0f}, {100, 100, 0});
    obj2 = new Square(getRenderer(), {1, 1, 0, 1}, {windowWidth / 2.0f, windowHeight / 2.0f, 0.0f}, {100, 100, 0});


    Animation animationPlayerRight = Animation(268, (465 / 6) * 4, 5, 0.5f, 830, 465, 36, 44);
    Animation animationPlayerLeft = Animation(268, (465 / 6) * 4, 5, 0.5f, -830, 465, 36, 44);
    Animation animationPlayerIdle = Animation(47, (465 / 6) * 4.6, 3, 0.5f, 830, 465, 33, 45);
    Animation animationObstacle = Animation(132, (465 / 6) * 7.2, 5, 0.5f, 830, 465, 49, 52);
    
    Animation animationPlayer2Right = Animation(530, 300, 4, 0.5f, 847, 396, 47, 39);
    Animation animationPlayer2Left = Animation(-530, 300, 4, 0.5f, -847, 396, -47, 39);
    Animation animationPlayer2Idle = Animation(137, 346, 3, 0.5f, 847, 396, 40, 47);

    Animation spriteLogo1 = Animation(350, 0, 1, 1.0f, 847, 396, 187, 149);
    Animation spriteLogo2 = Animation(593, 93, 1, 1.0f, 847, 396, 253, 42);

    Animator.insert_or_assign("Right", animationPlayerRight);
    Animator.insert_or_assign("Left", animationPlayerLeft);
    Animator.insert_or_assign("Idle", animationPlayerIdle);
    
    AnimatorP2.insert_or_assign("Right", animationPlayer2Right);
    AnimatorP2.insert_or_assign("Left", animationPlayer2Left);
    AnimatorP2.insert_or_assign("Idle", animationPlayer2Idle);

    
    AnimatorObstacle.insert_or_assign("ObstacleIdle", animationObstacle);
    AnimatorObstacle.insert_or_assign("logo1", spriteLogo1);
    AnimatorObstacle.insert_or_assign("logo2", spriteLogo2);
}

void Game::update()
{
    Vec3 newPos = {Player->GetPosition().x, Player->GetPosition().y, Player->GetPosition().z};
    Vec3 newPos2 = {Player2->GetPosition().x, Player2->GetPosition().y, Player2->GetPosition().z};
    float speed = 5.0f;

    bool hasBeenPressed = false;
    bool hasBeenPressed2 = false;
    
    if (input->isKeyPressed(KeyKode::KEY_A))
    {
        newPos.x -= speed;
        Player->SetPosition(newPos);
        Player->ChangeAnimation(Animator["Left"]);
        hasBeenPressed = true;
        Colitions::CheckCollitions(Player, obstacle);
        Colitions::CheckCollitions(Player, Player2);
    }
    if (input->isKeyPressed(KeyKode::KEY_W))
    {
        newPos.y += speed;
        Player->SetPosition(newPos);
        Player->ChangeAnimation(Animator["Right"]);
        hasBeenPressed = true;
        Colitions::CheckCollitions(Player, obstacle);
        Colitions::CheckCollitions(Player, Player2);
    }
    if (input->isKeyPressed(KeyKode::KEY_S))
    {
        newPos.y -= speed;
        Player->SetPosition(newPos);
        Player->ChangeAnimation(Animator["Right"]);
        hasBeenPressed = true;
        Colitions::CheckCollitions(Player, obstacle);
        Colitions::CheckCollitions(Player, Player2);
    }
    if (input->isKeyPressed(KeyKode::KEY_D))
    {
        newPos.x += speed;
        Player->SetPosition(newPos);
        Player->ChangeAnimation(Animator["Right"]);
        hasBeenPressed = true;
        Colitions::CheckCollitions(Player, obstacle);
        Colitions::CheckCollitions(Player, Player2);
    }

    if (input->isKeyPressed(KeyKode::KEY_LEFT))
    {
        newPos2.x -= speed;
        Player2->SetPosition(newPos2);
        Player2->ChangeAnimation(AnimatorP2["Left"]);
        hasBeenPressed2 = true;
        Colitions::CheckCollitions(Player2, obstacle);
        Colitions::CheckCollitions(Player, Player2);
    }
    if (input->isKeyPressed(KeyKode::KEY_UP))
    {
        newPos2.y += speed;
        Player2->SetPosition(newPos2);
        Player2->ChangeAnimation(AnimatorP2["Right"]);
        hasBeenPressed2 = true;
        Colitions::CheckCollitions(Player2, obstacle);
        Colitions::CheckCollitions(Player, Player2);
    }
    if (input->isKeyPressed(KeyKode::KEY_DOWN))
    {
        newPos2.y -= speed;
        Player2->SetPosition(newPos2);
        Player2->ChangeAnimation(AnimatorP2["Right"]);
        hasBeenPressed2 = true;
        Colitions::CheckCollitions(Player2, obstacle);
        Colitions::CheckCollitions(Player, Player2);
    }
    if (input->isKeyPressed(KeyKode::KEY_RIGHT))
    {
        newPos2.x += speed;
        Player2->SetPosition(newPos2);
        Player2->ChangeAnimation(AnimatorP2["Right"]);
        hasBeenPressed2 = true;
        Colitions::CheckCollitions(Player2, obstacle);
        Colitions::CheckCollitions(Player, Player2);
    }

    

    if (Colitions::CheckCollitions(obstacle, Player))
    {
        cout << "Collision" << endl;
    }

    if (!hasBeenPressed)
    {
        Player->ChangeAnimation(Animator["Idle"]);
    }
    
    if (!hasBeenPressed2)
    {
        Player2->ChangeAnimation(AnimatorP2["Idle"]);
    }

    obstacle->ChangeAnimation(AnimatorObstacle["ObstacleIdle"]);
    logo1->ChangeAnimation(AnimatorObstacle["logo1"]);
    logo2->ChangeAnimation(AnimatorObstacle["logo2"]);


    background->Draw();
    Player->UpdateAnimation();
    Player->Draw();
    Player2->UpdateAnimation();
    Player2->Draw();
    obstacle->Draw();
    obstacle->UpdateAnimation();
    logo1->Draw();
    logo1->UpdateAnimation();
    logo2->Draw();
    logo2->UpdateAnimation();
}

void Game::exit()
{
    delete background;
    delete Player;
    delete Player2;
    delete obstacle;
    delete obj1;
    delete obj2;
    delete logo1;
    delete logo2;
}
