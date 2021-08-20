#pragma once
#include "State.h"

class StateIntro :
    public State
{
public:
    StateIntro(StateStack& stack, Context context);

    void Draw() override;
    bool Update(sf::Time dTime) override;
    bool HandleInput(const sf::Event& event) override;

private:
    sf::Sprite mBackgroundSprite;
    sf::RectangleShape mBackgroundShape;

    sf::Text mText;
    sf::Time mElapsedTime;

    sf::Time mShadowTime; 
    sf::Time mAlphaTime;
};

