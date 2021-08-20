#include "StateMainMenu.h"
#include <cassert>
#include <iostream>

const char * toString(StateMainMenu::MenuAction action)
{
    switch (action)
    {
    case StateMainMenu::NewGame:
        return "New game";
    case StateMainMenu::Settings:
        return "Settings";
    case StateMainMenu::Exit:
        return "Exit";
    }
    assert(false);
    return "";
}

StateMainMenu::StateMainMenu(StateStack& stack, Context context) 
    : State(stack, context)
{
    sf::Vector2f viewSize = context.mWindow->getView().getSize();
    sf::Vector2f viewPos = context.mWindow->getView().getCenter() - viewSize / 2.f;
    
    float x = viewPos.x + viewSize.x * 2.f / 3.f;
    float y = viewPos.y + viewSize.y * 1.f / 4.f;
    
    sf::Vector2f startPoint = sf::Vector2f(x, y);
    float interval_y = 50.f;

    for (int i = 0; i < MenuAction::Size; ++i)
    {
        sf::Text text;
        text.setString(toString(static_cast<MenuAction>(i)));
        text.setPosition(startPoint.x, startPoint.y + i * interval_y);
        text.setFont(context.mFonts->Get(Main));
        text.setFillColor(sf::Color::White);

        mMenuTexts.push_back(text);
    }

    mBackground.setTexture(context.mTextures->Get(Textures::Loading));
    SetPointerPosition(0);
}

void StateMainMenu::Draw()
{
    sf::RenderWindow* render = GetContext()->mWindow;
    render->draw(mBackground);

    for (auto& text : mMenuTexts)
        render->draw(text);
}

bool StateMainMenu::Update(sf::Time dTime)
{
    return true;
}

bool StateMainMenu::HandleInput(const sf::Event& event)
{
    if (event.type != sf::Event::KeyPressed)
    {
        return true;
    }

    if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
        SetPointerPosition(mMenuPointer - 1);
    else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
        SetPointerPosition(mMenuPointer + 1);
    else if (event.key.code == sf::Keyboard::Enter)
        OnEnterPressed();

    return true;
}

void StateMainMenu::SetPointerPosition(int position)
{
    int prevPosition = mMenuPointer;

    if (position < 0)
        position = MenuAction::Size - 1;
    else if (position >= MenuAction::Size)
        position = 0;

    mMenuPointer = position;

    mMenuTexts[prevPosition].setFillColor(sf::Color::White);
    mMenuTexts[mMenuPointer].setFillColor(sf::Color::Red);

}

void StateMainMenu::OnEnterPressed()
{
    switch (mMenuPointer)
    {
    case MenuAction::NewGame:
        OnNewGameSelected();
        break;
    case MenuAction::Settings:
        OnSettingsSelected();
        break;
    case MenuAction::Exit:
        OnExitSelected();
        break;
    default:
        assert(false);
        break;
    }
}

void StateMainMenu::OnNewGameSelected()
{
    std::cout << "New Game choice" << std::endl;
    requestPopState();
    requestPushState(States::GameState);
}

void StateMainMenu::OnSettingsSelected()
{
    std::cout << "Settings choice" << std::endl;
}

void StateMainMenu::OnExitSelected()
{
    std::cout << "Exit choice" << std::endl;
    requestPopState();
}
