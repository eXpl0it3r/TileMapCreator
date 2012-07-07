#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <Thor/Resources.hpp>
#include <SFML/Graphics.hpp>	
#include <SFGUI/Image.hpp>

class Resources
{
public:
	Resources();

	// Add key
	const unsigned int addFontKey(const std::string& aPath);
	const unsigned int addImageKey(const std::string& aPath);
	const unsigned int addTextureKey(const std::string& aPath);

	// Remove resource
	void removeFont(const unsigned int aKey);
	void removeImage(const unsigned int aKey);
	void removeTexture(const unsigned int aKey);

	// Get resources
	const std::shared_ptr<sf::Font> getFont(const unsigned int aKey);
	const std::shared_ptr<sf::Image> getImage(const unsigned int aKey);
	const std::shared_ptr<sf::Texture> getTexture(const unsigned int aKey);

	// Get SFGUI
	const sfg::Image::Ptr getImageGui(const unsigned int aKey);

private:
	void loadResources();

	// Keys
	std::vector<thor::ResourceKey<sf::Font>> mFontKeys;
	std::vector<thor::ResourceKey<sf::Image>> mImageKeys;
	std::vector<thor::ResourceKey<sf::Texture>> mTextureKeys;

	// Resources
	std::map<unsigned int, std::shared_ptr<sf::Font>> mFont;
	std::map<unsigned int, std::shared_ptr<sf::Image>> mImage;
	std::map<unsigned int, std::shared_ptr<sf::Texture>> mTexture;

	std::map<unsigned int, sfg::Image::Ptr> mImageGui;

	// Managers
	thor::MultiResourceCache mCache;
};

#endif // RESOURCES_HPP