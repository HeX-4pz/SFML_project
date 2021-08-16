#pragma once
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>


class SceneNode: public sf::Transformable, public sf::Drawable, public sf::NonCopyable
{
public:
    typedef std::unique_ptr<SceneNode> uPtr;

public:
    void AttachChild(uPtr child);
    uPtr DetachChild(const SceneNode& node);
    
    void Update(sf::Time dTime);

    sf::Transform GetWorldTransform() const;
    sf::Vector2f GetWorldPosition() const;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    virtual void DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    void DrawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

    virtual void UpdateCurent(sf::Time dTime);
    void UpdateChildren(sf::Time dTime);


private:
    std::vector<uPtr> mChildren;
    SceneNode* mParent = nullptr;

};

