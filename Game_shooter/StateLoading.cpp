#include "StateLoading.h"

StateLoading::StateLoading(StateStack& stack, Context context) 
    : State(stack, context)
{
    mBackgroundSprite.setTexture(context.mTextures->Get(Textures::Loading));

    sf::Vector2f viewSize = context.mWindow->getView().getSize();
    sf::Vector2f viewPos = context.mWindow->getView().getCenter() - viewSize / 2.f;

    mBackgroundShape.setFillColor(sf::Color(255, 255, 255, 200));
    mBackgroundShape.setSize(sf::Vector2f(viewSize.x / 2.f, 20.f));

    mLoadingShape.setFillColor(sf::Color(255, 0, 0, 255));
    mLoadingShape.setSize(sf::Vector2f(0, 20.f));
    
    float x = viewPos.x + 0.25f * viewSize.x;
    float y = viewPos.y + 0.90f * viewSize.y;
    mBackgroundShape.setPosition(x, y);
    mLoadingShape.setPosition(x, y);

    mParallelTask.Execute();
}

void StateLoading::Draw()
{
    sf::RenderWindow& render = *GetContext()->mWindow;
    render.draw(mBackgroundSprite);
    render.draw(mBackgroundShape);
    render.draw(mLoadingShape);
}

bool StateLoading::Update(sf::Time dTime)
{
    if (mParallelTask.IsFinished())
    {
        requestPopState();
        requestPushState(States::MainMenu);
    }
    else
    {
        float x = mBackgroundShape.getSize().x * mParallelTask.GetCompletion();
        float y = mBackgroundShape.getSize().y;
        mLoadingShape.setSize(sf::Vector2f(x, y));
    }
    return true;
}

bool StateLoading::HandleInput(const sf::Event& event)
{
    return true;
}
