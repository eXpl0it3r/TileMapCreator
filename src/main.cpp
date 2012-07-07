#include "Application.hpp"

int main()
{
	Application app;

	if(!app.run())
		return -1;

	return 0;
}