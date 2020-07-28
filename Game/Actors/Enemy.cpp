#include "Enemy.h"
#include "Math/Math.h"
#include "Graphics/ParticleSystem.h"
#include "Object/Scene.h"
#include "../Game.h"
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
        nc::Vector2 direction;
        if (m_target) {
            direction = m_target->GetTransform().position - m_transform.position;
            m_transform.angle = std::atan2(direction.y, direction.x) + nc::dtor(90.0f);

        }

        nc::Vector2 e_velocity = direction.Normalized() * m_thrust;
        m_transform.position += e_velocity * dt;

        m_transform.Update();
        // to compute the direction to move towards, use the pointer to the player actor

       
    }
	void Enemy::OnCollision(Actor* actor)
	{
        if (actor->GetType() == eType::PROJECTILE) {
            m_destroy = true;

            //set game score
            m_scene->GetGame()->AddPoints(100);

            nc::Color colors[] = { nc::Color::white, nc::Color::red, nc::Color::blue, nc::Color::green, nc::Color::yellow, nc::Color::magenta };
            nc::Color color = colors[rand() % 6];

            g_ps.Create({ m_transform.position.x, m_transform.position.y }, 0, 180, 30, color, 1, 100, 200);
        }
	}
}