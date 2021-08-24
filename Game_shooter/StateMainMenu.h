#pragma once
#include "State.h"
#include "Container.h"
#include <vector>

class StateMainMenu
    : public State
{

public:
    StateMainMenu(StateStack& stack, Context context);

    void Draw() override;
    bool Update(sf::Time dTime) override;
    bool HandleInput(const sf::Event& event) override;

private:
    sf::Sprite mBackground;
    GUI::Container mGUIContainer;

};

