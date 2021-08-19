#pragma once
#include <string>
#include <memory>
#include <SFML/Graphics.hpp>
#include <cassert>

namespace Textures
{
    enum ID
    {
        Spaceship_Eagle,
        Spaceship_Raptor,
        Desert,
        Title,
        Loading,
    };
}

enum Fonts
{
    Main,
};

template<typename Resource, typename Identifier>
class ResourceHolder
{
public:
    void Load(Identifier id, const std::string& filename);

    template<typename Parameter>
    void Load(Identifier id, const std::string& filename, const Parameter& parameter);

    Resource& Get(Identifier id);
    const Resource& Get(Identifier id) const;

public:
    std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

#include "ResourceHolder.inl"

typedef ResourceHolder<sf::Texture, Textures::ID> TexturesHolder;
typedef ResourceHolder<sf::Font, Fonts> FontsHolder;
