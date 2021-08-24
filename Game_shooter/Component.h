#pragma once

#include <SFML/Graphics.hpp>

namespace GUI
{
    class Component : public sf::Drawable
        , public sf::Transformable
        , public sf::NonCopyable
    {
    public:
        typedef std::shared_ptr<Component> Ptr;

    public:
        Component();
        virtual         ~Component();
        virtual bool    IsSelectable() const = 0;
        virtual bool    IsActive() const;
        bool            IsSelected() const;

        virtual void    Select();
        virtual void    Deselect();

        virtual void    Activate();
        virtual void    Deactivate();

        virtual void    HandleEvent(const sf::Event& event) = 0;

    private:
        bool    mIsSelected;
        bool    mIsActive;

    };
}


