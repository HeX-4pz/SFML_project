#pragma once
#include "State.h"

class StateIntro :
    public State
{
public:
    StateIntro(StateStack& stack, Context context);

    virtual void Draw();
    virtual bool Update(sf::Time dTime);
    virtual bool HandleInput(const sf::Event& event);

private:
    sf::Sprite mBackgroundSprite;
    sf::RectangleShape mBackgroundShape;

    sf::Text mText;
    sf::Time mElapsedTime;

    sf::Time mShadowTime; 
    sf::Time mAlphaTime;
};

