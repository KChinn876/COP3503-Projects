#include "TextureManager.h"
// redeclare variable, so this file knows it exists and can use
unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(std::string fileName) {
    string path = "images/";
    path += fileName + ".png";

    textures[fileName].loadFromFile(path);
}

sf::Texture& TextureManager::GetTexture(string textureName) {
    // if the texture doesn't exist... load it first then return it
    if(textures.find(textureName) == textures.end()) {
        LoadTexture(textureName);
    }
    return textures[textureName];
}

void TextureManager::Clear() {
    textures.clear(); // get rid of all stored objects
}