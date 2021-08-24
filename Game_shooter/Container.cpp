#include "Container.h"

GUI::Container::Container()
    : mChildren()
    , mSelectedChild(-1)
{

}

void GUI::Container::Pack(Component::Ptr component)
{
    mChildren.push_back(component);

    if (!HasSelection())
    {
        Select(mChildren.size() - 1);
    }
}

bool GUI::Container::IsSelectable() const
{
    return false;
}

void GUI::Container::HandleEvent(const sf::Event& event)
{
    if (HasSelection() && mChildren[mSelectedChild]->IsActive())
    {
        mChildren[mSelectedChild]->HandleEvent(event);
    }
    else if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
            SelectPrev();
        else if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
            SelectNext();
        else if (event.key.code == sf::Keyboard::Return && HasSelection())
            mChildren[mSelectedChild]->Activate();
    }
}

void GUI::Container::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    for (auto& child : mChildren)
        target.draw(*child, states);
}

bool GUI::Container::HasSelection() const
{
    return mSelectedChild >= 0;
}

void GUI::Container::Select(std::size_t index)
{
    if (mChildren[index]->IsSelectable())
    {
        if (HasSelection())
            mChildren[mSelectedChild]->Deselect();

        mChildren[index]->Select();
        mSelectedChild = index;
    }
}

void GUI::Container::SelectNext()
{
    if (!HasSelection())
        return;

    int next = mSelectedChild;

    do 
    {
        next = (next + 1) % mChildren.size();
    } while (!mChildren[next]->IsSelectable());

    Select(next);
}

void GUI::Container::SelectPrev()
{
    if (!HasSelection())
        return;

    int prev = mSelectedChild;

    do
    {
        prev = (prev + mChildren.size() - 1) % mChildren.size();
    } while (!mChildren[prev]->IsSelectable());

    Select(prev);
}
