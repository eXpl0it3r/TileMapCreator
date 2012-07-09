#include "GUI.hpp"

#include "Application.hpp"

GUI::GUI()
{
	
}

bool GUI::init(  Application *aApp )
{
	// Main window
	WndMain = sfg::Window::Create( sfg::Window::BACKGROUND );
	Desktop.Add( WndMain );
	if( !Desktop.LoadThemeFromFile( "data/gui/tmc.theme" ) )
		return false;
	
	// Load font
	if( !mFont.loadFromFile( "data/gui/BRIDGE.TTF" ) )
		return false;
	Desktop.GetEngine().GetResourceManager().AddFont( "Bridgnorth", mFont, false );
	
	// Load imgages and creat buttons
	if( !mImgPut.loadFromFile( "data/gui/put.png" ) )
		return false;
	mImgPtrPut = sfg::Image::Create();
	mImgPtrPut->SetImage( mImgPut );
	BtnPut = sfg::ToggleButton::Create();
	BtnPut->SetImage(mImgPtrPut);
	
	if( !mImgRemove.loadFromFile( "data/gui/remove.png" ) )
		return false;
	mImgPtrRemove = sfg::Image::Create();
	mImgPtrRemove->SetImage( mImgRemove );
	BtnRemove = sfg::ToggleButton::Create();
	BtnRemove->SetImage(mImgPtrRemove);
	
	if( !mImgAdd.loadFromFile( "data/gui/add.png" ) )
		return false;
	mImgPtrAdd = sfg::Image::Create();
	mImgPtrAdd->SetImage( mImgAdd );
	BtnAdd = sfg::Button::Create();
	BtnAdd->SetImage(mImgPtrAdd);
	
	if( !mImgSave.loadFromFile( "data/gui/save.png" ) )
		return false;
	mImgPtrSave = sfg::Image::Create();
	mImgPtrSave->SetImage( mImgSave );
	BtnSave = sfg::Button::Create();
	BtnSave->SetImage(mImgPtrSave);
	
	if( !mImgLoad.loadFromFile( "data/gui/load.png" ) )
		return false;
	mImgPtrLoad = sfg::Image::Create();
	mImgPtrLoad->SetImage( mImgLoad );
	BtnLoad = sfg::Button::Create();
	BtnLoad->SetImage(mImgPtrLoad);
	
	if( !mImgExit.loadFromFile( "data/gui/exit.png" ) )
		return false;
	mImgPtrExit = sfg::Image::Create();
	mImgPtrExit->SetImage( mImgExit );
	BtnExit = sfg::Button::Create();
	BtnExit->SetImage(mImgPtrExit);

	EditBar = sfg::Box::Create(sfg::Box::HORIZONTAL, 0.f);
	EditBar->Pack(BtnPut);
	EditBar->Pack(BtnRemove);
	EditBar->Pack(BtnAdd);

	FileBar = sfg::Box::Create(sfg::Box::HORIZONTAL, 0.f);
	FileBar->Pack(BtnSave);
	FileBar->Pack(BtnLoad);
	FileBar->Pack(BtnExit);

	// Static table
	TilesStaticTable = sfg::Table::Create();

	// Animated table
	TilesAnimatedTable = sfg::Table::Create();

	// Tile Notebook
	TilesNotebook = sfg::Notebook::Create();
	TilesNotebook->SetTabPosition(sfg::Notebook::TOP);
	TilesNotebook->AppendPage(TilesStaticTable, sfg::Label::Create("Tiles"));
	TilesNotebook->AppendPage(TilesAnimatedTable, sfg::Label::Create("Actions"));

	// Add boxes
	SideBar = sfg::Box::Create(sfg::Box::VERTICAL, 0.f);
	SideBar->Pack(EditBar, false, true);
	SideBar->Pack(TilesNotebook, true, true);
	SideBar->Pack(FileBar, false, true);
	WndMain->Add(SideBar);

	// Create signals
	BtnPut->GetSignal(sfg::Widget::OnLeftClick).Connect(&Application::onClickPut, aApp);
	BtnRemove->GetSignal(sfg::Widget::OnLeftClick).Connect(&Application::onClickRemove, aApp);
	BtnExit->GetSignal(sfg::Widget::OnLeftClick).Connect(&Application::onClickExit, aApp);

	return true;
}