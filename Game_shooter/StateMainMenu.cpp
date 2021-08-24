#include "StateMainMenu.h"
#include <cassert>
#include <iostream>
#include "Button.h"

StateMainMenu::StateMainMenu(StateStack& stack, Context context) 
    : State(stack, context)
    , mGUIContainer()
{
    mBackground.setTexture(context.mTextures->Get(Textures::Loading));

    sf::Vector2f viewSize = context.mWindow->getView().getSize();
    sf::Vector2f viewPos = context.mWindow->getView().getCenter() - viewSize / 2.f;
    
    float x = viewPos.x + viewSize.x * 2.f / 3.f;
    float y = viewPos.y + viewSize.y * 0.7f / 4.f;

    
    GUI::Button::Ptr startButton = std::make_shared<GUI::Button>(*context.mFonts, *context.mTextures);
    GUI::Button::Ptr settingsButton = std::make_shared<GUI::Button>(*context.mFonts, *context.mTextures);
    GUI::Button::Ptr exitButton = std::make_shared<GUI::Button>(*context.mFonts, *context.mTextures);

    startButton->setPosition(x, y);
    settingsButton->setPosition(x, y + 60);
    exitButton->setPosition(x, y + 120);

    startButton->setScale(0.8f, 0.7f);
    settingsButton->setScale(0.8f, 0.7f);
    exitButton->setScale(0.8f, 0.7f);

    startButton->SetText("Start game");
    settingsButton->SetText("Settings");
    exitButton->SetText("Exit");

    startButton->SetCallback([this]() {
        requestPopState();
        requestPushState(States::GameState);
    });

    exitButton->SetCallback([this]() {
        requestPopState();
    });

    mGUIContainer.Pack(startButton);
    mGUIContainer.Pack(settingsButton);
    mGUIContainer.Pack(exitButton);

    
}

void StateMainMenu::Draw()
{
    sf::RenderWindow* render = GetContext()->mWindow;
    render->setView(render->getDefaultView());

    render->draw(mBackground);
    render->draw(mGUIContainer);
}

bool StateMainMenu::Update(sf::Time dTime)
{
    return true;
}

bool StateMainMenu::HandleInput(const sf::Event& event)
{
    mGUIContainer.HandleEvent(event);
    return false;
}

