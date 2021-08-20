#include "StateGame.h"
#include "PlayerController.h"

StateGame::StateGame(StateStack& stack, Context context) 
    : State(stack, context)
    , mWorld(*context.mWindow)
    , mPlayer(*context.mPlayerController)
{

}

void StateGame::Draw()
{
    mWorld.Draw();
}

bool StateGame::Update(sf::Time dTime)
{
    mWorld.Update(dTime);
    mPlayer.HandleRealtimeInput(mWorld.GetCommandQueue());
    return true;
}

bool StateGame::HandleInput(const sf::Event& event)
{
    mPlayer.HandleInputEvent(event, mWorld.GetCommandQueue());

    if (event.type == sf::Event::KeyPressed, event.key.code == sf::Keyboard::Escape)
    {
        requestPopState();
    }

    return true;
}
