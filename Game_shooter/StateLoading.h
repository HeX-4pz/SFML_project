#pragma once
#include "State.h"
#include "ParallelTask.h"

class StateLoading :
    public State
{

public:
    StateLoading(StateStack& stack, Context context);

    void Draw() override;
    bool Update(sf::Time dTime) override;
    bool HandleInput(const sf::Event& event) override;

private:
    sf::Sprite mBackgroundSprite;
    
    sf::RectangleShape mBackgroundShape;
    sf::RectangleShape mLoadingShape;

    ParallelTask mParallelTask;

};

