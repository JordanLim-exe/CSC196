#include "Player.h"
#include "Projectile.h"
#include "Math/Math.h"
#include "Object\Scene.h"
#include "..\Game.h"
#include "Graphics\ParticleSystem.h"
#include <fstream>

namespace nc
{
    bool Player::Load(const std::string& filename)
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
            
			// stream into rotation rate
			stream >> m_rotation;

            stream.close();
        }

        return success;
    }

    void Player::Update(float dt)
    {
		m_firetimer += dt;

		if (Core::Input::IsPressed(VK_SPACE) && m_firetimer >= m_firerate) {
			/*auto removeActors = GetActors<nc::Enemy>();
			for (auto actor : removeActors) {
				auto iter = std::find(actors.begin(), actors.end(), actor);
				delete* iter;
				actors.erase(iter);
			}
			scene.Shutdown();*/
			m_firetimer = 0;
			Projectile* projectile = new Projectile;
			projectile->Load("projectile.txt");
			projectile->GetTransform().position = m_transform.position;
			projectile->GetTransform().angle = m_transform.angle;
			m_scene->AddActor(projectile);
		}

		//float thrust = 250.0f;
		float t{ 0 };

		float frametime;
		float roundTime{ 0 };
		bool gameOver{ false };

		//DWORD prevTime;
		DWORD deltaTime;
        // this code will be the current code to control the player that is in main.cpp/Game.cpp
		//dt = current frame time - previous frame time
		DWORD time = GetTickCount();
		//deltaTime = time - prevTime;

		//prevTime = time;

		t = t + dt * 5;

		frametime = dt;
		roundTime += dt;

		if (roundTime >= 60.0f) gameOver = true;

		dt *= 2.0f;
		if (gameOver)dt *= 0;

		int x;
		int y;
		Core::Input::GetMousePos(x, y);

		//nc::Vector2 target = nc::Vector2{ x,y };
		//nc::Vector2 direction = target - position; // (head <- tail)
		//direction.Normalize();

		nc::Vector2 force;
		if (Core::Input::IsPressed(Core::Input::KEY_UP)) { force = nc::Vector2::forward * m_thrust; }
		force = nc::Vector2::Rotate(force, m_transform.angle);
		force += nc::Vector2{ 0, 50 };

		velocity += force * dt;
		velocity *= 0.99f;
		m_transform.position += velocity * dt;

		if (Core::Input::IsPressed(Core::Input::KEY_LEFT)) { m_transform.angle -= dt * nc::dtor(360.0f); }
		if (Core::Input::IsPressed(Core::Input::KEY_RIGHT)) { m_transform.angle += dt * nc::dtor(360.0f); }

		if (m_transform.position.x > 800) m_transform.position.x = 0;
		if (m_transform.position.x < 0) m_transform.position.x = 800;
		if (m_transform.position.y > 600) m_transform.position.y = 0;
		if (m_transform.position.y < 0) m_transform.position.y = 600;

		if (force.LengthSqr() > 0) {
			g_ps.Create(m_transform.position, m_transform.angle + nc::PI, 20, 1, nc::Color::white, 1, 100, 200);
		}
		m_transform.Update();

		//player.GetTransform().position = nc::Clamp(player.GetTransform().position, { 0, 0 }, { 800, 600 });

		//enemy
		


		/*transform.position.x = nc::Clamp(transform.position.x, 0.0f, 800.0f);
		transform.position.y = nc::Clamp(transform.position.y, 0.0f, 600.0f);*/
		//if (Core::Input::IsPressed(Core::Input::KEY_LEFT)) { position += nc::Vector2::left * speed * dt; }
		//if (Core::Input::IsPressed(Core::Input::KEY_RIGHT)) { position += nc::Vector2::right * speed * dt; }
		//if (Core::Input::IsPressed(Core::Input::KEY_UP)) { position += nc::Vector2::up * speed * dt; }
		//if (Core::Input::IsPressed(Core::Input::KEY_DOWN)) { position += nc::Vector2::down * speed * dt; }
		/*for (nc::Vector2& point : points) {
			point = { nc::random(-10.0f, 10.0f), nc::random(-10.0f, 10.0f) };
		}*/

        // you will be using the m_transform, thrust and rotation rate of this class
                // example:
                // m_transform.position = m_transform.position + m_velocity * dt;
                // and
                // if (Core::Input::IsPressed('A')) { m_transform.angle = m_transform.angle - (nc::DegreesToRadians(m_rotationRate) * dt); }
    }

	void Player::OnCollision(Actor* actor)
	{
		if (actor->GetType() == eType::ENEMY) {
			m_scene->GetGame()->SetState(Game::eState::GAME_OVER);
		}
	}

    
}

