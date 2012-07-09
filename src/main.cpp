#include "Application.hpp"

int main()
{
	Application app;

	if(!app.init())
		return -1;

	if(!app.run())
		return -2;

	return 0;
}