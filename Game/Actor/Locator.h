#pragma once
#include "Object/Actor.h"

namespace nc {
	class Locator : public nc::Actor {
	public:
		Locator() = default;
		~Locator() {}

		virtual eType GetType() { return nc::Actor::eType::LOCATOR; }
		
		virtual void Update(float dt) override;

	protected:
		float m_thrust{ 0.0f };
		float m_lifetime{ 3 };
	};
}