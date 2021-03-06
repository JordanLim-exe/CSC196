#include "core.h"
#include "Game.h"
#include "Audio/AudioSystem.h"
#include <time.h>

Game game;

bool Update(float dt)
{
	return game.Update(dt);
}

void Draw(Core::Graphics& graphics)
{
	game.Draw(graphics);
}

int main()
{
	srand(static_cast<unsigned int>(time(NULL)));


	g_audioSystem.Startup();
	game.Startup();

	char name[] = "CSC196";
	Core::Init(name, 800, 600);
	Core::RegisterUpdateFn(Update);
	Core::RegisterDrawFn(Draw);

	Core::GameLoop();
	Core::Shutdown();
	
	game.Shutdown();
	g_audioSystem.Shutdown();
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
