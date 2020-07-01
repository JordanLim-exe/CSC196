
#include "core.h"
#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Math/Random.h"
#include <iostream>

const size_t NUM_POINTS = 40;
float speed = 5.0f;
std::vector<nc::Vector2> points;
nc::Vector2 position{ 400.0f, 300.0f };



bool Update(float dt)
{
	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);
	
	int x;
	int y;
	Core::Input::GetMousePos(x, y);

	nc::Vector2 target = nc::Vector2{ x,y };
	nc::Vector2 direction = target - position; // (head <- tail)
	direction.Normalize();

	position += direction * 5.0f;

	if (Core::Input::IsPressed(Core::Input::KEY_LEFT)) { position += nc::Vector2{ -1.0f, 0.0f } * speed; }
	if (Core::Input::IsPressed(Core::Input::KEY_RIGHT)) { position += nc::Vector2{ 1.0f, 0.0f } * speed; }
	if (Core::Input::IsPressed(Core::Input::KEY_UP)) { position += nc::Vector2{ 0.0f, -1.0f } * speed; }
	if (Core::Input::IsPressed(Core::Input::KEY_DOWN)) { position += nc::Vector2{ 0.0f, 1.0f } * speed; }

	for (nc::Vector2& point : points) {
		point = { nc::random(-10.0f, 10.0f), nc::random(-10.0f, 10.0f) };
	}


	return quit;
}

void Draw(Core::Graphics& graphics)
{
	graphics.SetColor(RGB(rand() % 256, rand() % 256, rand() % 256));
	//graphics.DrawLine(static_cast<float>(rand() % 800), static_cast<float>(rand() % 600), static_cast<float>(rand() % 800), static_cast<float>(rand() % 600));

	for (size_t i = 0; i < NUM_POINTS - 1; i++) {
		nc::Vector2 p1 = position + points[i] * 5.0f;
		nc::Vector2 p2 = position + points[i + 1] + 5.0f;

		graphics.DrawLine(p1.x, p1.y, p2.x, p2.y);
	}

}

int main()
{
	for (size_t i = 0; i < NUM_POINTS; i++) {
		points.push_back(nc::Vector2{ nc::random(0.0f, 800.0f), nc::random(0.0f, 600.0f) });
	}

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
