/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include <string>

#include "OvRendering/Resources/Sprite.h"
#include "OvRendering/Resources/Parsers/ESpriteParserFlags.h"

namespace OvRendering::Resources::Loaders
{
	/**
	* Handle the Sprite creation and destruction
	*/
	class SpriteLoader
	{
	public:
		/**
		* Disabled constructor
		*/
		SpriteLoader() = delete;

		/**
		* Create a sprite
		* @param p_filepath
		* @param p_parserFlags
		*/
		static Sprite* Create(const std::string& p_filepath, Parsers::ESpriteParserFlags p_parserFlags = Parsers::ESpriteParserFlags::NONE);

		/**
		* Reload a sprite from file
		* @param p_sprite
		* @param p_filePath
		* @param p_parserFlags
		*/
		static void Reload(Sprite& p_sprite, const std::string& p_filePath, Parsers::ESpriteParserFlags p_parserFlags = Parsers::ESpriteParserFlags::NONE);

		/**
		* Disabled constructor
		* @param p_spriteInstance
		*/
		static bool Destroy(Sprite*& p_spriteInstance);
	};
}