#include "Component.h"

GUI::Component::Component()
    : mIsActive(false)
    , mIsSelected(false)
{

}

GUI::Component::~Component()
{

}

bool GUI::Component::IsActive() const
{
    return mIsActive;
}

bool GUI::Component::IsSelected() const
{
    return mIsSelected;
}

void GUI::Component::Select()
{
    mIsSelected = true;
}

void GUI::Component::Deselect()
{
    mIsSelected = false;
}

void GUI::Component::Activate()
{
    mIsActive = true;
}

void GUI::Component::Deactivate()
{
    mIsActive = false;
}
