#include "Player.h"
#include "Projectile.h"
#include "Math/Math.h"
#include "Object\Scene.h"
#include "..\Game.h"
#include "Graphics\ParticleSystem.h"
#include <fstream>
#include "Audio/AudioSystem.h"

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
			g_audioSystem.PlayAudio("Laser");
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
		force += nc::Vector2{ 0, 0 };

		velocity += force * dt;
		velocity *= 0.97f;
		m_transform.position += velocity * dt;

		float torque = 0;
		if (Core::Input::IsPressed(Core::Input::KEY_LEFT)) { torque = -nc::dtor(m_rotation); }
		if (Core::Input::IsPressed(Core::Input::KEY_RIGHT)) { torque = nc::dtor(m_rotation); }

		m_angularVelocity += torque * dt;
		m_angularVelocity *= 0.95f;
		m_transform.angle += m_angularVelocity * dt;

		if (m_transform.position.x > 800) m_transform.position.x = 0;
		if (m_transform.position.x < 0) m_transform.position.x = 800;
		if (m_transform.position.y > 600) m_transform.position.y = 0;
		if (m_transform.position.y < 0) m_transform.position.y = 600;

		if (force.LengthSqr() > 0) {
			Actor* locator = m_children[0];
			g_ps.Create(locator->GetTransform().matrix.GetPosition(), locator->GetTransform().matrix.GetAngle() + nc::PI, 20, 1, nc::Color::white, 1, 100, 200);

			locator = m_children[1];
			g_ps.Create(locator->GetTransform().matrix.GetPosition(), locator->GetTransform().matrix.GetAngle() + nc::PI, 20, 1, nc::Color::white, 1, 100, 200);
		}
		m_transform.Update();

		for (auto child: m_children) {
			child->Update(dt);
		}
    }

	void Player::OnCollision(Actor* actor)
	{
		if (actor->GetType() == eType::ENEMY) {
			m_scene->GetGame()->SetState(Game::eState::PLAYER_DEAD);
			m_destroy = true;

			nc::Color colors[] = { nc::Color::white, nc::Color::red, nc::Color::blue, nc::Color::green, nc::Color::yellow, nc::Color::magenta };
			nc::Color color = colors[rand() % 6];

			g_ps.Create({ m_transform.position.x, m_transform.position.y }, 0, 180, 30, color, 1, 100, 200);
		}
	}

    
}

