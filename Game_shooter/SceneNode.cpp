#include "SceneNode.h"
#include <algorithm>
#include <cassert>

void SceneNode::AttachChild(uPtr child)
{
    child->mParent = this;
    mChildren.push_back(std::move(child));
}

SceneNode::uPtr SceneNode::DetachChild(const SceneNode & node)
{
    std::vector<uPtr>::iterator found = std::find_if(mChildren.begin(), mChildren.end(),
        [&](uPtr& p) -> bool {return p.get() == &node; });

    assert(found != mChildren.end());

    uPtr result = std::move(*found);
    result->mParent = nullptr;
    
    if (mChildren.begin() != mChildren.end())
    {
        *found = std::move(*(mChildren.end() - 1));
        mChildren.pop_back();
    }

    return result;

}

void SceneNode::Update(sf::Time dTime)
{
    UpdateCurent(dTime);
    UpdateChildren(dTime);
}

void SceneNode::OnCommand(const Command & command, sf::Time dTime)
{
    if (GetCommandType() == command.mCommandType)
    {
        command.mAction(*this, dTime);
    }

    for (auto& child : mChildren)
    {
        child->OnCommand(command, dTime);
    }
}

sf::Transform SceneNode::GetWorldTransform() const
{
    sf::Transform transform = sf::Transform::Identity;
    for (const SceneNode* node = this; node; node = node->mParent)
    {
        transform = node->getTransform() * transform;
    }
    return transform;
}

sf::Vector2f SceneNode::GetWorldPosition() const
{
    return GetWorldTransform() * sf::Vector2f();
}

void SceneNode::DrawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto& child : mChildren)
    {
        child->draw(target, states);
    }
}

void SceneNode::UpdateCurent(sf::Time dTime)
{

}

void SceneNode::UpdateChildren(sf::Time dTime)
{
    for (auto& child : mChildren)
    {
        child->Update(dTime);
    }
}

CommandType SceneNode::GetCommandType()
{
    return CommandType_Scene;
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    DrawCurrent(target, states);
    DrawChildren(target, states);

}

void SceneNode::DrawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{

}
