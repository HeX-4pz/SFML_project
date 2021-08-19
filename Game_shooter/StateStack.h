#pragma once
#include <functional>
#include <vector>
#include <map>
#include <SFML/Graphics.hpp>

#include "State.h"

class StateStack : private sf::NonCopyable
{
public:
    enum Action
    {
        Push,
        Pop,
        Clear,
    };

public:
    explicit StateStack(Context context);

    template<typename T>
    void RegisterState(States::ID stateID);

    void Draw();
    void Update(sf::Time dTime);
    void HandleInput(const sf::Event& event);

    void PushState(States::ID stateID);
    void PopState();
    void ClearStates();

    bool IsEmpty();

private:
    State::uPtr CreateState(States::ID stateID);
    void ApplayPendingChanges();

private:
    struct PendingChange
    {
        explicit PendingChange(Action action, States::ID stateID = States::None) 
            : mAction(action)
            , mStateID(stateID) {}
        
        Action mAction;
        States::ID mStateID;
    };


private:
    std::vector<State::uPtr> mStack;
    std::vector<PendingChange> mPendingChangesList;

    Context mContext;
    std::map<States::ID, std::function<State::uPtr()>> mFactories;
};



template<typename T>
void StateStack::RegisterState(States::ID stateID)
{
    mFactories[stateID] = [this] () 
    {
        return State::uPtr(new T(*this, mContext));
    };
}