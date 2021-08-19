#include "StateIntro.h"
#include <iostream>

StateIntro::StateIntro(StateStack& stack, Context context) : State(stack, context)
{
    mShadowTime = sf::seconds(3.f);
    mAlphaTime = sf::seconds(1.f);
    mElapsedTime = mAlphaTime;

    mText.setFont(context.mFonts->Get(Fonts::Main));
    mText.setCharacterSize(50);
    mText.setString("Press any key");
    mText.setFillColor(sf::Color(255, 0, 0, 255));

    sf::FloatRect bounds = mText.getLocalBounds();
    mText.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    mText.setPosition(context.mWindow->getView().getSize() / 2.f);

    mBackgroundSprite.setTexture(context.mTextures->Get(Textures::Title));

    mBackgroundShape.setFillColor(sf::Color(0, 0, 0, 255));
    mBackgroundShape.setSize(context.mWindow->getView().getSize());
}

void StateIntro::Draw()
{
    sf::RenderWindow& render = *GetContext()->mWindow;
    render.draw(mBackgroundSprite);
    render.draw(mBackgroundShape);
    render.draw(mText);
}

bool StateIntro::Update(sf::Time dTime)
{

    int alphaText; 
    int alphaShape;
    mShadowTime -= dTime;

    if (mShadowTime.asSeconds() > 0.f)
    {
        alphaShape = static_cast<int> (255.f / 3.f * mShadowTime.asSeconds());
        alphaText = 0;
    }
    else
    {
        mShadowTime = sf::Time::Zero;
        mElapsedTime -= dTime;
        mElapsedTime = mElapsedTime <= sf::seconds(0.f) ? mAlphaTime : mElapsedTime;

        alphaShape = 0;
        alphaText = static_cast<int> (255.f / 1.f * mElapsedTime.asSeconds());
    }
    
    mText.setFillColor(sf::Color(255, 0, 0, alphaText));
    mBackgroundShape.setFillColor(sf::Color(0, 0, 0, alphaShape));

    return true;
}

bool StateIntro::HandleInput(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        requestPopState();
        requestPushState(States::Loading);
    }
    return true;
}
