#pragma once

#include <cassert>
#include <cmath>

#include <SFML/Graphics.hpp>

constexpr const double PI = std::atan(1.f) * 4.f;

//rand engine utils
inline int rrange(int min, int max) {
    assert(min <= max);
    return rand() % (max - min) + min;
}
inline int rrange(int max) {
    return rrange(0, max);
}
inline double rrangef(double min, double max) {
    assert(min <= max);
    return double(rand()) / double(RAND_MAX) * (max - min) + min;
}
inline double rrangef(double max) {
    return rrangef(0.f, max);
}

inline bool perc(double chance) {
    return rrangef(0, 100) < chance;
}

//comparison operators for vectors
template <typename T1, typename T2>
bool operator<(const sf::Vector2<T1>& lhs, const sf::Vector2<T2>& rhs) {
    return lhs.x < rhs.x && lhs.y < rhs.y;
}
template <typename T1, typename T2>
bool operator>(const sf::Vector2<T1>& lhs, const sf::Vector2<T2>& rhs) {
    return lhs.x > rhs.x && lhs.y > rhs.y;
}

///utils namespace
namespace utils {

//check if either of the keys mentioned is down
template <typename T>
bool areKeysPressed(T only) {
    return sf::Keyboard::isKeyPressed(only);
}
template <typename T, typename... Args>
bool areKeysPressed(T first, Args... args) {
    return areKeysPressed(first) || areKeysPressed(args...);
}

//normalize any vector
template <typename T>
sf::Vector2<T> normalize(const sf::Vector2<T>& vector, T normalIntensity = 1) {
    T intensity = std::sqrt(std::pow(vector.x, 2) + std::pow(vector.y, 2));
    return vector / intensity * normalIntensity;
}

//get intensity of any vector
template <typename T>
T intensity(const sf::Vector2<T>& vector) {
    return std::sqrt(std::pow(vector.x, 2) + std::pow(vector.y, 2));
}

//return random vector
template <typename T>
auto randVec2(const sf::Vector2<T>& min, const sf::Vector2<T>& max) {
    assert(min.x <= max.x && min.y <= max.y);
    return sf::Vector2<T>(rrangef(min.x, max.x), rrangef(min.y, max.y));
}
template <typename T>
auto randVec2(const sf::Vector2<T>& max) {
    return randVec2(sf::Vector2<T>(0, 0), max);
}

//returns random vector along borders given
template <typename T>
auto randBorderVec2(const sf::Vector2<T>& min, const sf::Vector2<T>& max) {
    assert(min.x <= max.x && min.y <= max.y);

    sf::Vector2<T> retVal;
    switch(rrange(4)) {
        case 0:
            return sf::Vector2<T>(rrangef(min.x, max.x), min.y);
        case 1:
            return sf::Vector2<T>(rrangef(min.x, max.x), max.y);
        case 2:
            return sf::Vector2<T>(min.x, rrangef(min.y, max.y));
        case 3:
            return sf::Vector2<T>(max.x, rrangef(min.y, max.y));
        default:
            assert(false);
    }
}
template <typename T>
auto randBorderVec2(const sf::Vector2<T>& max) {
    return randBorderVec2(sf::Vector2<T>(0, 0), max);
}

//take an integer and build a fixed digit string out of it (with 0s where there are usually no digits)
std::string intToFixedDigitsString(int num, int digits);

}
