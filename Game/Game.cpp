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
#include "Graphics/ParticleSystem.h"
#include <iostream>
#include <string>
#include <list>

void Game::Startup()
{
	DWORD ticks = GetTickCount();
	std::cout << ticks / 1000 / 60 / 60 << std::endl;

	g_ps.Startup();

	m_scene.SetGame(this); 
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
		break;
	case Game::eState::TITLE:
	{
		if (Core::Input::IsPressed(VK_SPACE)) {
			m_state = eState::START_GAME;
		}
	}
		break;
	case Game::eState::START_GAME:
	{
		nc::Actor* player = new nc::Player;
		player->Load("player.txt");
		m_scene.AddActor(player);
		//actors.push_back(player);

		for (int i = 0; i < 10; i++) {
			nc::Actor* enemy = new nc::Enemy;
			enemy->Load("enemy.txt");
			dynamic_cast<nc::Enemy*>(enemy)->SetTarget(player);
			enemy->GetTransform().position = nc::Vector2{ nc::random(0, 800), nc::random(0, 600) };
			dynamic_cast<nc::Enemy*>(enemy)->SetThrust(nc::random(50, 100));

			m_scene.AddActor(enemy);
		}
		m_state = eState::GAME;
	}
		break;
	case Game::eState::GAME:
	{
		m_spawntimer += dt;
		if (m_spawntimer >= 3.0f) {
			m_spawntimer = 0.0f;

			nc::Actor* enemy = new nc::Enemy;
			enemy->Load("enemy.txt");
			dynamic_cast<nc::Enemy*>(enemy)->SetTarget(m_scene.GetActor<nc::Player>());
			enemy->GetTransform().position = nc::Vector2{ nc::random(0, 800), nc::random(0, 600) };
			dynamic_cast<nc::Enemy*>(enemy)->SetThrust(nc::random(50, 100));

			m_scene.AddActor(enemy);

		}
		m_scene.Update(dt);
	}
		break;
	case Game::eState::GAME_OVER:
		break;
	default:
		break;
	}

	


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
		graphics.SetColor(nc::Color::white);
		graphics.DrawString(700, 10, std::to_string(m_score).c_str());
		m_scene.Draw(graphics);
		break;
	case Game::eState::GAME_OVER:
		graphics.SetColor(nc::Color::green);
		graphics.DrawString(400, 300, "GAME OVER");
		break;
	default:
		break;
	}
}
