#include "Resources.hpp"

#include <sstream>
#include <fstream>
#include <iostream>

Resources::Resources()
{
	loadResources();
}

void Resources::loadResources()
{
	std::ifstream file;
	std::string filename = "";
	std::stringstream ss;
	char lineBuffer[256];

	// Image
	filename = "data/res/images";
	file.open(filename, std::ifstream::in);

	while(file.good())
	{
		//Reset
		ss.str("");
		ss.clear();

		// Read line
		file.getline(lineBuffer, 256);
		ss << lineBuffer;

		// Ignore empty lines
		if(ss.str().size() <= 0)
			continue;

		// Add image key
		mImageKeys.push_back(thor::Resources::fromFile<sf::Image>(ss.str()));
	}
	file.close();

	// Texture
	filename = "data/res/textures";
	file.open(filename, std::ifstream::in);

	while(file.good())
	{
		//Reset
		ss.str("");
		ss.clear();

		// Read line
		file.getline(lineBuffer, 256);
		ss << lineBuffer;
		
		// Ignore empty lines
		if(ss.str().size() <= 0)
			continue;
		
		// Add texture key
		mTextureKeys.push_back(thor::Resources::fromFile<sf::Texture>(ss.str()));
	}
	file.close();

	// Font
	filename = "data/res/fonts";
	file.open(filename, std::ifstream::in);

	while(file.good())
	{
		//Reset
		ss.str("");
		ss.clear();

		// Read line
		file.getline(lineBuffer, 256);
		ss << lineBuffer;

		// Ignore empty lines
		if(ss.str().size() <= 0)
			continue;
		
		// Add font key
		mFontKeys.push_back(thor::Resources::fromFile<sf::Font>(ss.str()));
	}
	file.close();
}

const unsigned int Resources::addFontKey(const std::string& aPath)
{
	mFontKeys.push_back(thor::Resources::fromFile<sf::Font>(aPath));
	return static_cast<unsigned int>(mFontKeys.size()-1);
}

const unsigned int Resources::addImageKey(const std::string& aPath)
{
	mImageKeys.push_back(thor::Resources::fromFile<sf::Image>(aPath));
	return static_cast<unsigned int>(mImageKeys.size()-1);
}

const unsigned int Resources::addTextureKey(const std::string& aPath)
{
	mTextureKeys.push_back(thor::Resources::fromFile<sf::Texture>(aPath));
	return static_cast<unsigned int>(mTextureKeys.size()-1);
}

void Resources::removeFont(const unsigned int aKey)
{
	if(mFont.find(aKey) != mFont.end())
		mFont.erase(aKey);
}

void Resources::removeImage(const unsigned int aKey)
{
	if(mImageGui.find(aKey) != mImageGui.end())
		mImageGui.erase(aKey);

	if(mImage.find(aKey) != mImage.end())
		mImage.erase(aKey);
}

void Resources::removeTexture(const unsigned int aKey)
{
	if(mTexture.find(aKey) != mTexture.end())
		mTexture.erase(aKey);
}

const std::shared_ptr<sf::Font> Resources::getFont(const unsigned int aKey)
{
	if(mFont.find(aKey) == mFont.end())
	{
		mFont.insert(std::pair<unsigned int, std::shared_ptr<sf::Font>>(aKey, mCache.acquire(mFontKeys.at(aKey))));
	}
	return mFont.at(aKey);
}

const std::shared_ptr<sf::Image> Resources::getImage(const unsigned int aKey)
{
	if(mImage.find(aKey) == mImage.end())
	{
		mImage.insert(std::pair<unsigned int, std::shared_ptr<sf::Image>>(aKey, mCache.acquire(mImageKeys.at(aKey))));
	}
	return mImage.at(aKey);
}

const std::shared_ptr<sf::Texture> Resources::getTexture(const unsigned int aKey)
{
	if(mTexture.find(aKey) == mTexture.end())
	{
		mTexture.insert(std::pair<unsigned int, std::shared_ptr<sf::Texture>>(aKey, mCache.acquire(mTextureKeys.at(aKey))));
	}
	return mTexture.at(aKey);
}

const sfg::Image::Ptr Resources::getImageGui(const unsigned int aKey)
{
	if(mImageGui.find(aKey) == mImageGui.end())
	{
		if(mImage.find(aKey) == mImage.end())
		{
			mImage.insert(std::pair<unsigned int, std::shared_ptr<sf::Image>>(aKey, mCache.acquire(mImageKeys.at(aKey))));
		}
		mImageGui.insert(std::pair<unsigned int, sfg::Image::Ptr>(aKey, sfg::Image::Create()));
		mImageGui.at(aKey)->SetImage(*mImage.at(aKey));
	}
	return mImageGui.at(aKey);
}