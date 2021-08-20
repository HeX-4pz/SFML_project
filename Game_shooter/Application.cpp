#include "Application.h"
#include "StateIntro.h"
#include "StateLoading.h"
#include "StateMainMenu.h"
#include "StateGame.h"

const sf::Time Application::TimePerFrame = sf::seconds(1.f / 60.f);

Application::Application()
    : mWindow(sf::VideoMode(640, 480), "My game", sf::Style::Close)
    , mTextureHolder()
    , mFontHolder()
    , mController()
    , mStateStack(Context(mWindow, mTextureHolder, mFontHolder, mController))
{
    mTextureHolder.Load(Textures::ID::Title, "resources/tex/title.png");
    mTextureHolder.Load(Textures::ID::Loading, "resources/tex/loading.png");
    mFontHolder.Load(Fonts::Main, "resources/fonts/Sansation.ttf");
    
    mStatisticText.setFont(mFontHolder.Get(Fonts::Main));
    mStatisticText.setPosition(5.f, 5.f);
    mStatisticText.setCharacterSize(10);

    RegisterStates();
    mStateStack.PushState(States::StartScreen);
}

void Application::Run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time elapsedTime = sf::Time::Zero;
    mStatisticUpdateTime = 0;

    mWindow.setFramerateLimit(60 + 1);
    while (mWindow.isOpen())
    {
        elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;

        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            ProcessInput();
            Update(TimePerFrame);

            if (mStateStack.IsEmpty())
            {
                mWindow.close();
            }
        }

        UpdateStatistic(elapsedTime);
        Render();
    }
}

void Application::Update(sf::Time dTime)
{
    mStateStack.Update(dTime);
}

void Application::Render()
{
    mWindow.clear();
    mStateStack.Draw();

    mWindow.setView(mWindow.getDefaultView());
    mWindow.draw(mStatisticText);

    mWindow.display();
}

void Application::ProcessInput()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        mStateStack.HandleInput(event);

        if (event.type == sf::Event::Closed)
            mWindow.close();
    }
}

void Application::RegisterStates()
{
    mStateStack.RegisterState<StateIntro>(States::StartScreen);
    mStateStack.RegisterState<StateLoading>(States::Loading);
    mStateStack.RegisterState<StateMainMenu>(States::MainMenu);
    mStateStack.RegisterState<StateGame>(States::GameState);
    //mStateStack.RegisterState<State>(States::PauseState);
}

void Application::UpdateStatistic(sf::Time dTime)
{
    mStatisticUpdateTime += dTime.asSeconds();
    mStatisticFPS += 1;

    if (mStatisticUpdateTime > 1.f)
    {
        mStatisticText.setString("FPS = " + std::to_string(mStatisticFPS) + '\n');
        mStatisticUpdateTime -= 1.f;
        mStatisticFPS = 1;
    }
}

