#include "Game.h"
#include "Math/Math.h"
//#include "Math/Vector2.h"
#include "Object/Actor.h"
#include "Object/Scene.h"
#include "Math/Random.h"
#include "Math/Color.h"
#include "Math/Transform.h"
#include "Graphics/Shape.h"
#include "..\Game\Actors\Player.h"
#include "..\Game\Actors\Enemy.h"
#include "..\Game\Actors\Projectile.h"
#include "Actor/Locator.h"
#include "Graphics/ParticleSystem.h"
#include "Audio/AudioSystem.h"
#include <iostream>
#include <string>
#include <list>

void Game::Startup()
{
	DWORD ticks = GetTickCount();
	std::cout << ticks / 1000 / 60 / 60 << std::endl;

	g_ps.Startup();

	m_scene.SetGame(this); 

	g_audioSystem.AddAudio("Laser", "Laser.wav");
}

void Game::Shutdown()
{
	//scene.Shutdown();
	g_ps.Shutdown();
}

bool Game::Update(float dt)
{
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	switch (m_state)
	{
	case Game::eState::INIT:
		m_state = eState::TITLE;
		break;
	case Game::eState::TITLE:
	{
			m_lives = 3;
		if (Core::Input::IsPressed(VK_SPACE)) {
			m_state = eState::START_GAME;
			m_score = 0;
		}
	}
		break;
	case Game::eState::START_GAME:
	{
		nc::Actor* player = new nc::Player;
		player->Load("player.txt");

		nc::Locator* locator = new nc::Locator;
		locator->GetTransform().position = nc::Vector2{ 3, 2 };
		//locator->GetTransform().angle = nc::dtor(90);
		player->AddChild(locator);

		locator = new nc::Locator;
		locator->GetTransform().position = nc::Vector2{ -3, 2 };
		//locator->GetTransform().angle = nc::dtor(90);
		player->AddChild(locator);

		m_scene.AddActor(player);
		//actors.push_back(player);

		for (int i = 0; i < 10; i++) {
			nc::Actor* enemy = new nc::Enemy;
			enemy->Load("enemy.txt");
			dynamic_cast<nc::Enemy*>(enemy)->SetTarget(player);
			float distance = nc::random(300, 600);
			float angle = nc::random(0, nc::TWO_PI);
			nc::Vector2 position = nc::Vector2{ 400, 300 } + nc::Vector2::Rotate(nc::Vector2{ distance, 0.0f }, angle);

			enemy->GetTransform().position = position;
			dynamic_cast<nc::Enemy*>(enemy)->SetThrust(nc::random(10, 25));

			m_scene.AddActor(enemy);
		}
		m_state = eState::GAME;
	}
		break;
	case Game::eState::GAME:
	{
		m_spawntimer += dt;
		if (m_spawntimer >= 1.5f) {
			m_spawntimer = 0.0f;

			nc::Actor* enemy = new nc::Enemy;
			enemy->Load("enemy.txt");
			dynamic_cast<nc::Enemy*>(enemy)->SetTarget(m_scene.GetActor<nc::Player>());
			float distance = nc::random(100, 300);
			float angle = nc::random(0, nc::TWO_PI);
			nc::Vector2 position = m_scene.GetActor<nc::Player>()->GetTransform().position + nc::Vector2::Rotate(nc::Vector2{ distance, 0.0f }, angle);

			enemy->GetTransform().position = position;
			dynamic_cast<nc::Enemy*>(enemy)->SetThrust(nc::random(50, 100));

			m_scene.AddActor(enemy);

		}
	}
		break;
	case Game::eState::PLAYER_DEAD:
	{
		auto enemies = m_scene.GetActors<nc::Enemy>();
		for (auto enemy : enemies) {
			enemy->SetTarget(nullptr);
		}
		m_lives -= 1;
		m_state = (m_lives == 0) ? eState::GAME_OVER : eState::GAME_WAIT;
		m_stateTimer = 3.0f;
	}
		break;
	case Game::eState::GAME_WAIT:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0) {
			m_scene.RemoveAllActors();
			m_state = eState::START_GAME;
		}
		break;
	case Game::eState::GAME_OVER:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0) {
			m_scene.RemoveAllActors();
			m_state = eState::TITLE;
		}
		break;
	default:
		break;
	}
	m_scene.Update(dt);

	


	if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT)) {
		int x, y;
		Core::Input::GetMousePos(x, y);

		nc::Color colors[] = { nc::Color::white, nc::Color::red, nc::Color::blue, nc::Color::green, nc::Color::yellow, nc::Color::magenta };
		nc::Color color = colors[rand() % 6];

		g_ps.Create({ x, y }, 0, 180, 30, color, 1, 100, 200);
	}

	g_ps.Update(dt);
	return quit;
}

void Game::Draw(Core::Graphics& graphics)
{
	g_ps.Draw(graphics);
	switch (m_state)
	{
	case Game::eState::INIT:
		break;
	case Game::eState::TITLE:
		graphics.SetColor(nc::Color::green);
		graphics.DrawString(400, 300, "VECTOROIDS");
		break;
	case Game::eState::START_GAME:
		break;
	case Game::eState::GAME:
		break;
	case Game::eState::PLAYER_DEAD:
		break;
	case Game::eState::GAME_WAIT:
		break;
	case Game::eState::GAME_OVER:
		graphics.SetColor(nc::Color::green);
		graphics.DrawString(400, 300, "GAME OVER");
		break;
	default:
		break;
	}

	graphics.SetColor(nc::Color::white);
	graphics.DrawString(700, 10, std::to_string(m_score).c_str());
	graphics.DrawString(700, 20, ("LIVES: " + std::to_string(m_lives)).c_str());

	m_scene.Draw(graphics);
}
