#pragma once
#include <SFML/Graphics.hpp>
#include "World.h"

class Game
{
public:
    Game();
    void Run();

private:
    void ProcessEvents();
    void Update(sf::Time dTime);
    void Render();
    void HadlePlayerInput(sf::Keyboard::Key key, bool pressed);
    void UpdateStatistic(sf::Time dTime);

private:
    sf::RenderWindow mWindow;
    sf::Text mStatisticText;
    sf::Font mFont;

    World mWorld;

    float mStatisticUpdateTime;
    int mStatisticFPS = 0;

};

