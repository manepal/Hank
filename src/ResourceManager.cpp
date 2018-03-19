#include "ResourceManager.h"

#include <iostream>

std::map<std::string, std::shared_ptr<Texture2D>> ResourceManager::mTextureCache;

const std::shared_ptr<Texture2D> ResourceManager::getTexture(const std::string & texturePath)
{
	// look for texture in the map
	auto iterator = mTextureCache.find(texturePath);

	if (iterator != mTextureCache.end()) // found
	{
		std::cout << "'" << texturePath  << "' loaded from texture cache." <<  std::endl;
		return iterator->second;
	}

	std::cout << "'" << texturePath << "' loaded from disk." << std::endl;
	
	std::shared_ptr<Texture2D> newTexture(new Texture2D);
	if (newTexture->loadTexture(texturePath) == false)
	{
		return nullptr;
	}

	mTextureCache.insert(std::pair<std::string, std::shared_ptr<Texture2D>>(texturePath, newTexture));

	return newTexture;
}
