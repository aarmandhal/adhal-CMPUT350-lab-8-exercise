#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include <deque>
#include <string>
#include <unordered_map>
#include <utility>

#include "sprite.h"
#include <SFML/Graphics.hpp>

using SpriteID = size_t;

class SpriteManager {
public:
    // Get or load a texture from the given path.
    sf::Texture& registerTexture(const std::string& path) {
        // Try to find the texture in the map
        auto existing = mTexturePathIndex.find(path);
        // If found, return the texture
        if (existing != mTexturePathIndex.end()) {
            // This uses the index from the map to get the texture from the deque
            return mTextures[existing->second];
        }
        // If not found, load the texture
        mTextures.emplace_back(path);
        // Get the new index
        size_t newIndex = mTextures.size() - 1;
        // Store the index in the map
        mTexturePathIndex[path] = newIndex;
        // Return the texture
        return mTextures[newIndex];
    }

    // Create a sprite with the given arguments.
    template <typename... Args>
    SpriteID createSprite(Args&&... args) {
        // Add the sprite to the deque
        mSprites.emplace_back(std::forward<Args>(args)...);
        // Return the index of the sprite
        return mSprites.size() - 1;
    }

    // Get a reference to the sprite with the given ID.
    Sprite& getSprite(SpriteID id) { return mSprites[id]; }

private:
    // Store textures in a deque
    std::deque<sf::Texture> mTextures;
    // Map file paths to texture indices
    std::unordered_map<std::string, size_t> mTexturePathIndex;
    // Store sprites in a deque
    std::deque<Sprite> mSprites;
};

#endif  // SPRITE_MANAGER_H
