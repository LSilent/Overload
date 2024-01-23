/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include "OvRendering/Resources/Loaders/SpriteLoader.h"

OvRendering::Resources::Sprite* OvRendering::Resources::Loaders::SpriteLoader::Create(const std::string& p_filepath, Parsers::ESpriteParserFlags p_parserFlags)
{
	Sprite* result = new Sprite(p_filepath);

	if (result)
	{
		return result;
	}

	delete result;

	return nullptr;
}

void OvRendering::Resources::Loaders::SpriteLoader::Reload(Sprite& p_sprite, const std::string& p_filePath, Parsers::ESpriteParserFlags p_parserFlags)
{
	Sprite* newSprite = Create(p_filePath, p_parserFlags);

	if (newSprite)
	{
		p_sprite.m_meshes = newSprite->m_meshes;
		p_sprite.m_materialNames = newSprite->m_materialNames;
		p_sprite.m_texture = newSprite->m_texture;
		p_sprite.m_boundingSphere = newSprite->m_boundingSphere;
		newSprite->m_meshes.clear();
		delete newSprite;
	}
}

bool OvRendering::Resources::Loaders::SpriteLoader::Destroy(Sprite*& p_spriteInstance)
{
	if (p_spriteInstance)
	{
		delete p_spriteInstance;
		p_spriteInstance = nullptr;

		return true;
	}

	return false;
}
