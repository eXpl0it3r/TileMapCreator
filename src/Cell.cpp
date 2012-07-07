#include "Cell.hpp"

Cell::Cell(const bool aHighlighted, const bool aSelected, std::shared_ptr<sf::Texture> aTexture) :
	mHighlighted(aHighlighted),
	mSelected(aSelected),
	mTexture(aTexture)
{ }