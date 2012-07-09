#pragma once

#include <Thor/Resources.hpp>
#include <SFML/Graphics.hpp>
#include "GUI.hpp"
/*#include "Grid.hpp"

#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Engines/BREW.hpp>
#include <SFGUI/Renderer.hpp>*/

class Application
{
public:
	/// @brief Constructor.
	///
	Application();

	/// @brief Initialization with possible error returner.
	/// @return True in case everything got initialized correctly, false otherwise.
	bool init();

	/// @brief Starts the application, that includes create a window and managing the GUI, etc.
	/// @return True in case everything run correctly, false otherwise.
	bool run();

	/// @brief Callback function if button 'put' is pressed.
	///
	void onClickPut();

	/// @brief Callback function if button 'remove' is pressed.
	///
	void onClickRemove();

	/// @brief Callback function if button 'exit' is pressed.
	///
	void onClickExit();

	/// @brief Callback function if the window gets resized. Can also be used to update the views.
	///
	void onResize();

private:
	// Cache for resources
	thor::MultiResourceCache mCache;

	// Window
	sf::RenderWindow mWindow;

	// GUI
	GUI mGUI;
	sf::View mGUIView;

	// Grid
	sf::View mGridView;

	// Time management
	sf::Clock mClock;

	/*
	// Events
	void onMouseWheelMoved(sf::Event aEvent);
	void onInput();

	// SFML elements
	sf::Vector2i miLastPosition;
	sf::Vector2u muLastPosition;

	// Grid
	Grid mGrid;
	sf::Rect<unsigned int> mSelectionRect;
	std::vector<sf::Vector2u> mSelection;
	bool mSelectionState;*/
};
