#include "media.h"

///global objects and variables
//media providers
MediaProvider<sf::Texture> gTextureProvider;
MediaProvider<sf::Font> gFontProvider;

///global functions
//load all media, return false on failure
bool load_media()
{
    bool success = true;
    //load textures
    success &= gTextureProvider.loadMediaFromDirectory(fs::path("./assets/art/"));
    //load fonts
    success &= gFontProvider.loadMediaFromDirectory(fs::path("./assets/fonts/"));
    //
    return success;
}
