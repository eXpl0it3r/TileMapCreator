#pragma once


#include <SFML/Graphics.hpp>
#include <Thor/Resources.hpp>
#include <SFGUI/SFGUI.hpp>

// Forward decleration
class Application;

class GUI
{
public:
	/// @brief Constructor.
	///
	GUI();
	
	/// @brief Initializes the GUI.
	/// @param aApp Reference to the Application class for callbacks.
	/// @return True in case everything got initialized correctly, false otherwise.
	bool init(  Application *aApp );
	
	// SFGUI elements
	sfg::SFGUI SFGUI;
	sfg::Desktop Desktop;
	sfg::Window::Ptr WndMain;
	sfg::Box::Ptr SideBar;
	sfg::Box::Ptr EditBar;
	sfg::Box::Ptr FileBar;

	sfg::Box::Ptr TilesBox;
	sfg::Notebook::Ptr TilesNotebook;
	sfg::Table::Ptr TilesStaticTable;
	std::vector<sfg::Image::Ptr> TilesStaticElements;
	sfg::Table::Ptr TilesAnimatedTable;
	std::vector<sfg::Image::Ptr> TilesAnimatedElements;

	sfg::ToggleButton::Ptr BtnPut;
	sfg::ToggleButton::Ptr BtnRemove;
	sfg::Button::Ptr BtnAdd;
	sfg::Button::Ptr BtnSave;
	sfg::Button::Ptr BtnLoad;
	sfg::Button::Ptr BtnExit;

private:
	// Resource pointers
	sf::Font mFont;
	sf::Image mImgPut;
	sfg::Image::Ptr mImgPtrPut;
	sf::Image mImgRemove;
	sfg::Image::Ptr mImgPtrRemove;
	sf::Image mImgAdd;
	sfg::Image::Ptr mImgPtrAdd;
	sf::Image mImgSave;
	sfg::Image::Ptr mImgPtrSave;
	sf::Image mImgLoad;
	sfg::Image::Ptr mImgPtrLoad;
	sf::Image mImgExit;
	sfg::Image::Ptr mImgPtrExit;
};
