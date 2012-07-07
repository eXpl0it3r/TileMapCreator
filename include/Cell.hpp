#ifndef CELL_HPP
#define CELL_HPP

#include <SFML/Graphics.hpp>

class Cell
{
public:
	Cell(const bool aHighlighted = false, const bool aSelected = false, const std::shared_ptr<const sf::Texture> aTexture = nullptr) :
		mHighlighted(aHighlighted),
		mSelected(aSelected),
		mChanged(true),
		mTexture(aTexture) { }
	void fill(const std::shared_ptr<const sf::Texture> aTexture) { mTexture = aTexture; mChanged = true; }
	void select(const bool aState) { mSelected = aState; mChanged = true; }
	void highlight(const bool aState) { mHighlighted = aState; mChanged = true; }
	const std::shared_ptr<const sf::Texture> draw() { mChanged = false; return mTexture; }
	void blank() { mChanged = false; }
	const bool isFilled() const { if(mTexture == nullptr) return false; return true; }
	const bool isSelected() const { return mSelected; }
	const bool isHighlighted() const { return mHighlighted; }
	const bool isChanged() const { return mChanged; }

private:
	bool mHighlighted;
	bool mSelected;
	bool mChanged;
	std::shared_ptr<const sf::Texture> mTexture;
};

#endif // CELL_HPP