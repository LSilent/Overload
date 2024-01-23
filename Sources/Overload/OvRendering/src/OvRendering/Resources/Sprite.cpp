/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include <algorithm>

#include "OvRendering/Resources/Sprite.h"

const OvRendering::Geometry::BoundingSphere& OvRendering::Resources::Sprite::GetBoundingSphere() const
{
	return m_boundingSphere;
}

OvRendering::Resources::Sprite::Sprite(const std::string& p_path) : path(p_path), m_texture(nullptr), m_materialNames(1, ":Materials\\Unlit.ovmat")
{
}

OvRendering::Resources::Sprite::~Sprite()
{
	for (auto mesh : m_meshes)
		delete mesh;
}

void OvRendering::Resources::Sprite::ComputeBoundingSphere()
{
	if (m_meshes.size() == 1)
	{
		m_boundingSphere = m_meshes[0]->GetBoundingSphere();
	}
	else
	{
		m_boundingSphere.position = OvMaths::FVector3::Zero;
		m_boundingSphere.radius = 0.0f;

		if (!m_meshes.empty())
		{
			float minX = std::numeric_limits<float>::max();
			float minY = std::numeric_limits<float>::max();
			float minZ = std::numeric_limits<float>::max();

			float maxX = std::numeric_limits<float>::min();
			float maxY = std::numeric_limits<float>::min();
			float maxZ = std::numeric_limits<float>::min();

			for (const auto& mesh : m_meshes)
			{
				const auto& boundingSphere = mesh->GetBoundingSphere();
				minX = std::min(minX, boundingSphere.position.x - boundingSphere.radius);
				minY = std::min(minY, boundingSphere.position.y - boundingSphere.radius);
				minZ = std::min(minZ, boundingSphere.position.z - boundingSphere.radius);

				maxX = std::max(maxX, boundingSphere.position.x + boundingSphere.radius);
				maxY = std::max(maxY, boundingSphere.position.y + boundingSphere.radius);
				maxZ = std::max(maxZ, boundingSphere.position.z + boundingSphere.radius);
			}

			m_boundingSphere.position = OvMaths::FVector3{ minX + maxX, minY + maxY, minZ + maxZ } / 2.0f;
			m_boundingSphere.radius = OvMaths::FVector3::Distance(m_boundingSphere.position, { minX, minY, minZ });
		}
	}
}

void OvRendering::Resources::Sprite::SetTexture(OvRendering::Resources::Texture* p_Texture)
{
	m_texture = p_Texture;
	ProcessMesh();
}

OvRendering::Resources::Texture* OvRendering::Resources::Sprite::GetTexture() const
{
	return m_texture;
}

void OvRendering::Resources::Sprite::SetMeshes(const std::vector<Mesh*>& p_Mesh)
{
	for (auto mesh : m_meshes)
		delete mesh;

	m_meshes = p_Mesh;
}

const std::vector<OvRendering::Resources::Mesh*>& OvRendering::Resources::Sprite::GetMeshes() const
{
	return m_meshes;
}

const std::vector<std::string>& OvRendering::Resources::Sprite::GetMaterialNames() const
{
	return m_materialNames;
}

void OvRendering::Resources::Sprite::ProcessMesh()
{
	if (!m_texture)
	{
		return;
	}

	float halfWidth = m_texture->width / 2.0f;
	float halfHeight = m_texture->height / 2.0f;

	std::vector<Geometry::Vertex> vertices;
	Geometry::Vertex tl{ { -halfWidth, halfHeight, 0.0f }, { 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
	Geometry::Vertex bl{ { -halfWidth, -halfHeight, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
	Geometry::Vertex tr{ { halfWidth, halfHeight, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
	Geometry::Vertex br{ { halfWidth, -halfHeight, 0.0f }, { 1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
	vertices.push_back(tl);
	vertices.push_back(bl);
	vertices.push_back(tr);
	vertices.push_back(br);

	std::vector<uint32_t> indices;
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(3);
	indices.push_back(2);

	std::vector<Mesh*> meshes;

	meshes.push_back(new Mesh(vertices, indices, 0));

	SetMeshes(meshes);

	ComputeBoundingSphere();
}
