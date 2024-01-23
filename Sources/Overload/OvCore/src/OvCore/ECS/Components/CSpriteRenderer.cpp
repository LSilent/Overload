/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#include <OvUI/Widgets/Texts/Text.h>
#include <OvUI/Widgets/Texts/TextColored.h>
#include <OvUI/Plugins/DDTarget.h>
#include <OvUI/Widgets/Visual/Image.h>
#include <OvUI/Widgets/Selection/ComboBox.h>
#include <OvUI/Widgets/Selection/CheckBox.h>
#include <OvUI/Widgets/Drags/DragFloat.h>

#include "OvCore/Global/ServiceLocator.h"
#include "OvCore/ResourceManagement/TextureManager.h"
#include "OvCore/ResourceManagement/ModelManager.h"
#include "OvCore/ResourceManagement/ShaderManager.h"
#include "OvCore/ECS/Components/CSpriteRenderer.h"
#include "OvCore/ECS/Components/CMaterialRenderer.h"
#include "OvCore/ECS/Actor.h"

OvCore::ECS::Components::CSpriteRenderer::CSpriteRenderer(ECS::Actor& p_owner) : AComponent(p_owner)
{
	m_spriteChangedEvent += [this]
		{
			if (auto materialRenderer = owner.GetComponent<CMaterialRenderer>())
				materialRenderer->UpdateMaterialList();
		};
}

std::string OvCore::ECS::Components::CSpriteRenderer::GetName()
{
	return "Sprite Renderer";
}

void OvCore::ECS::Components::CSpriteRenderer::SetSprite(OvRendering::Resources::Sprite* p_sprite)
{
	m_sprite = p_sprite;
	m_spriteChangedEvent.Invoke();
}

OvRendering::Resources::Sprite* OvCore::ECS::Components::CSpriteRenderer::GetSprite() const
{
	return m_sprite;
}

void OvCore::ECS::Components::CSpriteRenderer::SetFrustumBehaviour(EFrustumBehaviour p_boundingMode)
{
	m_frustumBehaviour = p_boundingMode;
}

OvCore::ECS::Components::CSpriteRenderer::EFrustumBehaviour OvCore::ECS::Components::CSpriteRenderer::GetFrustumBehaviour() const
{
	return m_frustumBehaviour;
}

const OvRendering::Geometry::BoundingSphere& OvCore::ECS::Components::CSpriteRenderer::GetCustomBoundingSphere() const
{
	return m_customBoundingSphere;
}

void OvCore::ECS::Components::CSpriteRenderer::SetCustomBoundingSphere(const OvRendering::Geometry::BoundingSphere& p_boundingSphere)
{
	m_customBoundingSphere = p_boundingSphere;
}

void OvCore::ECS::Components::CSpriteRenderer::OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{
	OvCore::Helpers::Serializer::SerializeSprite(p_doc, p_node, "sprite", m_sprite);
	OvCore::Helpers::Serializer::SerializeInt(p_doc, p_node, "frustum_behaviour", reinterpret_cast<int&>(m_frustumBehaviour));
	OvCore::Helpers::Serializer::SerializeVec3(p_doc, p_node, "custom_bounding_sphere_position", m_customBoundingSphere.position);
	OvCore::Helpers::Serializer::SerializeFloat(p_doc, p_node, "custom_bounding_sphere_radius", m_customBoundingSphere.radius);
}

void OvCore::ECS::Components::CSpriteRenderer::OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node)
{
	OvCore::Helpers::Serializer::DeserializeSprite(p_doc, p_node, "sprite", m_sprite);
	OvCore::Helpers::Serializer::DeserializeInt(p_doc, p_node, "frustum_behaviour", reinterpret_cast<int&>(m_frustumBehaviour));
	OvCore::Helpers::Serializer::DeserializeVec3(p_doc, p_node, "custom_bounding_sphere_position", m_customBoundingSphere.position);
	OvCore::Helpers::Serializer::DeserializeFloat(p_doc, p_node, "custom_bounding_sphere_radius", m_customBoundingSphere.radius);
}

void OvCore::ECS::Components::CSpriteRenderer::OnInspector(OvUI::Internal::WidgetContainer& p_root)
{
	using namespace OvCore::Helpers;

	GUIDrawer::DrawSprite(p_root, "Sprite", m_sprite, &m_spriteChangedEvent);

	GUIDrawer::CreateTitle(p_root, "Frustum Culling Behaviour");
	auto& boundingMode = p_root.CreateWidget<OvUI::Widgets::Selection::ComboBox>(0);
	boundingMode.choices.emplace(0, "Disabled");
	boundingMode.choices.emplace(1, "Cull model");
	boundingMode.choices.emplace(2, "Cull model & sub-meshes");
	boundingMode.choices.emplace(3, "Cull custom bounding sphere");
	auto& boundingModeDispatcher = boundingMode.AddPlugin<OvUI::Plugins::DataDispatcher<int>>();
	boundingModeDispatcher.RegisterReference(reinterpret_cast<int&>(m_frustumBehaviour));

	auto& centerLabel = p_root.CreateWidget<OvUI::Widgets::Texts::TextColored>("Bounding Sphere Center", GUIDrawer::TitleColor);
	auto& centerWidget = p_root.CreateWidget<OvUI::Widgets::Drags::DragMultipleScalars<float, 3>>(GUIDrawer::GetDataType<float>(), GUIDrawer::_MIN_FLOAT, GUIDrawer::_MAX_FLOAT, 0.f, 0.05f, "", GUIDrawer::GetFormat<float>());
	auto& centerDispatcher = centerWidget.AddPlugin<OvUI::Plugins::DataDispatcher<std::array<float, 3>>>();
	centerDispatcher.RegisterReference(reinterpret_cast<std::array<float, 3>&>(m_customBoundingSphere.position));

	auto& radiusLabel = p_root.CreateWidget<OvUI::Widgets::Texts::TextColored>("Bounding Sphere Radius", GUIDrawer::TitleColor);
	auto& radiusWidget = p_root.CreateWidget<OvUI::Widgets::Drags::DragFloat>(0.0f, GUIDrawer::_MAX_FLOAT, 0.f, 0.1f);
	auto& radiusDispatcher = radiusWidget.AddPlugin<OvUI::Plugins::DataDispatcher<float>>();
	radiusDispatcher.RegisterReference(m_customBoundingSphere.radius);

	boundingMode.ValueChangedEvent += [&](int p_choice)
	{
		centerLabel.enabled = centerWidget.enabled = radiusLabel.enabled = radiusWidget.enabled = p_choice == 3;
	};

	centerLabel.enabled = centerWidget.enabled = radiusLabel.enabled = radiusWidget.enabled = m_frustumBehaviour == EFrustumBehaviour::CULL_CUSTOM;
}
