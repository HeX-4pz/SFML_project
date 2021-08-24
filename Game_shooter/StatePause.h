#pragma once
#include "State.h"
#include "Container.h"

class StatePause :
    public State
{
public:
    StatePause(StateStack& stack, Context context);

    void Draw() override;
    bool Update(sf::Time dTime) override;
    bool HandleInput(const sf::Event& event) override;

private:
    sf::RectangleShape mShape;
    sf::Sprite mBackground;
    GUI::Container mGUIContainer;

};

