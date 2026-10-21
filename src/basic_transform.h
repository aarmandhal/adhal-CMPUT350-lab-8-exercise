#ifndef BASIC_TRANSFORM_H
#define BASIC_TRANSFORM_H

#include <cassert>

#include "vector_util.h"
#include <SFML/System/Vector2.hpp>

struct BasicTransform {
    // TODO: Determine if possible in general, else provide counterexample:
    // compose(f, g) is equivalent to first applying g, then applying f.
    static BasicTransform compose(const BasicTransform& f, const BasicTransform& g) {
        // Get new scale by multiplying the scales
        sf::Vector2f newScale = {f.scale.x * g.scale.x, f.scale.y * g.scale.y};
        // Get new translation by applying the second transform to the first transform's translation
        sf::Vector2f newTranslation = f.applyPoint(g.translation);
        // Return the new transform
        return BasicTransform(newScale, newTranslation);
    };

    // TODO: Determine if possible in general, else provide counterexample:
    static BasicTransform inverse(const BasicTransform& f) {
        // Get the inverse scale by taking the reciprocal of the scale
        sf::Vector2f ones = {1.f, 1.f};
        // Calculate the inverse scale
        sf::Vector2f invScale = {ones.x / f.scale.x, ones.y / f.scale.y};
        // Calculate the inverse translation
        sf::Vector2f invTranslation = {-f.translation.x / f.scale.x, -f.translation.y / f.scale.y};
        // Return the inverse transform
        return BasicTransform(invScale, invTranslation);
    };

    constexpr BasicTransform(const sf::Vector2f& scale = {1.f, 1.f},
                             const sf::Vector2f& translation = {0.f, 0.f})
        : scale{scale}, translation{translation} {}

    constexpr sf::Vector2f applyPoint(const sf::Vector2f& p) const {
        // first scale, then translate -- if you do the reverse, the translation gets messed up.
        return {p.x * scale.x + translation.x, p.y * scale.y + translation.y};
    }

    constexpr sf::Vector2f applyVector(const sf::Vector2f& p) const {
        // vectors are not translated by transformations
        return {p.x * scale.x, p.y * scale.y};
    }

    constexpr bool operator==(const BasicTransform& other) const {
        return scale == other.scale && translation == other.translation;
    }

    sf::Vector2f scale;
    sf::Vector2f translation;
};

#endif