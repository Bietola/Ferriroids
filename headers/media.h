#ifndef MEDIA_H_INCLUDED
#define MEDIA_H_INCLUDED

#include <boost/filesystem.hpp>

#include <SFML/Graphics.hpp>

#include "MediaProvider.h"

namespace fs = boost::filesystem;

///global objects and variables
extern MediaProvider<sf::Texture> gTextureProvider;
extern MediaProvider<sf::Font> gFontProvider;

///global functions
//load all media, return false on failure
extern bool load_media();

#endif // MEDIA_H_INCLUDED
