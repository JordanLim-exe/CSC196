
#include "core.h"
#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Math/Random.h"
#include "Math/Color.h"
#include <iostream>

const size_t NUM_POINTS = 40;
float speed = 5.0f;

std::vector<nc::Vector2> points = { { 0, -3 }, { 3, 3 }, { 0, 1 }, { -3, 3 }, { 0, -3 } };
nc::Color color{ 0, 1, 0 };

nc::Vector2 position{ 400.0f, 300.0f };
float scale = 4.0f;
float angle = 0.0f;



bool Update(float dt)
{
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	
	int x;
	int y;
	Core::Input::GetMousePos(x, y);

	nc::Vector2 target = nc::Vector2{ x,y };
	nc::Vector2 direction = target - position; // (head <- tail)
	direction.Normalize();

	//position += direction * 5.0f;

	if (Core::Input::IsPressed(Core::Input::KEY_LEFT)) { angle -= dt * 2.0f; }
	if (Core::Input::IsPressed(Core::Input::KEY_RIGHT)) { angle += dt * 2.0f; }

	//if (Core::Input::IsPressed(Core::Input::KEY_LEFT)) { position += nc::Vector2{ -1.0f, 0.0f } * speed; }
	//if (Core::Input::IsPressed(Core::Input::KEY_RIGHT)) { position += nc::Vector2{ 1.0f, 0.0f } * speed; }
	//if (Core::Input::IsPressed(Core::Input::KEY_UP)) { position += nc::Vector2{ 0.0f, -1.0f } * speed; }
	//if (Core::Input::IsPressed(Core::Input::KEY_DOWN)) { position += nc::Vector2{ 0.0f, 1.0f } * speed; }

	/*for (nc::Vector2& point : points) {
		point = { nc::random(-10.0f, 10.0f), nc::random(-10.0f, 10.0f) };
	}*/


	return quit;
}

void Draw(Core::Graphics& graphics)
{


	graphics.SetColor(color.Pack888());
	//graphics.DrawLine(static_cast<float>(rand() % 800), static_cast<float>(rand() % 600), static_cast<float>(rand() % 800), static_cast<float>(rand() % 600));

	for (size_t i = 0; i < points.size() - 1; i++) {
		
		//local / object space points
		nc::Vector2 p1 = points[i];
		nc::Vector2 p2 = points[i + 1];

		//transform
		//scale
		p1 *= scale;
		p2 *= scale;
		//rotate
		p1 = nc::Vector2::Rotate(p1, angle);
		p2 = nc::Vector2::Rotate(p2, angle);
		//translate
		p1 += position;
		p2 += position;


		graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}

}

int main()
{
	/*for (size_t i = 0; i < NUM_POINTS; i++) {
		points.push_back(nc::Vector2{ nc::random(0.0f, 800.0f), nc::random(0.0f, 600.0f) });
	}*/

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
