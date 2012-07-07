#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "Resources.hpp"
#include "Grid.hpp"

#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Engines/BREW.hpp>
#include <SFGUI/Renderer.hpp>

class Application
{
public:
	Application();

	bool run();

private:
	// Setup
	void createWidgets();
	void createSignals();

	// Events
	void onResize();
	void onClickPut();
	void onClickRemove();
	void onClickExit();
	void onMouseWheelMoved(sf::Event aEvent);
	void onInput();

	// SFML elements
	sf::RenderWindow mWindow;
	sfg::SFGUI mSfgui;
	sf::Clock mClock;
	sf::Vector2i miLastPosition;
	sf::Vector2u muLastPosition;
	sf::View mGridView;
	sf::View mGUIView;

	// Resource
	Resources mResources;

	// Grid
	Grid mGrid;
	sf::Rect<unsigned int> mSelectionRect;
	std::vector<sf::Vector2u> mSelection;
	bool mSelectionState;

	// SFGUI elements
	sfg::Desktop mDesktop;
	sfg::Window::Ptr mWndMain;
	sfg::Box::Ptr mSideBar;
	sfg::Box::Ptr mEditBar;
	sfg::Box::Ptr mFileBar;

	sfg::Box::Ptr mTilesBox;
	sfg::Notebook::Ptr mTilesNotebook;
	sfg::Table::Ptr mTilesStaticTable;
	std::vector<sfg::Image::Ptr> mTilesStaticElements;
	sfg::Table::Ptr mTilesAnimatedTable;
	std::vector<sfg::Image::Ptr> mTilesAnimatedElements;

	sfg::ToggleButton::Ptr mBtnPut;
	sfg::ToggleButton::Ptr mBtnRemove;
	sfg::Button::Ptr mBtnAdd;
	sfg::Button::Ptr mBtnSave;
	sfg::Button::Ptr mBtnLoad;
	sfg::Button::Ptr mBtnExit;
};

#endif // APPLICATION_HPP