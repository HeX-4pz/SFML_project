#pragma once
#include <SFML/Graphics.hpp>

class TexturesHolder;
class FontsHolder;
class StateStack;

struct Context
{
    Context(sf::RenderWindow& window, TexturesHolder& textureHolder, FontsHolder& fontsHolder)
        : mWindow(&window)
        , mTextures(&textureHolder)
        , mFonts(&fontsHolder) {}

    sf::RenderWindow* mWindow;
    TexturesHolder* mTextures;
    FontsHolder* mFonts;
};


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

class State
{

public:
    typedef std::unique_ptr<State> uPtr;

    State(StateStack& stack, Context context);

    virtual void Draw() = 0;
    virtual bool Update(sf::Time dTime) = 0;
    virtual bool HandleInput(const sf::Event& event) = 0;

private:
    void requestPushState(States::ID id);
    void requestPopState();
    void requestClearStates();


private:
    StateStack* mStack;
    Context mContext;

};

