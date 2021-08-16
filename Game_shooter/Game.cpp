#include <iostream>
#include <string>
#include "Game.h"
#include "ResourceHolder.hpp"

sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game() 
    : mWindow(sf::VideoMode(640, 480), "My game")
    , mWorld(mWindow)
{
    mFont.loadFromFile("resources/fonts/Sansation.ttf");
    mStatisticText.setFont(mFont);
    mStatisticText.setPosition(5.f, 5.f);
    mStatisticText.setCharacterSize(10);
}

void Game::Run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time elapsedTime = sf::Time::Zero;
    mStatisticUpdateTime = 0;

    mWindow.setFramerateLimit(60);
    while (mWindow.isOpen())
    {
        elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;

        while (timeSinceLastUpdate > TimePerFrame)
        {

            timeSinceLastUpdate -= TimePerFrame;
            ProcessEvents();
            Update(TimePerFrame);
        }
        UpdateStatistic(elapsedTime);
        Render();
    }
}

void Game::ProcessEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            mWindow.close();
            break;
        }
            
    }
}

void Game::Update(sf::Time dTime)
{
    mWorld.Update(dTime);
}

void Game::Render()
{
    mWindow.clear();
    mWorld.Draw();

    mWindow.setView(mWindow.getDefaultView());
    mWindow.draw(mStatisticText);
    mWindow.display();
}

void Game::UpdateStatistic(sf::Time dTime)
{
    mStatisticUpdateTime += dTime.asSeconds();
    mStatisticFPS += 1;
    
    if (mStatisticUpdateTime > 1.f)
    {
        
        mStatisticText.setString("FPS = " + std::to_string(mStatisticFPS) + '\n');
        mStatisticUpdateTime -= 1.f;
        mStatisticFPS = 0;
    }
}
