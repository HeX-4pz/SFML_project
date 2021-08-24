#pragma once
#include "Component.h"

namespace GUI
{
    class Container : public Component
    {
    public:
        typedef std::shared_ptr<Container> Ptr;

    public:
        Container();

        void Pack(Component::Ptr component);

        bool IsSelectable() const override;
        void HandleEvent(const sf::Event& event) override;

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        bool HasSelection() const;
        void Select(std::size_t index);
        void SelectNext();
        void SelectPrev();

    private:
        std::vector<Component::Ptr> mChildren;
        int mSelectedChild;

    };
}


