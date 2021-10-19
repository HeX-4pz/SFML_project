#pragma once
#include <functional>

#include "Component.h"
#include "ResourceHolder.hpp"

namespace GUI
{
    class Button :
        public Component
    {
    public:
        typedef std::shared_ptr<Button> Ptr;
        typedef std::function<void()> Callback;

    public:
        Button(const FontsHolder& fonts, const TexturesHolder& textures);

        void SetCallback(Callback callback);
        void SetText(const std::string& text);

        sf::FloatRect GetLocalBounds();

        bool    IsSelectable() const override;
        void    Select() override;
        void    Deselect() override;

        void    Activate() override;
        void    Deactivate() override;

        void    HandleEvent(const sf::Event& event) override;

    private:
        virtual void    draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        sf::Text mText;
        const sf::Texture& mBG_Normal;
        const sf::Texture& mBG_Selected;
        const sf::Texture& mBG_Pressed;
        sf::Sprite mSprite;
        Callback mCallback;
    };

}

