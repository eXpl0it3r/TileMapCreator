#ifndef GRID_HPP
#define GRID_HPP

#include "Resources.hpp"

#include "Cell.hpp"

#include <vector>
#include <SFML/Graphics.hpp>

class Grid
{
public:
	Grid(const std::shared_ptr<const sf::Texture> aGrid, const sf::Vector2u& aGridSize, const sf::Vector2u& aTileSize = sf::Vector2u(48, 48));
	~Grid();

	/** Get a descriptive name for a key.
	* @param 
	* @return Name or empty if not defined.
	*/
	void add(const sf::Vector2u& aPosition, const std::shared_ptr<const sf::Texture> aTexture);
	void remove(const sf::Vector2u& aPosition);
	void highlight(const sf::Vector2u& aPosition, bool aState = true);
	void select(const sf::Vector2u& aPosition, bool aState = true);
	void select(const sf::Rect<unsigned int>& aRect, bool aState = true);
	void selectAll(bool aState = true);

	const sf::Vector2u& getGridSize() const;
	void setGridSize(const sf::Vector2u& aSize);
	const sf::Vector2u& getTileSize() const;
	void setTileSize(const sf::Vector2u& aSize);
	const sf::Color& getHighlightColor() const;
	void setHighlightColor(const sf::Color& aColor);
	const sf::Color& getSelectColor() const;
	void setSelectColor(const sf::Color& aColor);

	const sf::Drawable& getDrawable();

private:
	const bool bounds(const sf::Vector2u& aPos) const;
	const bool bounds(const unsigned x, const unsigned y) const;
	const sf::Vector2f snap(const unsigned int x, const unsigned int y) const;

	sf::RenderTexture mGridTexture;
	sf::Sprite mGridDrawable;
	sf::Sprite mGrid;
	sf::RectangleShape mHighlighter;
	sf::RectangleShape mSelector;
	sf::RectangleShape mBlank;
	sf::Color mHighlightColor;
	sf::Color mSelectColor;
	sf::Vector2u mGridSize;
	sf::Vector2u mTileSize;
	std::vector<std::vector<Cell>> mCells;
};

#endif // GRID_HPP