#pragma once
#include "Object/Actor.h"

namespace nc {
	class Projectile : public nc::Actor {
	public:
		Projectile() = default;
		~Projectile() {}

		virtual eType GetType() { return nc::Actor::eType::PROJECTILE; }

		virtual bool Load(const std::string& filename) override;

		virtual void Update(float dt) override;

		void SetThrust(float thrust) { m_thrust = thrust; }

	protected:
		float m_thrust{ 0.0f };
	};
}