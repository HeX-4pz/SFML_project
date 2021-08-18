#include <cassert>
#include "StateStack.h"

StateStack::StateStack(Context context)
    :mContext(context)
{
}

void StateStack::Draw()
{
    for (auto& state : mStack)
    {
        state->Draw();
    }
}

void StateStack::Update(sf::Time dTime)
{
    for (auto it = mStack.rbegin(); it != mStack.rend(); ++it)
    {
        if (!(*it)->Update(dTime))
            break;
    }

    ApplayPendingChanges();
}

void StateStack::HandleInput(const sf::Event & event)
{
    for (auto it = mStack.rbegin(); it != mStack.rend(); ++it)
    {
        if (!(*it)->HandleInput(event))
            break;
    }

    ApplayPendingChanges();
}

void StateStack::PushState(States::ID stateID)
{
    mPendingChangesList.push_back(PendingChange(Action::Push, stateID));
}

void StateStack::PopState()
{
    mPendingChangesList.push_back(PendingChange(Action::Pop));
}

void StateStack::ClearStates()
{
    mPendingChangesList.push_back(PendingChange(Action::Clear));
}

bool StateStack::IsEmpty()
{
    return mStack.empty();
}

State::uPtr StateStack::CreateState(States::ID stateID)
{
    auto found = mFactories.find(stateID);
    assert(found != mFactories.end());

    return found->second();
}

void StateStack::ApplayPendingChanges()
{
    for (auto change : mPendingChangesList)
    {
        switch (change.mAction)
        {
        case Action::Push:
            mStack.push_back(CreateState(change.mStateID));
            break;
        case Action::Pop:
            mStack.pop_back();
            break;
        case Action::Clear:
            mStack.clear();
            break;
        default:
            assert(false);
        }
    }
    mPendingChangesList.clear();
}
