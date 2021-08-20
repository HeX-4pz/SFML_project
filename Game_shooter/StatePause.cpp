#include "StatePause.h"

const char * toString(StatePause::Options option)
{
    switch (option)
    {
    case StatePause::Resume:
        return "Resume";
    case StatePause::Menu:
        return "Menu";
    }
    assert(false);
    return "";
}

StatePause::StatePause(StateStack& stack, Context context) 
    : State(stack, context)
    , mPointer(0)
    , mShape()
{
    sf::Vector2f viewSize = context.mWindow->getView().getSize();
    sf::Vector2f viewPos = context.mWindow->getView().getCenter() - viewSize / 2.f;

    float y = viewPos.y + viewSize.y * 1.f / 3.f;

    sf::Vector2f startPoint = sf::Vector2f(context.mWindow->getView().getCenter().x, y);
    float interval_y = 50.f;

    for (int i = 0; i < Options::Size; ++i)
    {
        sf::Text text;
        text.setFont(context.mFonts->Get(Main));
        text.setString(toString(static_cast<Options>(i)));
        
        sf::Vector2f origin = text.getOrigin();
        origin.x += text.getLocalBounds().width / 2.f;
        text.setOrigin(origin);

        text.setFillColor(sf::Color::White);
        text.setPosition(startPoint.x, startPoint.y + interval_y * i);

        mPauseTexts.push_back(text);
    }

    mShape.setSize(viewSize);
    mShape.setFillColor(sf::Color(0, 0, 0, 150));
    mPauseTexts[mPointer].setFillColor(sf::Color::Red);
}

void StatePause::Draw()
{
    sf::RenderWindow* render = GetContext()->mWindow;
    render->setView(render->getDefaultView());
    
    render->draw(mShape);

    for (auto& text : mPauseTexts)
        render->draw(text);
}

bool StatePause::Update(sf::Time dTime)
{
    return false;
}

bool StatePause::HandleInput(const sf::Event& event)
{
    if (event.type != sf::Event::KeyPressed)
    {
        return false;
    }

    if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
    {
        mPauseTexts[mPointer].setFillColor(sf::Color::White);

        if (mPointer > 0)
            --mPointer;

        mPauseTexts[mPointer].setFillColor(sf::Color::Red);
    }
    else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
    {
        mPauseTexts[mPointer].setFillColor(sf::Color::White);

        if (mPointer < Options::Size - 1)
            ++mPointer;

        mPauseTexts[mPointer].setFillColor(sf::Color::Red);
    }
    else if (event.key.code == sf::Keyboard::Enter)
    {
        if (mPointer == Options::Resume)
        {
            requestPopState();
        }
        else if (mPointer == Options::Menu)
        {
            requestClearStates();
            requestPushState(States::MainMenu);
        }
        else
        {
            assert(false);
        }
    }

    return false;
}
