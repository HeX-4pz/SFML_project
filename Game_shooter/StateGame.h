#pragma once
#include "State.h"
#include "World.h"

class StateGame :
    public State
{
public:
    StateGame(StateStack& stack, Context context);

    void Draw() override;
    bool Update(sf::Time dTime) override;
    bool HandleInput(const sf::Event& event) override;

private:
    World mWorld;
    PlayerController& mPlayer;
};

