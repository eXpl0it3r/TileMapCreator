#include <boost/test/unit_test.hpp>

#include "Application.hpp"
#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>
#include "GUI.hpp"

BOOST_AUTO_TEST_CASE( GUITest )
{
	Application app;
	thor::MultiResourceCache res;

	GUI gui;
	BOOST_ASSERT( gui.init(&app) );
}
