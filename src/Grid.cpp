#include "Grid.hpp"

Grid::Grid(const std::shared_ptr<const sf::Texture> aGrid, const sf::Vector2u& aGridSize, const sf::Vector2u& aTileSize) :
	mGrid(*aGrid),
	mGridSize(aGridSize),
	mTileSize(aTileSize)
{
	// Grid tile must have the size of TileSize
	//if(static_cast<unsigned int>(mGrid.getGlobalBounds().width) != mGridSize.x || static_cast<unsigned int>(mGrid.getGlobalBounds().height) != mGridSize.y)
	//	mGrid.scale(mGridSize.x/mGrid.getGlobalBounds().width, mGridSize.y/mGrid.getGlobalBounds().height);

	// Create render texture & cells
	mGridTexture.create(mGridSize.x*mTileSize.x, mGridSize.y*mTileSize.y);
	mGridDrawable.setTexture(mGridTexture.getTexture());
	mCells.resize(mGridSize.y, std::vector<Cell>(mGridSize.x));

	// Blank will be rendered with no blend mode thus the color actually doesn't matter
	mBlank.setFillColor(sf::Color(0, 0, 0, 255));
	mBlank.setSize(sf::Vector2f(static_cast<float>(mTileSize.x), static_cast<float>(mTileSize.y)));

	mHighlightColor = sf::Color(0xDF, 0xE8, 0xF0, 0x90);
	mHighlighter.setFillColor(mHighlightColor);
	mHighlighter.setSize(sf::Vector2f(static_cast<float>(mTileSize.x), static_cast<float>(mTileSize.y)));
	
	mSelectColor = sf::Color(0xE5, 0xBF, 0xBF, 0x90);
	mSelector.setFillColor(mSelectColor);
	mSelector.setSize(sf::Vector2f(static_cast<float>(mTileSize.x), static_cast<float>(mTileSize.y)));
}

Grid::~Grid()
{

}

void Grid::add(const sf::Vector2u& aPosition, const std::shared_ptr<const sf::Texture> aTexture)
{
	if(bounds(aPosition))
	{
		// Add texture to the cell
		mCells.at(aPosition.y).at(aPosition.x).fill(aTexture);
	}
}

void Grid::remove(const sf::Vector2u& aPosition)
{
	if(bounds(aPosition))
	{
		// Remove the texture from the cell
		mCells.at(aPosition.y).at(aPosition.x).fill(nullptr);
	}
}

void Grid::highlight(const sf::Vector2u& aPosition, bool aState)
{
	if(bounds(aPosition))
	{
		mCells.at(aPosition.y).at(aPosition.x).highlight(aState);
	}
}

void Grid::select(const sf::Vector2u& aPosition, bool aState)
{
	if(bounds(aPosition))
	{
		mCells.at(aPosition.y).at(aPosition.x).select(aState);
	}
}

void Grid::select(const sf::Rect<unsigned int>& aRect, bool aState)
{
	unsigned int startH = 0;
	unsigned int startV = 0;
	unsigned int limitH = 0;
	unsigned int limitV = 0;

	if(aRect.left <= aRect.width)
	{
		startH = aRect.left;
		limitH = aRect.width;
	}
	else
	{
		startH = aRect.width;
		limitH = aRect.left;
	}

	if(aRect.top <= aRect.height)
	{
		startV = aRect.top;
		limitV = aRect.height;
	}
	else
	{
		startV = aRect.height;
		limitV = aRect.top;
	}

	for(unsigned int y=startV; y <= limitV; ++y)
		for(unsigned int x=startH; x <= limitH; ++x)
		{
			if(bounds(x, y))
			{
				mCells.at(y).at(x).select(aState);
			}
		}
}

void Grid::selectAll(bool aState)
{
	for(unsigned int y; y < mGridSize.y; ++y)
		for(unsigned int x; x < mGridSize.x; ++x)
		{
			mCells.at(y).at(x).select(aState);
		}
}

const sf::Vector2u& Grid::getGridSize() const
{
	return mGridSize;
}

void Grid::setGridSize(const sf::Vector2u& aSize)
{
	// TODO

	/*std::vector<std::vector<sf::Sprite*> > temp(aSize.y, std::vector<sf::Sprite*>(aSize.x, nullptr));

	for(unsigned int y=0; y < mTiles.size(); ++y)
	{
		for(unsigned int x=0; x < mTiles.at(y).size(); ++x)
		{
			if(y < aSize.y && x < aSize.x)
				temp.at(y).at(x) = mTiles.at(y).at(x);
			else
				delete mTiles.at(y).at(x);
		}
	}
	
	mTiles.swap(temp);
	mGridTexture.create(aSize.x*48, aSize.y*48);
	
	mChangedAll = true;*/
}
const sf::Vector2u& Grid::getTileSize() const
{
	return mTileSize;
}
void Grid::setTileSize(const sf::Vector2u& aSize)
{
	// TODO
}
const sf::Color& Grid::getHighlightColor() const
{
	return mHighlightColor;
}

void Grid::setHighlightColor(const sf::Color& aColor)
{
	mHighlightColor = aColor;
}
const sf::Color& Grid::getSelectColor() const
{
	return mSelectColor;
}
void Grid::setSelectColor(const sf::Color& aColor)
{
	mSelectColor = aColor;
}

const sf::Drawable& Grid::getDrawable()
{
	bool changed = false;

	for(unsigned int y=0; y < mGridSize.y; ++y)
		for(unsigned int x=0; x < mGridSize.x; ++x)
		{
			Cell& cell = mCells.at(y).at(x);

			// Cell has been changed
			if(cell.isChanged())
			{
				changed = true;

				// Draw Blank
				mBlank.setPosition(snap(x, y));
				mGridTexture.draw(mBlank, sf::RenderStates(sf::BlendNone));

				// Draw Tile
				if(cell.isFilled())
				{
					sf::Sprite sprite(*cell.draw());
					sprite.setPosition(snap(x, y));
					mGridTexture.draw(sprite);
				}
				else
				{
					cell.blank();
				}

				// Draw Selector
				if(cell.isSelected())
				{
					mSelector.setPosition(snap(x, y));
					mGridTexture.draw(mSelector);
				}

				// Draw Highlighter
				if(cell.isHighlighted())
				{
					mHighlighter.setPosition(snap(x, y));
					mGridTexture.draw(mHighlighter);
				}

				// Draw Grid
				mGrid.setPosition(snap(x, y));
				mGridTexture.draw(mGrid);
			}
		}

	// RerenderTexture needs only be updated if there was a change.
	if(changed)
	{
		mGridTexture.display();
	}

	// Return drawable
	return mGridDrawable;
}

const bool Grid::bounds(const sf::Vector2u& aPosition) const
{
	return bounds(aPosition.x, aPosition.y);
}

const bool Grid::bounds(const unsigned x, const unsigned y) const
{
	return (y >= 0 && y < mGridSize.y && x >= 0 && x < mGridSize.x);
}

const sf::Vector2f Grid::snap(const unsigned int x, const unsigned int y) const
{
	return sf::Vector2f(static_cast<float>(x*mTileSize.x), static_cast<float>(y*mTileSize.y));
}
