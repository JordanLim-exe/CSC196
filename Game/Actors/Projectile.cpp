#include "Projectile.h"
#include "Math/Math.h"
#include <fstream>

namespace nc {
    bool Projectile::Load(const std::string& filename)
    {
        bool success = false;

        std::ifstream stream(filename);
        if (stream.is_open())
        {
            success = true;

            // load the base actor members
            Actor::Load(stream);

            // stream into thrust
            stream >> m_thrust;

            stream.close();
        }

        return success;
    }

    void Projectile::Update(float dt)
    {
        // this code will be the current code to control the enemy that is in main.cpp/Game.cpp
        
        //m_transform.angle = std::atan2(direction.y, direction.x) + nc::dtor(90.0f);

        nc::Vector2 direction = nc::Vector2::Rotate(nc::Vector2::forward, m_transform.angle);
        nc::Vector2 e_velocity = direction.Normalized() * m_thrust;
        m_transform.position += e_velocity * dt;

        m_transform.Update();
        // to compute the direction to move towards, use the pointer to the player actor

       
    }
}