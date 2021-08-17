#pragma once
#include <SFML/Graphics.hpp>

class World;
class PlayerController;

class Game
{
public:
    Game();
    ~Game();
    void Run();

private:
    void ProcessEvents();
    void Update(sf::Time dTime);
    void Render();
    void UpdateStatistic(sf::Time dTime);

private:
    sf::RenderWindow mWindow;
    sf::Text mStatisticText;
    sf::Font mFont;

    World * mWorld;
    PlayerController * mPlayerController;

    float mStatisticUpdateTime;
    int mStatisticFPS = 0;

};

