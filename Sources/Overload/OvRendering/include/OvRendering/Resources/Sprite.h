/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include <vector>
#include <unordered_map>
#include <string>

#include "OvRendering/Resources/Texture.h"
#include "OvRendering/Resources/Mesh.h"

namespace OvRendering::Resources
{

	namespace Loaders { class SpriteLoader; }

	/**
	* A sprite is a combinaison of meshes
	*/
	class Sprite
	{
		friend class Loaders::SpriteLoader;

	public:
		/**
		* Set the texture
		*/
		void SetTexture(OvRendering::Resources::Texture* p_Texture);

		/**
		* Get the texture
		*/
		OvRendering::Resources::Texture* GetTexture() const;

		/**
		* Set the meshes
		*/
		void SetMeshes(const std::vector<Mesh*>& p_Mesh);

		/**
		* Get the meshes
		*/
		const std::vector<Mesh*>& GetMeshes() const;

		/**
		* Get the material names
		*/
		const std::vector<std::string>& GetMaterialNames() const;

		/**
		* Get the bounding sphere of the sprite
		*/
		const OvRendering::Geometry::BoundingSphere& GetBoundingSphere() const;

		void ProcessMesh();

	private:
		Sprite(const std::string& p_path);
		~Sprite();

		void ComputeBoundingSphere();

	public:
		const std::string path;

	private:
		std::vector<Mesh*> m_meshes;
		OvRendering::Resources::Texture* m_texture;
		std::vector<std::string> m_materialNames;

		Geometry::BoundingSphere m_boundingSphere;
	};
}