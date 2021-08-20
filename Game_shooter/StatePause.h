#pragma once
#include "State.h"

class StatePause :
    public State
{

private:
    enum Options
    {
        Resume,
        Menu,
        Size,
    };

    friend const char * toString(StatePause::Options);

public:
    StatePause(StateStack& stack, Context context);

    void Draw() override;
    bool Update(sf::Time dTime) override;
    bool HandleInput(const sf::Event& event) override;

private:
    sf::RectangleShape mShape;
    sf::Sprite mBackground;
    std::vector<sf::Text> mPauseTexts;

    int mPointer;

};

