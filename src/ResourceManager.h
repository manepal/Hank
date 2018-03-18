#ifndef  RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H


#include <map>
#include <string>
#include <memory>

#include "Texture2D.h"

class ResourceManager
{
public:
	static const std::shared_ptr<Texture2D> getTexture(const std::string& texturePath);
private:
	static std::map<std::string, std::shared_ptr<Texture2D>> mTextureCache;
};


#endif // RESOURCE_MANAGER_H