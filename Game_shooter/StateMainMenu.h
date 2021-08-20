#pragma once
#include "State.h"
#include <vector>

class StateMainMenu
    : public State
{

private:
    enum MenuAction
    {
        NewGame,
        Settings,
        Exit,
        Size,
    };

    friend const char * toString(StateMainMenu::MenuAction);

public:
    StateMainMenu(StateStack& stack, Context context);

    void Draw() override;
    bool Update(sf::Time dTime) override;
    bool HandleInput(const sf::Event& event) override;

private:
    void SetPointerPosition(int position);

    void OnEnterPressed();
    void OnNewGameSelected();
    void OnSettingsSelected();
    void OnExitSelected();

private:
    sf::Sprite mBackground;
    std::vector<sf::Text> mMenuTexts;

    int mMenuPointer;

};

