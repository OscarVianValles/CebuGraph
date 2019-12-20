#include "Application.hpp"
#include "MapState.hpp"

int main()
{
	Application app;

	app.pushState(new MapState(&app));

	app.appLoop();

	return 0;
}
