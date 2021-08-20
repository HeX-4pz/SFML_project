#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceHolder.hpp"

class StateStack;
class PlayerController;

namespace States
{
    enum ID 
    {
        None,
        StartScreen,
        Loading,
        MainMenu,
        GameState,
        PauseState,
    };
}

struct Context
{
    Context(sf::RenderWindow& window, TexturesHolder& textureHolder, FontsHolder& fontsHolder, PlayerController& controller)
        : mWindow(&window)
        , mTextures(&textureHolder)
        , mFonts(&fontsHolder)
        , mPlayerController(&controller) {}

    sf::RenderWindow* mWindow;
    TexturesHolder* mTextures;
    FontsHolder* mFonts;
    PlayerController* mPlayerController;
};


class State
{

public:
    typedef std::unique_ptr<State> uPtr;

    State(StateStack& stack, Context context);

    virtual void Draw() = 0;
    virtual bool Update(sf::Time dTime) = 0;
    virtual bool HandleInput(const sf::Event& event) = 0;

    Context* GetContext();

protected:
    void requestPushState(States::ID id);
    void requestPopState();
    void requestClearStates();

private:
    StateStack* mStack;
    Context mContext;

};

