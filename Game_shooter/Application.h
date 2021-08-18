#pragma once
#include <SFML/Graphics.hpp>
#include "StateStack.h"
#include "ResourceHolder.hpp"
#include "PlayerController.h"


class Application
{

public:
    Application();

    void Run();

private:
    void Update(sf::Time dTime);
    void Render();
    void ProcessInput();

    void RegisterStates();

    void UpdateStatistic(sf::Time dTime);

private:
    static const sf::Time TimePerFrame;

    sf::RenderWindow mWindow;
    PlayerController mController;
    StateStack mStateStack;

    TexturesHolder mTextureHolder;
    FontsHolder mFontHolder;

    sf::Text mStatisticText;
    float mStatisticUpdateTime;
    int mStatisticFPS = 0;

};

