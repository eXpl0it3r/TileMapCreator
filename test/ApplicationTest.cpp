#include <boost/test/unit_test.hpp>

#include "Application.hpp"

BOOST_AUTO_TEST_CASE( ApplicationTest )
{
	Application app;
	BOOST_ASSERT( app.init() );
}

