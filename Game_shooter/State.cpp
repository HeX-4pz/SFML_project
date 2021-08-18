#include "State.h"
#include "StateStack.h"

State::State(StateStack & stack, Context context)
    : mStack(&stack)
    , mContext(context)
{
}

void State::requestPushState(States::ID id)
{
    mStack->PushState(id);
}

void State::requestPopState()
{
    mStack->PopState();
}

void State::requestClearStates()
{
    mStack->ClearStates();
}
