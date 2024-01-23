/**
* @project: Overload
* @author: Overload Tech.
* @licence: MIT
*/

#pragma once

#include <OvRendering/Geometry/Vertex.h>
#include <OvRendering/Resources/Sprite.h>

#include "OvCore/ECS/Components/AComponent.h"

namespace OvCore::ECS { class Actor; }

namespace OvCore::ECS::Components
{
	/**
	* A SpriteRenderer is necessary in combination with a MaterialRenderer to render a sprite in the world
	*/
	class CSpriteRenderer : public AComponent
	{
	public:
		/**
		* Defines how the sprite renderer bounding sphere should be interpreted
		*/
		enum class EFrustumBehaviour
		{
			DISABLED = 0,
			CULL_MODEL = 1,
			CULL_MESHES = 2,
			CULL_CUSTOM = 3
		};

		/**
		* Constructor
		* @param p_owner
		*/
		CSpriteRenderer(ECS::Actor& p_owner);

		/**
		* Returns the name of the component
		*/
		std::string GetName() override;

		/**
		* Defines the model to use
		* @param p_model
		*/
		void SetSprite(OvRendering::Resources::Sprite* p_sprite);

		/**
		* Returns the current model
		*/
		OvRendering::Resources::Sprite* GetSprite() const;

		/**
		* Sets a bounding mode
		* @param p_boundingMode
		*/
		void SetFrustumBehaviour(EFrustumBehaviour p_boundingMode);

		/**
		* Returns the current bounding mode
		*/
		EFrustumBehaviour GetFrustumBehaviour() const;

		/**
		* Returns the custom bounding sphere
		*/
		const OvRendering::Geometry::BoundingSphere& GetCustomBoundingSphere() const;

		/**
		* Sets the custom bounding sphere
		* @param p_boundingSphere
		*/
		void SetCustomBoundingSphere(const OvRendering::Geometry::BoundingSphere& p_boundingSphere);

		/**
		* Serialize the component
		* @param p_doc
		* @param p_node
		*/
		virtual void OnSerialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

		/**
		* Deserialize the component
		* @param p_doc
		* @param p_node
		*/
		virtual void OnDeserialize(tinyxml2::XMLDocument& p_doc, tinyxml2::XMLNode* p_node) override;

		/**
		* Defines how the component should be drawn in the inspector
		* @param p_root
		*/
		virtual void OnInspector(OvUI::Internal::WidgetContainer& p_root) override;

	private:
		OvRendering::Resources::Sprite* m_sprite = nullptr;
		OvTools::Eventing::Event<> m_spriteChangedEvent;
		OvRendering::Geometry::BoundingSphere m_customBoundingSphere = { {}, 1.0f };
		EFrustumBehaviour m_frustumBehaviour = EFrustumBehaviour::CULL_MODEL;
	};
}