/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include <OvRendering/Resources/Loaders/SpriteLoader.h>

#include "OvCore/ResourceManagement/AResourceManager.h"

namespace OvCore::ResourceManagement
{
	/**
	* ResourceManager of sprites
	*/
	class SpriteManager : public AResourceManager<OvRendering::Resources::Sprite>
	{
	public:
		/**
		* Create the resource identified by the given path
		* @param p_path
		*/
		virtual OvRendering::Resources::Sprite* CreateResource(const std::string & p_path) override;

		/**
		* Destroy the given resource
		* @param p_resource
		*/
		virtual void DestroyResource(OvRendering::Resources::Sprite* p_resource) override;

		/**
		* Reload the given resource
		* @param p_resource
		* @param p_path
		*/
		virtual void ReloadResource(OvRendering::Resources::Sprite* p_resource, const std::string& p_path) override;
	};
}