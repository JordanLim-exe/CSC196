
#include "core.h"
#include "Math/Math.h"
//#include "Math/Vector2.h"
#include "Math/Random.h"
#include "Math/Color.h"
#include "Math/Transform.h"
#include "Graphics/Shape.h"
#include <iostream>
#include <string>

const size_t NUM_POINTS = 40;
float speed = 250.0f;

nc::Shape ship;
//nc::Shape ship{ points, color };

nc::Transform transform{ {400, 300}, 3, 0 };

float frametime;
float roundTime{ 0 };
bool gameOver{ false };

DWORD prevTime;
DWORD deltaTime;


bool Update(float dt) // delta time (60 fps) (1 / 60 = 0.016)
{
	//dt = current frame time - previous frame time
	DWORD time = GetTickCount();
	deltaTime = time - prevTime;

	prevTime = time;



	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	
	frametime = dt;
	roundTime += dt;

	if (roundTime >= 5.0f) gameOver = true;

	dt *= 2.0f;
	if (gameOver)dt *= 0;

	int x;
	int y;
	Core::Input::GetMousePos(x, y);

	//nc::Vector2 target = nc::Vector2{ x,y };
	//nc::Vector2 direction = target - position; // (head <- tail)
	//direction.Normalize();

	nc::Vector2 force;
	if (Core::Input::IsPressed(Core::Input::KEY_UP)) { force = nc::Vector2::forward * speed * dt; }
	nc::Vector2 direction = force;
	direction = nc::Vector2::Rotate(direction, transform.angle);
	transform.position += direction;

	if (Core::Input::IsPressed(Core::Input::KEY_LEFT)) { transform.angle -= dt * 3.0f; }
	if (Core::Input::IsPressed(Core::Input::KEY_RIGHT)) { transform.angle += dt * 3.0f; }

	//if (Core::Input::IsPressed(Core::Input::KEY_LEFT)) { position += nc::Vector2::left * speed * dt; }
	//if (Core::Input::IsPressed(Core::Input::KEY_RIGHT)) { position += nc::Vector2::right * speed * dt; }
	//if (Core::Input::IsPressed(Core::Input::KEY_UP)) { position += nc::Vector2::up * speed * dt; }
	//if (Core::Input::IsPressed(Core::Input::KEY_DOWN)) { position += nc::Vector2::down * speed * dt; }
	/*for (nc::Vector2& point : points) {
		point = { nc::random(-10.0f, 10.0f), nc::random(-10.0f, 10.0f) };
	}*/


	return quit;
}

void Draw(Core::Graphics& graphics)
{
	graphics.DrawString(10, 10, std::to_string(frametime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / frametime).c_str());
	graphics.DrawString(10, 30, std::to_string(deltaTime).c_str());

	
	//graphics.DrawLine(static_cast<float>(rand() % 800), static_cast<float>(rand() % 600), static_cast<float>(rand() % 800), static_cast<float>(rand() % 600));

	if (gameOver) graphics.DrawString(400, 300, "Game Over");

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

	ship.Draw(graphics, transform);

}

int main()
{
	DWORD ticks = GetTickCount();
	std::cout << ticks / 1000 / 60 / 60 << std::endl;
	/*for (size_t i = 0; i < NUM_POINTS; i++) {
		points.push_back(nc::Vector2{ nc::random(0.0f, 800.0f), nc::random(0.0f, 600.0f) });
	}*/
	prevTime = GetTickCount();

	ship.Load("ship.txt");
	//ship.SetColor(nc::Color{ 1, 1, 1 });

	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
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
