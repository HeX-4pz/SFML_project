#include "World.h"
#include "SpriteNode.h"
#include "Spaceship.h"
#include "Command.h"

World::World(sf::RenderWindow& window)
    : mRender(window)
    , mView(window.getDefaultView())
    , mTextureHolder()
    , mSceneGraph()
    , mPlayerSpaceship(nullptr)
    , mScrolSpeed(-50.f)
    , mWorldBounds(0.f, 0.f, mView.getSize().x, 2000.f)
    , mSpawnPosition(mView.getSize().x / 2.f, mWorldBounds.height - mView.getSize().y / 2.f)
    , mCommandsQueue()
{
    LoadResources();
    Initiate();
    mView.setCenter(mSpawnPosition);
}

void World::Update(sf::Time dTime)
{
    mView.move(0.f, mScrolSpeed * dTime.asSeconds());
    mPlayerSpaceship->SetVelocity(0.f, 0.f);

    while (!mCommandsQueue.empty())
    {
        mSceneGraph.OnCommand(mCommandsQueue.pop(), dTime);
    }

    AdaptPlayerVelocity();
    mSceneGraph.Update(dTime);
    
    AdaptPlayerPosition();
}

void World::Draw()
{
    mRender.setView(mView);
    mRender.draw(mSceneGraph);
}

sf::FloatRect World::GetCurrentBouds()
{
    return sf::FloatRect(
        mView.getCenter().x - mView.getSize().x / 2.f,
        mView.getCenter().y - mView.getSize().y / 2.f,
        mView.getSize().x,
        mView.getSize().y);
}

float World::GetScrollSpeed()
{
    return mScrolSpeed;
}

QueueInputCommands& World::GetCommandQueue()
{
    return mCommandsQueue;
}

void World::LoadResources()
{
    mTextureHolder.Load(Textures::Spaceship_Eagle, "resources/tex/Spaceship.png");
    mTextureHolder.Load(Textures::Spaceship_Raptor, "resources/tex/Raptor.png");
    mTextureHolder.Load(Textures::Desert, "resources/tex/Desert.png");
}

void World::Initiate()
{
    for (std::size_t i = 0; i < LayerCount; ++i)
    {
        SceneNode::uPtr layer(new SceneNode());
        mSceneLayers[i] = layer.get();

        mSceneGraph.AttachChild(std::move(layer));
    }

    sf::Texture& texture = mTextureHolder.Get(Textures::Desert);
    sf::IntRect rect(mWorldBounds);
    texture.setRepeated(true);

    std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, rect));
    backgroundSprite->setPosition(mWorldBounds.left, mWorldBounds.top);
    mSceneLayers[Background]->AttachChild(std::move(backgroundSprite));

    std::unique_ptr<Spaceship> player(new Spaceship(Spaceship::Eagle, *this, mTextureHolder));
    mPlayerSpaceship = player.get();
    mPlayerSpaceship->setPosition(mSpawnPosition);
    mPlayerSpaceship->SetVelocity(0, mScrolSpeed);
    mSceneLayers[Front]->AttachChild(std::move(player));
}

void World::AdaptPlayerPosition()
{
    sf::FloatRect viewBouds(mView.getCenter() - mView.getSize() / 2.f, mView.getSize());
    float borderDistance = 32;

    sf::Vector2f position = mPlayerSpaceship->getPosition();

    position.x = std::max(position.x, viewBouds.left + borderDistance);
    position.x = std::min(position.x, viewBouds.left + viewBouds.width - borderDistance);
    position.y = std::max(position.y, viewBouds.top + borderDistance);
    position.y = std::min(position.y, viewBouds.top + viewBouds.height - borderDistance);

    mPlayerSpaceship->setPosition(position);
}

void World::AdaptPlayerVelocity()
{
    sf::Vector2f velocity = mPlayerSpaceship->GetVelocity();

    if (velocity.x != 0.f && velocity.y != 0.f)
        mPlayerSpaceship->SetVelocity(velocity / std::sqrt(2.f));

    mPlayerSpaceship->Accelerate(0.f, mScrolSpeed);
}
