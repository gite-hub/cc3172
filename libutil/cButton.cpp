#include "cButton.h"
#include "_ccu.h"
#include "cSprite.h"
#include "cLabel.h"

void cLabelInner::setColor(const sColor& color)
{
	_label->setColor(_color = color);
}

void cLabelInner::setString(const std::string& text)
{
	_label->setString(text);
}

const std::string& cLabelInner::getString()
{
	return _label->getString();
}

void cLabelInner::setAilgn(eAilgn e, const Size& contentSize)
{
	switch (_eAilgn = e)
	{
	case eAilgn::Left:
		if (_label)
		{
			_label->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		}
		_vLabel.x = 5;
		_vLabel.y = contentSize.height / 2;
		break;
	case eAilgn::Mid:
		if (_label)
		{
			_label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		}
		_vLabel = contentSize / 2;
		break;
	case eAilgn::Right:
		if (_label)
		{
			_label->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
		}
		_vLabel.x = contentSize.width - 3;
		_vLabel.y = contentSize.height / 2;
		break;
	}
	if (_label)
	{
		_label->setPosition(_vLabel);
	}
}



//////////////////////////////////////////////////////////////////////////
cButton* cButton::create(const std::string& text, eFont e)
{
	CREATE(cButton, ccu::cButton64, cSp::c0, text, e);
}

cButton* cButton::create(const std::string& text)
{
	CREATE(cButton, ccu::cButton64, cSp::c0, text, eFont::normal);
}

cButton* cButton::create(eFont e)
{
	CREATE(cButton, ccu::cButton64, cSp::c0, "", e);
}

cButton* cButton::create()
{
	CREATE(cButton, ccu::cButton64, cSp::c0, "", eFont::normal);
}

cButton* cButton::create2(const std::string& image, const std::string& text, eFont e)
{
	CREATE(cButton, image, cSp::c0, text, e);
}


cButton* cButton::create2(const std::string& image, const std::string& text)
{
	CREATE(cButton, image, cSp::c0, text, eFont::normal);
}

cButton* cButton::create2(const std::string& image, eFont e)
{
	CREATE(cButton, image, cSp::c0, "", e);
}

cButton* cButton::create2(const std::string& image)
{
	CREATE(cButton, image, cSp::c0, "", eFont::normal);
}


cButton* cButton::create2(ulong uid, const std::string& text, eFont e)
{
	CREATE(cButton, "", uid, text, e);
}

cButton* cButton::create2(ulong uid, const std::string& text)
{
	CREATE(cButton, "", uid, text, eFont::normal);
}

cButton* cButton::create2(ulong uid)
{
	CREATE(cButton, "", uid, "", eFont::normal);
}

cButton* cButton::create2()
{
	CREATE(cButton, "", cSp::c0, "", eFont::normal);
}

cButton* cButton::create9(ulong uid, const std::string& text, eFont e)
{
	CREATE(cButton, "9", uid, text, e);
}

cButton* cButton::create9(ulong uid, const std::string& text)
{
	CREATE(cButton, "9", uid, text, eFont::normal);
}

cButton* cButton::create9(ulong uid, eFont e)
{
	CREATE(cButton, "9", uid, "", e);
}

cButton* cButton::create9(ulong uid)
{
	CREATE(cButton, "9", uid, "", eFont::normal);
}


bool cButton::init(const std::string& image, ulong uid, const std::string& text, eFont e)
{
	if (!MenuItem::init())
	{
		return false;
	}
	if (image.empty())
	{
		if (!MenuItemSprite::initWithNormalSprite(cSprite1::create(uid), nullptr, nullptr, nullptr))
		{
			return false;
		}
	}
	else if (image == "9")
	{
		if (!MenuItemSprite::initWithNormalSprite(cSprite9::create(uid), nullptr, nullptr, nullptr))
		{
			return false;
		}
	}
	else
	{
		if (!MenuItemSprite::initWithNormalSprite(Sprite9::create(image), nullptr, nullptr, nullptr))
		{
			return false;
		}
	}

	this->addChild(_label = cLabel::create(text, e));
	setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	set9(16, 16);
	setAilgn();

	MenuItemSprite::setCallback([this](Ref* r)
	{
		Node* node = dynamic_cast<Node*>(r);
		if (node != nullptr)
		{
			auto c1 = node->getComponent(cc::cComponentMenuItemLongPress1);
			auto c = node->getComponent(cc::cComponentMenuItemLongPress);
			if (c1 != nullptr || c != nullptr)
			{
				if (_isEasy)
				{
					if (onClick != nullptr)
					{
						onClick();
					}
				}
				else
				{
					if (onKeep != nullptr)
					{
						onKeep(c1 != nullptr);
					}
				}
				return;
			}
		}
		if (onClick != nullptr)
		{
			onClick();
		}
	});
	return true;
}


void cButton::setContentSize(const Size& contentSize)
{
	_normalImage->setContentSize(contentSize);
 	MenuItemSprite::setContentSize(contentSize);
	cLabelInner::setAilgn(_eAilgn, contentSize);
}


// void cButton::setPosition(float x, float y)
// {
// 	MenuItemSprite::setPosition(x, y);
// 	_v.x = x;
// 	_v.y = y;
// }
// 
// void cButton::setPosition(const Vec2& v)
// {
// 	setPosition(v.x, v.y);
// }

void cButton::selected()
{
	MenuItemSprite::selected();
	MenuItemSprite::setPosition(_position + Vec2(2, -2));
}

void cButton::unselected()
{
	MenuItemSprite::unselected();
	MenuItemSprite::setPosition(_position - Vec2(2, -2));
}

void cButton::setEnabled(bool bEnabled)
{
	MenuItemSprite::setEnabled(bEnabled);
	if (!bEnabled)
	{
		_normalImage->setColor(sColor::GRAY);
		_label->setColor(sColor::GRAY);
	}
}

void cButton::setAilgn(eAilgn e)
{
	cLabelInner::setAilgn(e, _contentSize);
}


void cButton::set9(int other, int top)
{
	_9 = other;
	_top9 = top;
	auto sprite9 = (dynamic_cast<Sprite9*>(_normalImage));
	if (sprite9 != nullptr)
	{
		sprite9->set9(other);
		sprite9->setInsetTop(top);
	}
	else
	{
		auto sprite9 = (dynamic_cast<cSprite9*>(_normalImage));
		if (sprite9 != nullptr)
		{
			sprite9->set9(other);
			sprite9->setInsetTop(top);
		}
	}
}
