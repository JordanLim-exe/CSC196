#pragma once
#include "Object/Actor.h"

namespace nc {
	class Player : public nc::Actor {
	public:
		Player() {}
		virtual ~Player() {}

		virtual eType GetType() { return nc::Actor::eType::PLAYER; }

		virtual bool Load(const std::string& filename) override;

		virtual void Update(float dt) override;
		
		virtual void OnCollision(Actor* actor);

	protected:
		float m_thrust;
		float m_rotation;
		Vector2 velocity;
		float m_firetimer{ 0.2f };
		float m_firerate{ 0.2f };
	};
}