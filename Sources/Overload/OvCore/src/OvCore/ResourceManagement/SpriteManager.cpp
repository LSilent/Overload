/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include "OvCore/ResourceManagement/SpriteManager.h"
#include "OvCore/ResourceManagement/TextureManager.h"
#include "OvCore/Global/ServiceLocator.h"

#include <OvTools/Filesystem/IniFile.h>

OvRendering::Resources::Parsers::ESpriteParserFlags GetAssetMetadata(const std::string& p_path)
{
	auto metaFile = OvTools::Filesystem::IniFile(p_path + ".meta");

	OvRendering::Resources::Parsers::ESpriteParserFlags flags = OvRendering::Resources::Parsers::ESpriteParserFlags::NONE;

	if (metaFile.GetOrDefault("CALC_TANGENT_SPACE",			true))	flags |= OvRendering::Resources::Parsers::ESpriteParserFlags::CALC_TANGENT_SPACE;
	if (metaFile.GetOrDefault("JOIN_IDENTICAL_VERTICES",	true))	flags |= OvRendering::Resources::Parsers::ESpriteParserFlags::JOIN_IDENTICAL_VERTICES;
	if (metaFile.GetOrDefault("MAKE_LEFT_HANDED",			false))	flags |= OvRendering::Resources::Parsers::ESpriteParserFlags::MAKE_LEFT_HANDED;
	if (metaFile.GetOrDefault("TRIANGULATE",				true))	flags |= OvRendering::Resources::Parsers::ESpriteParserFlags::TRIANGULATE;
	if (metaFile.GetOrDefault("REMOVE_COMPONENT",			false))	flags |= OvRendering::Resources::Parsers::ESpriteParserFlags::REMOVE_COMPONENT;
	if (metaFile.GetOrDefault("GEN_NORMALS",				false))	flags |= OvRendering::Resources::Parsers::ESpriteParserFlags::GEN_NORMALS;
	if (metaFile.GetOrDefault("GEN_SMOOTH_NORMALS",			true))	flags |= OvRendering::Resources::Parsers::ESpriteParserFlags::GEN_SMOOTH_NORMALS;
	if (metaFile.GetOrDefault("SPLIT_LARGE_MESHES",			false))	flags |= OvRendering::Resources::Parsers::ESpriteParserFlags::SPLIT_LARGE_MESHES;
	if (metaFile.GetOrDefault("PRE_TRANSFORM_VERTICES",		true))	flags |= OvRendering::Resources::Parsers::ESpriteParserFlags::PRE_TRANSFORM_VERTICES;
	if (metaFile.GetOrDefault("LIMIT_BONE_WEIGHTS",			false))	flags |= OvRendering::Resources::Parsers::ESpriteParserFlags::LIMIT_BONE_WEIGHTS;
	if (metaFile.GetOrDefault("VALIDATE_DATA_STRUCTURE",	false))	flags |= OvRendering::Resources::Parsers::ESpriteParserFlags::VALIDATE_DATA_STRUCTURE;
	if (metaFile.GetOrDefault("IMPROVE_CACHE_LOCALITY",		true))	flags |= OvRendering::Resources::Parsers::ESpriteParserFlags::IMPROVE_CACHE_LOCALITY;
	if (metaFile.GetOrDefault("REMOVE_REDUNDANT_MATERIALS", false))	flags |= OvRendering::Resources::Parsers::ESpriteParserFlags::REMOVE_REDUNDANT_MATERIALS;
	if (metaFile.GetOrDefault("FIX_INFACING_NORMALS",		false))	flags |= OvRendering::Resources::Parsers::ESpriteParserFlags::FIX_INFACING_NORMALS;
	if (metaFile.GetOrDefault("SORT_BY_PTYPE",				false))	flags |= OvRendering::Resources::Parsers::ESpriteParserFlags::SORT_BY_PTYPE;
	if (metaFile.GetOrDefault("FIND_DEGENERATES",			false))	flags |= OvRendering::Resources::Parsers::ESpriteParserFlags::FIND_DEGENERATES;
	if (metaFile.GetOrDefault("FIND_INVALID_DATA",			true))	flags |= OvRendering::Resources::Parsers::ESpriteParserFlags::FIND_INVALID_DATA;
	if (metaFile.GetOrDefault("GEN_UV_COORDS",				true))	flags |= OvRendering::Resources::Parsers::ESpriteParserFlags::GEN_UV_COORDS;
	if (metaFile.GetOrDefault("TRANSFORM_UV_COORDS",		false))	flags |= OvRendering::Resources::Parsers::ESpriteParserFlags::TRANSFORM_UV_COORDS;
	if (metaFile.GetOrDefault("FIND_INSTANCES",				true))	flags |= OvRendering::Resources::Parsers::ESpriteParserFlags::FIND_INSTANCES;
	if (metaFile.GetOrDefault("OPTIMIZE_MESHES",			true))	flags |= OvRendering::Resources::Parsers::ESpriteParserFlags::OPTIMIZE_MESHES;
	if (metaFile.GetOrDefault("OPTIMIZE_GRAPH",				true))	flags |= OvRendering::Resources::Parsers::ESpriteParserFlags::OPTIMIZE_GRAPH;
	if (metaFile.GetOrDefault("FLIP_UVS",					false))	flags |= OvRendering::Resources::Parsers::ESpriteParserFlags::FLIP_UVS;
	if (metaFile.GetOrDefault("FLIP_WINDING_ORDER",			false))	flags |= OvRendering::Resources::Parsers::ESpriteParserFlags::FLIP_WINDING_ORDER;
	if (metaFile.GetOrDefault("SPLIT_BY_BONE_COUNT",		false))	flags |= OvRendering::Resources::Parsers::ESpriteParserFlags::SPLIT_BY_BONE_COUNT;
	if (metaFile.GetOrDefault("DEBONE",						true))	flags |= OvRendering::Resources::Parsers::ESpriteParserFlags::DEBONE;
	if (metaFile.GetOrDefault("GLOBAL_SCALE",				true))	flags |= OvRendering::Resources::Parsers::ESpriteParserFlags::GLOBAL_SCALE;
	if (metaFile.GetOrDefault("EMBED_TEXTURES",				false))	flags |= OvRendering::Resources::Parsers::ESpriteParserFlags::EMBED_TEXTURES;
	if (metaFile.GetOrDefault("FORCE_GEN_NORMALS",			false))	flags |= OvRendering::Resources::Parsers::ESpriteParserFlags::FORCE_GEN_NORMALS;
	if (metaFile.GetOrDefault("DROP_NORMALS",				false))	flags |= OvRendering::Resources::Parsers::ESpriteParserFlags::DROP_NORMALS;
	if (metaFile.GetOrDefault("GEN_BOUNDING_BOXES",			false))	flags |= OvRendering::Resources::Parsers::ESpriteParserFlags::GEN_BOUNDING_BOXES;

	return { flags };
}

OvRendering::Resources::Sprite* OvCore::ResourceManagement::SpriteManager::CreateResource(const std::string& p_path)
{
	std::string realPath = GetRealPath(p_path);
	auto sprite = OvRendering::Resources::Loaders::SpriteLoader::Create(realPath, GetAssetMetadata(realPath));
	if (sprite)
	{
		*reinterpret_cast<std::string*>(reinterpret_cast<char*>(sprite) + offsetof(OvRendering::Resources::Sprite, path)) = p_path; // Force the resource path to fit the given path
		auto texture = OvCore::Global::ServiceLocator::Get<OvCore::ResourceManagement::TextureManager>().GetResource(p_path);
		if (texture)
			sprite->SetTexture(texture);
	}

	return sprite;
}

void OvCore::ResourceManagement::SpriteManager::DestroyResource(OvRendering::Resources::Sprite* p_resource)
{
	OvRendering::Resources::Loaders::SpriteLoader::Destroy(p_resource);
}

void OvCore::ResourceManagement::SpriteManager::ReloadResource(OvRendering::Resources::Sprite* p_resource, const std::string& p_path)
{
	std::string realPath = GetRealPath(p_path);
	OvRendering::Resources::Loaders::SpriteLoader::Reload(*p_resource, realPath, GetAssetMetadata(realPath));
}
