#include "Application.hpp"

Application::Application() :
	mGrid(mResources.getTexture(0), sf::Vector2u(20, 20)),
	mSelectionState(false),
	mWindow(sf::VideoMode(1024, 768, 32), "Tile Map Creator", sf::Style::Close | sf::Style::Resize | sf::Style::Titlebar),
	mGridView(sf::FloatRect(0, 0, 1024, 768)),
	mGUIView(mWindow.getDefaultView()),
	mDesktop()
{
	mWindow.resetGLStates();
	mWindow.setFramerateLimit(30);

	createWidgets();
	createSignals();
}

void Application::createWidgets()
{
	// Main window
	mWndMain = sfg::Window::Create(sfg::Window::BACKGROUND);
	mDesktop.Add(mWndMain);
	
	mDesktop.GetEngine().GetResourceManager().AddFont("Bridgnorth", *mResources.getFont(0), false);

	// Properties
	mDesktop.SetProperty("*", "FontName", "Bridgnorth");
	mDesktop.SetProperty("Window", "BackgroundColor", sf::Color(0x2D, 0x3D, 0x5B));
	mDesktop.SetProperty("Window", "BorderColor", sf::Color(0x35, 0x49, 0x6A));
	mDesktop.SetProperty("Window", "Padding", 0.f);
	mDesktop.SetProperty("Window", "Gap", 0.f);
	mDesktop.SetProperty("Window", "BorderWidth", 0.f);
	mDesktop.SetProperty("ToggleButton", "Padding", 0.f);
	mDesktop.SetProperty("Button", "Padding", 0.f);
	mDesktop.SetProperty("Label", "FontSize", 15.f);
	//mDesktop.SetProperty("Notebook", "Padding", 12.f);
	
	// Buttons
	mBtnPut = sfg::ToggleButton::Create();
	mBtnPut->SetImage(mResources.getImageGui(0));

	mBtnRemove = sfg::ToggleButton::Create();
	mBtnRemove->SetImage(mResources.getImageGui(1));

	mBtnAdd = sfg::Button::Create();
	mBtnAdd->SetImage(mResources.getImageGui(2));

	mBtnSave = sfg::Button::Create();
	mBtnSave->SetImage(mResources.getImageGui(3));

	mBtnLoad = sfg::Button::Create();
	mBtnLoad->SetImage(mResources.getImageGui(4));

	mBtnExit = sfg::Button::Create();
	mBtnExit->SetImage(mResources.getImageGui(5));

	mEditBar = sfg::Box::Create(sfg::Box::HORIZONTAL, 0.f);
	mEditBar->Pack(mBtnPut);
	mEditBar->Pack(mBtnRemove);
	mEditBar->Pack(mBtnAdd);

	mFileBar = sfg::Box::Create(sfg::Box::HORIZONTAL, 0.f);
	mFileBar->Pack(mBtnSave);
	mFileBar->Pack(mBtnLoad);
	mFileBar->Pack(mBtnExit);

	// Static table
	mTilesStaticTable = sfg::Table::Create();

	// Animated table
	mTilesAnimatedTable = sfg::Table::Create();

	// Notebook
	mTilesNotebook = sfg::Notebook::Create();
	mTilesNotebook->SetTabPosition(sfg::Notebook::TOP);
	mTilesNotebook->AppendPage(mTilesStaticTable, sfg::Label::Create("Tiles"));
	mTilesNotebook->AppendPage(mTilesAnimatedTable, sfg::Label::Create("Actions"));

	// Add boxes
	mSideBar = sfg::Box::Create(sfg::Box::VERTICAL, 0.f);
	mSideBar->Pack(mEditBar, false, true);
	mSideBar->Pack(mTilesNotebook, true, true);
	mSideBar->Pack(mFileBar, false, true);
	mWndMain->Add(mSideBar);
}

void Application::createSignals()
{
	mBtnPut->GetSignal(sfg::Widget::OnLeftClick).Connect(&Application::onClickPut, this);
	mBtnRemove->GetSignal(sfg::Widget::OnLeftClick).Connect(&Application::onClickRemove, this);
	mBtnExit->GetSignal(sfg::Widget::OnLeftClick).Connect(&Application::onClickExit, this);
}

bool Application::run()
{
	sf::Event event;

	onResize(); // Ensure sizes

	while(mWindow.isOpen())
	{
		while(mWindow.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				mWindow.close();
			else if(event.type == sf::Event::Resized)
				onResize();
			else if(event.type == sf::Event::MouseWheelMoved)
				onMouseWheelMoved(event);

			mDesktop.HandleEvent(event);
		}

		mDesktop.Update(mClock.restart().asSeconds());
		onInput();

		mWindow.clear();

		mWindow.setView(mGridView);
		mWindow.draw(mGrid.getDrawable());
		mWindow.setView(mGUIView);

		mSfgui.Display(mWindow);

		mWindow.display();
	}
	
	return true;
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

	mDesktop.UpdateViewRect(sf::FloatRect(0.f, 0.f, size.x, size.y));
	mWndMain->SetAllocation(sf::FloatRect(size.x-width, 0.f, width, size.y));
	mSideBar->SetAllocation(sf::FloatRect(0.f, 0.f, width, size.y));
}

void Application::onClickPut()
{
	mBtnRemove->SetActive(false);
}

void Application::onClickRemove()
{
	mBtnPut->SetActive(false);
}

void Application::onClickExit()
{
	mWindow.close();
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
	}*/
}
