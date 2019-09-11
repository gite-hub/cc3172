#include "cLabel.h"
#include "_ccu.h"
#include "base/ccFPSImages.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "../proj.win32/_utf.h"
#endif

static const sColor& setColor(const u64& _number)
{
	static sColor color;
	if (_number < 10000)
	{
		return color = sColor::BLACK;
	}
	if (_number < 100000)
	{
		return color = sColor::BLUE;
	}
	if (_number < 1000000)
	{
		return color = sColor(0, 0x88, 0);
	}
	if (_number < 10000000)
	{
		return color = sColor::RED;
	}
	return color = sColor::MAGENTA;
}


void cLabelString::setNumber(u64 u, bool moneyColor /*= false*/)
{
	_number = u;
	setString(cc::toString(u));
	if (moneyColor)
	{
		doMoneyColor(::setColor(u));
	}
}


void cLabelString::setString(const std::string& text)
{

}


void cLabelString::doMoneyColor(const sColor& color)
{

}


//////////////////////////////////////////////////////////////////////////
cLabelEasy::cLabelEasy()
{
}

cLabelEasy* cLabelEasy::create(const std::string& text, eFont e)
{
	CREATE(cLabelEasy, text, e);
}

cLabelEasy* cLabelEasy::create(const std::string& text)
{
	CREATE(cLabelEasy, text, eFont::e125);
}

cLabelEasy* cLabelEasy::create(eFont e)
{
	CREATE(cLabelEasy, "", e);
}

cLabelEasy* cLabelEasy::create()
{
	CREATE(cLabelEasy, "", eFont::e125);
}

static Texture2D* getTextureAtlas(const std::string& imageName, const std::string& key)
{
	Texture2D::setDefaultAlphaPixelFormat(Texture2D::PixelFormat::RGBA4444);
	Image* image = new (std::nothrow) Image();
	if (!image)
	{
		return nullptr;
	}
	bool isOk;
	if (imageName.empty())
	{
		isOk = image->initWithImageData(cc_fps_images_png, cc_fps_images_len());
	}
	else
	{
		isOk = image->initWithImageFile(imageName);
	}
	if (!isOk)
	{
		CC_SAFE_RELEASE(image);
		return nullptr;
	}
	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(image, key);
	CC_SAFE_RELEASE(image);
	if (texture == nullptr)
	{
		return nullptr;
	}
	texture->retain();
	Director::getInstance()->getTextureCache()->removeTextureForKey(key);
	FileUtils::getInstance()->purgeCachedEntries();
	return texture;
}


bool cLabelEasy::init(const std::string& text, eFont e)
{
	static std::map<eFont, Texture2D*> textures;
	if (textures.empty())
	{
		auto format = Texture2D::getDefaultAlphaPixelFormat();
		auto texture = ::getTextureAtlas("", "/cc_fps_images");
		if (texture != nullptr)
		{
			textures.insert(std::make_pair(eFont::e100, texture));
		}
		texture = ::getTextureAtlas(cPath::cFont + "label125.png", "/cc_fps_images_125");
		if (texture != nullptr)
		{
			textures.insert(std::make_pair(eFont::e125, texture));
		}
		texture = ::getTextureAtlas(cPath::cFont + "label150.png", "/cc_fps_images_150");
		if (texture != nullptr)
		{
			textures.insert(std::make_pair(eFont::e150, texture));
		}
		texture = ::getTextureAtlas(cPath::cFont + "label200.png", "/cc_fps_images_200");
		if (texture != nullptr)
		{
			textures.insert(std::make_pair(eFont::e200, texture));
		}
		Texture2D::setDefaultAlphaPixelFormat(format);
	}
	const auto& it = textures.find(e);
	if (it == textures.end())
	{
		return false;
	}
	if (it->second == nullptr)
	{
		return false;
	}
	int i = 4;
	switch (e)
	{
	case eFont::e125:
		i = 5;
		break;
	case eFont::e150:
		i = 6;
		break;
	case eFont::e200:
		i = 8;
		break;
	}
	setIgnoreContentScaleFactor(true);
	if (!LabelAtlas::initWithString(text, it->second, 3 * i, 8 * i, '.'))
	{
		return false;
	}
	setScale(1.0f / CC_CONTENT_SCALE_FACTOR());
	return true;
}

void cLabelEasy::setString(const std::string& text)
{
	LabelAtlas::setString(text);
}

void cLabelEasy::doMoneyColor(const sColor& color)
{
	LabelAtlas::setColor(color);
}





//////////////////////////////////////////////////////////////////////////
const int cLabelEasy::cOffy = 2;
cLabel* cLabel::create(const std::string& text, eFont e)
{
	if (ccu::cFnt == ccu::cArial)
	{
		auto ret = new (std::nothrow) cLabel();
		if (ret)
		{
			ret->setHorizontalAlignment(TextHAlignment::LEFT);
			ret->setVerticalAlignment(TextVAlignment::TOP);
			ret->setSystemFontName(ccu::cFnt);
			ret->setSystemFontSize((int)e);
			ret->setDimensions(0, 0);
			ret->setString(text);
			ret->autorelease();
			return ret;
		}
		return nullptr;
	}
	CREATE(cLabel, text, e);
}


cLabel* cLabel::create(const std::string& text)
{
	return create(text, eFont::normal);
}

cLabel* cLabel::create(eFont e)
{
	return create("", e);
}

cLabel* cLabel::create()
{
	return create("", eFont::normal);
}

bool cLabel::init(const std::string& text, eFont e)
{
	return Label::initWithTTF(text, cPath::cFont + ccu::cFnt, (int)e);
}

void cLabel::setString(const std::string& text)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	Label::setString(cc::gbk2utf(text));
#else
	Label::setString(text);
#endif
}


void cLabel::doMoneyColor(const sColor& color)
{
	Label::setColor(color);
}