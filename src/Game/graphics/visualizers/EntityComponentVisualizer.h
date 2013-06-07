#pragma once
#include <graphics/AnimatedDraw.h>
#include <components/Component.h>
#include <Entity.h>
#include <Engine.h>
#include <Graphics/Sprites/SpriteInterface.h>
namespace Game
{
	namespace Graphics
	{
		const std::string EntityVisualizerComponentIndex = "EntityVisualizerComponent";

		class EntityVisualizer : public Components::Component, public virtual ::Graphics::AnimatedDraw, public virtual ::Graphics::SpriteInterface
		{
		public:
			EntityVisualizer(Engine* engine, Entity* owner) : Eng(engine), Components::Component(owner, owner != nullptr ? owner->GetName() + "Visualizer" : "BlankEntityVisualizer", "EntityVisualizer")
			{
			}
		protected:
			Engine* Eng;
		private:
		};

		class ComponentVisualizer : public Components::Component, public virtual ::Graphics::AnimatedDraw, public virtual ::Graphics::SpriteInterface
		{
		public:
			ComponentVisualizer(Engine* engine, Components::Component* visualizing, Entity* owner) : Eng(engine), Components::Component(owner, owner != nullptr ? owner->GetName() + "Visualizer" : "BlankComponentVisualizer", "ComponentVisualizer"), VisualizingComponent(visualizing)
			{

			}
		protected:
			Components::Component* VisualizingComponent;
			Engine* Eng;
		private:
		};
	}
}