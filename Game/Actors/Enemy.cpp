#include "Enemy.h"
#include "Math/Math.h"
#include <fstream>

namespace nc {
    bool Enemy::Load(const std::string& filename)
    {
        bool success = false;

        std::ifstream stream(filename);
        if (stream.is_open())
        {
            success = true;

            // load the base actor members
            //std::string actorname;
            //stream >> actorname;
            Actor::Load(stream);

            // stream into thrust
            stream >> m_thrust;

            stream.close();
        }

        return success;
    }

    void Enemy::Update(float dt)
    {
        // this code will be the current code to control the enemy that is in main.cpp/Game.cpp

        nc::Vector2 direction = m_target->GetTransform().position - m_transform.position;
        nc::Vector2 e_velocity = direction.Normalized() * 0;// m_thrust;
        m_transform.position += e_velocity * dt;
        m_transform.angle = std::atan2(direction.y, direction.x) + nc::dtor(90.0f);

        m_transform.Update();
        // to compute the direction to move towards, use the pointer to the player actor

       
    }
	void Enemy::OnCollision(Actor* actor)
	{
        if (actor->GetType() == eType::PROJECTILE) {
            m_destroy = true;
        }
	}
}