#include "Button.h"

GUI::Button::Button(const FontsHolder& fonts, const TexturesHolder& textures)
    : mText("", fonts.Get(Fonts::Main))
    , mBG_Normal(textures.Get(Textures::ID::Button_Normal))
    , mBG_Pressed(textures.Get(Textures::ID::Button_Pressed))
    , mBG_Selected(textures.Get(Textures::ID::Button_Selected))
    , mSprite()
    , mCallback()
{
    mSprite.setTexture(mBG_Normal);
    sf::FloatRect bounds = mSprite.getLocalBounds();

    mText.setPosition(bounds.width / 2.f, bounds.height / 2.f);
}

void GUI::Button::SetCallback(Callback callback)
{
    mCallback = std::move(callback);
}

void GUI::Button::SetText(const std::string & text)
{
    mText.setString(text);
    sf::FloatRect bounds = mText.getLocalBounds();

    float x = bounds.left + bounds.width / 2.f;
    float y = bounds.top + bounds.height / 2.f;

    mText.setOrigin(x, y);
}

sf::FloatRect& GUI::Button::GetLocalBounds() const
{
    sf::FloatRect localBounds = mSprite.getLocalBounds();
    sf::Vector2f size = sf::Vector2f(localBounds.width * getScale().x, localBounds.height * getScale().y);
    sf::FloatRect bounds(getPosition(), size);
    return bounds;
}

bool GUI::Button::IsSelectable() const
{
    return true;
}

void GUI::Button::Select()
{
    Component::Select();
    mSprite.setTexture(mBG_Selected);
}

void GUI::Button::Deselect()
{
    Component::Deselect();
    mSprite.setTexture(mBG_Normal);
}

void GUI::Button::Activate()
{
    Component::Activate();

    if (mCallback)
        mCallback();

    Deactivate();
}

void GUI::Button::Deactivate()
{
    Component::Deactivate();
}

void GUI::Button::HandleEvent(const sf::Event& event)
{

}

void GUI::Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mSprite, states);
    target.draw(mText, states);
}

