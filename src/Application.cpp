#include "Application.hpp"

Application::Application()
{
}

bool Application::init()
{
	mWindow.create(sf::VideoMode(1024, 768, 32), "Tile Map Creator", sf::Style::Close | sf::Style::Resize | sf::Style::Titlebar);
	mWindow.resetGLStates();
	mWindow.setFramerateLimit(30);

	// Initialize the GUI
	mGUIView = sf::View(mWindow.getDefaultView());
	if( !mGUI.init( this ) )
		return false;

	mGridView = sf::View(sf::FloatRect(0, 0, 1024, 768));

	// Ensure sizes view sizes
	onResize();

	return true;
}

bool Application::run()
{
	sf::Event event;

	while(mWindow.isOpen())
	{
		while(mWindow.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				mWindow.close();
			else if(event.type == sf::Event::Resized)
				onResize();
			/*else if(event.type == sf::Event::MouseWheelMoved)
				onMouseWheelMoved(event);*/

			mGUI.Desktop.HandleEvent(event);
		}

		mGUI.Desktop.Update(mClock.restart().asSeconds());
		//onInput();

		mWindow.clear();

		mWindow.setView(mGridView);
		//mWindow.draw(mGrid.getDrawable());
		mWindow.setView(mGUIView);

		mGUI.SFGUI.Display(mWindow);

		mWindow.display();
	}
	return true;
}

void Application::onClickPut()
{
	mGUI.BtnRemove->SetActive(false);
}

void Application::onClickRemove()
{
	mGUI.BtnPut->SetActive(false);
}

void Application::onClickExit()
{
	mWindow.close();
}

void Application::onResize()
{
	sf::Vector2f size = static_cast<sf::Vector2f>(mWindow.getSize());

	// Minimum size
	if(size.x < 800)
		size.x = 800;
	if(size.y < 600)
		size.y = 600;

	// Apply possible size changes
	mWindow.setSize(static_cast<sf::Vector2u>(size));

	// Reset grid view
	mGridView.setCenter(size/2.f);
	mGridView.setSize(size); // = sf::View(sf::FloatRect(mGridView.getCenter().x, mGridView.getCenter().y, mGridView.getSize().x+(mGridView.getSize().x - size.x), mGridView.getSize().y+(mGridView.getSize().y - size.y)));

	// Reset  GUI view
	mGUIView = sf::View(sf::FloatRect(0.f, 0.f, size.x, size.y));
	mWindow.setView(mGUIView);

	// Resize widgets

	// The sidebar should be 180px wide
	const float width = 180.f;

	mGUI.Desktop.UpdateViewRect(sf::FloatRect(0.f, 0.f, size.x, size.y));
	mGUI.WndMain->SetAllocation(sf::FloatRect(size.x-width, 0.f, width, size.y));
	mGUI.SideBar->SetAllocation(sf::FloatRect(0.f, 0.f, width, size.y));
}

/*:
	mGrid(mResources.getTexture(0), sf::Vector2u(20, 20)),
	mSelectionState(false),
{


	createWidgets();
	createSignals();
}

bool Application::run()
{

	
	return true;
}

void Application::onMouseWheelMoved(sf::Event aEvent)
{
	int delta = aEvent.mouseWheel.delta;
	sf::Vector2i pos(aEvent.mouseWheel.x, aEvent.mouseWheel.y);

	if(delta > 0)
		mGridView.zoom(1.2f);
	else if(delta < 0)
		mGridView.zoom(0.8f);

	//mGridView.r
}

void Application::onInput()
{
	sf::Vector2i absPos = sf::Mouse::getPosition(mWindow);


	/*
	// Mouse events
	
	// Positions
	sf::Vector2i iPos = sf::Mouse::getPosition(mWindow);
	sf::Vector2u uPos = sf::Vector2u(static_cast<unsigned int>(iPos.x)/48, static_cast<unsigned int>(iPos.y)/48);

	// Left button pressed
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		// Selection
		if(mSelectionState)
		{
			//mSelectionpush_back(uPos);
			//mGrid.select(uPos);
			mGrid.select(mSelectionRect, false);
			
			mSelectionRect.top = uPos.y;
			mSelectionRect.height = uPos.y;

			mGrid.select(mSelectionRect);
		}
		else
		{
			mSelectionState = true;
			mSelectionRect.left = uPos.x;
			mSelectionRect.width = uPos.x;
			mSelectionRect.top = uPos.y;
			mSelectionRect.height = uPos.y;

			mSelection.push_back(uPos);
		}

		// TODO option switch: rect vs pos
		//mGrid.select(uPos);
	}
	else
	{
		mSelectionState = false;
	}

	// Over the grid && grid position changed
	if((uPos.x != muLastPosition.x || uPos.y != muLastPosition.y) && iPos.x >= 0 && iPos.x < mWindow.getSize().x-180 && iPos.y >= 0 && iPos.y < mWindow.getSize().y)
	{
		// Highlight new grid position & unhighlight old grid position
		mGrid.highlight(muLastPosition, false);
		mGrid.highlight(uPos);

		// Remember last position
		muLastPosition = uPos;
		miLastPosition = iPos;
	}
	*/
	/*//mLastPosition

	else
	{
		mSelectionState = false;
	}

	// Over the grid && grid position changed
	if((uPos.x != muLastPosition.x || uPos.y != muLastPosition.y) && iPos.x >= 0 && iPos.x < mWindow.getSize().x-180 && iPos.y >= 0 && iPos.y < mWindow.getSize().y)
	{
		// Highlight new grid position & unhighlight old grid position
		mGrid.unhighlight(muLastPosition);
		mGrid.highlight(uPos);
		muLastPosition = uPos;
		miLastPosition = iPos;
	}*//*
}
*/