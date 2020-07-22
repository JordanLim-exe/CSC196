
#include "core.h"
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

//nc::Actor player;
//nc::Actor enemy;
//float thrust = 250.0f;
//nc::Vector2 velocity;
//
//float t{ 0 };
//
//float frametime;
//float roundTime{ 0 };
//bool gameOver{ false };
//
//DWORD prevTime;
//DWORD deltaTime;
//std::list<nc::Actor*> actors;

nc::Scene scene;
nc::ParticleSystem ps;

float spawntimer{ 0 };


bool Update(float dt) // delta time (60 fps) (1 / 60 = 0.016)
{
	//dt = current frame time - previous frame time
	//DWORD time = GetTickCount();
	//deltaTime = time - prevTime;
	//
	//prevTime = time;
	//
	//t = t + dt * 5;
	//
	//bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	//
	//frametime = dt;
	//roundTime += dt;
	//
	//if (roundTime >= 60.0f) gameOver = true;
	//
	//dt *= 2.0f;
	//if (gameOver)dt *= 0;
	//
	//int x;
	//int y;
	//Core::Input::GetMousePos(x, y);
	//
	////nc::Vector2 target = nc::Vector2{ x,y };
	////nc::Vector2 direction = target - position; // (head <- tail)
	////direction.Normalize();
	//
	//nc::Vector2 force;
	//if (Core::Input::IsPressed(Core::Input::KEY_UP)) { force = nc::Vector2::forward * thrust; }
	//force = nc::Vector2::Rotate(force, player.GetTransform().angle);
	//force += nc::Vector2{ 0, 50 };
	//
	//velocity += force * dt;
	//velocity = velocity * 0.99f;
	//player.GetTransform().position += velocity * dt;
	//
	//if (Core::Input::IsPressed(Core::Input::KEY_LEFT)) { player.GetTransform().angle -= dt * nc::dtor(360.0f); }
	//if (Core::Input::IsPressed(Core::Input::KEY_RIGHT)) { player.GetTransform().angle += dt * nc::dtor(360.0f); }
	//
	//if (player.GetTransform().position.x > 800) player.GetTransform().position.x = 0;
	//if (player.GetTransform().position.x < 0) player.GetTransform().position.x = 800;
	//if (player.GetTransform().position.y > 600) player.GetTransform().position.y = 0;
	//if (player.GetTransform().position.y < 0) player.GetTransform().position.y = 600;
	//
	////player.GetTransform().position = nc::Clamp(player.GetTransform().position, { 0, 0 }, { 800, 600 });
	//
	////enemy
	//nc::Vector2 direction = player.GetTransform().position - enemy.GetTransform().position;
	//nc::Vector2 e_velocity = direction.Normalized() * 100.0f;
	//enemy.GetTransform().position += e_velocity * dt;
	//enemy.GetTransform().angle = std::atan2(direction.y, direction.x) + nc::dtor(90.0f);
	//
	//
	//transform.position.x = nc::Clamp(transform.position.x, 0.0f, 800.0f);
	//transform.position.y = nc::Clamp(transform.position.y, 0.0f, 600.0f);*/
	////if (Core::Input::IsPressed(Core::Input::KEY_LEFT)) { position += nc::Vector2::left * speed * dt; }
	////if (Core::Input::IsPressed(Core::Input::KEY_RIGHT)) { position += nc::Vector2::right * speed * dt; }
	////if (Core::Input::IsPressed(Core::Input::KEY_UP)) { position += nc::Vector2::up * speed * dt; }
	////if (Core::Input::IsPressed(Core::Input::KEY_DOWN)) { position += nc::Vector2::down * speed * dt; }
	//for (nc::Vector2& point : points) {
	//	point = { nc::random(-10.0f, 10.0f), nc::random(-10.0f, 10.0f) };
	//}

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	ps.Update(dt);
	scene.Update(dt);
	

	spawntimer += dt;
	if (spawntimer >= 3.0f) {
		spawntimer = 0.0f;

		//add enemy to scene
		/*nc::Actor* enemy = new nc::Enemy;
		enemy->Load("enemy.txt");
		dynamic_cast<nc::Enemy*>(enemy)->SetTarget(player);
		enemy->GetTransform().position = nc::Vector2{ nc::random(0, 800), nc::random(0, 600) };
		dynamic_cast<nc::Enemy*>(enemy)->SetThrust(nc::random(50, 100));

		scene.AddActor(enemy);*/

	}

	nc::Player* player = scene.GetActor<nc::Player>();
	ps.Create(player->GetTransform().position, player->GetTransform().angle + nc::PI, 20, 1, nc::Color(1, 1, 1), 1, 100, 200);
	

	return quit;
}

void Draw(Core::Graphics& graphics)
{
	//graphics.DrawString(10, 10, std::to_string(frametime).c_str());
	//graphics.DrawString(10, 20, std::to_string(1.0f / frametime).c_str());
	//graphics.DrawString(10, 30, std::to_string(deltaTime).c_str())
	//float v = (std::sin(t) + 1.0f) * 0.5f;
	//nc::Color c = nc::Lerp(nc::Color{ 0, 0, 1 }, nc::Color{ 1, 0, 0 }, v);
	//graphics.SetColor(c);
	//nc::Vector2 p = nc::Lerp(nc::Vector2{ 40, 300 }, nc::Vector2{ 400, 100 }, v);
	//graphics.DrawString(p.x, p.y, "LSF");
	//graphics.DrawLine(static_cast<float>(rand() % 800), static_cast<float>(rand() % 600), static_cast<float>(rand() % 800), static_cast<float>(rand() % 600));
	//if (gameOver) graphics.DrawString(400, 300, "Game Over");
	//for (size_t i = 0; i < points.size() - 1; i++) {
	//	
	//	//local / object space points
	//	nc::Vector2 p1 = points[i];
	//	nc::Vector2 p2 = points[i + 1];
	//	//transform
	//	//scale
	//	p1 *= scale;
	//	p2 *= scale;
	//	//rotate
	//	p1 = nc::Vector2::Rotate(p1, angle);
	//	p2 = nc::Vector2::Rotate(p2, angle);
	//	//translate
	//	p1 += position;
	//	p2 += position;
	//	graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	//}
	ps.Draw(graphics);
	scene.Draw(graphics);

}

int main()
{
	DWORD ticks = GetTickCount();
	std::cout << ticks / 1000 / 60 / 60 << std::endl;

	ps.Startup();

	nc::Actor* player = new nc::Player;
	player->Load("player.txt");
	scene.AddActor(player);
	//actors.push_back(player);
	
	for (int i = 0; i < 10; i++) {
		nc::Actor* enemy = new nc::Enemy;
		enemy->Load("enemy.txt");
		dynamic_cast<nc::Enemy*>(enemy)->SetTarget(player);
		enemy->GetTransform().position = nc::Vector2{ nc::random(0, 800), nc::random(0, 600) };
		dynamic_cast<nc::Enemy*>(enemy)->SetThrust(nc::random(50, 100));

		scene.AddActor(enemy);
	}


	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
	//scene.Shutdown();
	ps.Shutdown();
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
