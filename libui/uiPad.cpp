#include "uiPad.h"
#include "_ccu.h"


const Size uiPad::cSize(800, 512);

uiPad* uiPad::create(const std::string& image, bool swallowTouches /*= true*/)
{
	CREATE(uiPad, image, swallowTouches);
}

uiPad* uiPad::create(ulong uid, bool swallowTouches /*= true*/)
{
	CREATE(uiPad, uid, swallowTouches);
}

uiPad* uiPad::create(bool swallowTouches /*= true*/)
{
	CREATE(uiPad, ccu::cPad, swallowTouches);
}

bool uiPad::init(const std::string& image, bool swallowTouches)
{
	return init(image, cSp::c0, swallowTouches);
}

bool uiPad::init(const std::string& image)
{
	return init(image, cSp::c0, true);
}

bool uiPad::init(ulong uid, bool swallowTouches)
{
	return init("", uid, swallowTouches);
}

bool uiPad::init(ulong uid)
{
	return init("", uid, true);
}

bool uiPad::init(const std::string& image, ulong uid, bool swallowTouches)
{
	if (!Node::init())
	{
		return false;
	}
	this->addChild(_nodeAlpha = cNode::create(sColor::BLACK));
	_nodeAlpha->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_nodeAlpha->setContentSize(cc::vsSize() * 3);
	_nodeAlpha->setOpacity(0x88);
	

	if (true || swallowTouches)
	{
		MenuItem* menuItemScreen = MenuItem::create();
		// Ä¬ÈÏ¾ÓÖÐ
	//	menuItemScreen->setAnchorPoint(node->getAnchorPoint());
		menuItemScreen->setContentSize(_nodeAlpha->getContentSize());
		menuItemScreen->setCallback([this](Ref*)
		{
			if (onClickOut != nullptr)
			{
				onClickOut();
			}
			if (_isCloseOnOut)
			{
				_buttonClose->onClick();
			}
		});
		Menu* menuScreen = nullptr;
		if (swallowTouches)
		{
			menuScreen = Menu::create(menuItemScreen, nullptr); 
		}
		else
		{
			auto m = cMenu::create(menuItemScreen, nullptr);
			m->setSwallowsTouch(false);
			menuScreen = m;
		}
		menuScreen->setPosition(Vec2::ZERO);
		this->addChild(menuScreen);
	}	

	if (image.empty())
	{
		cSprite9* sprite = cSprite9::create(uid);
		_nodePad = sprite;
	}
	else
	{
		Sprite9* sprite = Sprite9::create(image);
		_nodePad = sprite;
	}
	this->addChild(_nodePad);
	Node::setContentSize(_nodePad->getContentSize());
	_nodePad->setAnchorPoint(Vec2::ZERO);


	this->addChild(_menu = Menu::create(_menuItemPad = MenuItem::create(), nullptr)/*, INT_MAX*/);
	_menuItemPad->setCallback([this](Ref*)
	{
		if (onClick != nullptr)
		{
			onClick();
		}
	});
	_menuItemPad->setLocalZOrder(INT_MAX);
	_menuItemPad->setAnchorPoint(Vec2::ZERO);
	_menu->setPosition(Vec2::ZERO);


	this->addChild(_spriteTitle = Sprite::createWithSpriteFrameName(ccu::cTitle));
	_spriteTitle->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	_spriteTitle->setVisible(false);

	this->addChild(_labelTitle = cLabel::create());
	_labelTitle->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);

	_menu->addChild(_buttonClose = cButton::create2(ccu::cClose));
	_buttonClose->onClick = CC_CALLBACK_0(uiPad::close, this);

	setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	setPosition(cc::vsCenter());

	setRemoveOnClose(false);
	setCloseOnOut(false);

	resetButtonTitlePosition();
	return true;
}

void uiPad::setTitle(const std::string& title)
{
	_labelTitle->setString(title);
	_spriteTitle->setVisible(!title.empty());
	resetButtonTitlePosition();
}


void uiPad::setClose(bool visible)
{
	_buttonClose->setVisible(visible);
}


void uiPad::setContentSize(const Size& contentSize)
{
	Node::setContentSize(contentSize);
	resetButtonTitlePosition();
}

void uiPad::resetButtonTitlePosition()
{
	_menuItemPad->setContentSize(_contentSize);
	_nodePad->setContentSize(_contentSize);
	_buttonClose->setPosition(_contentSize - Size(16, 16));
	_labelTitle->setPositionX(_contentSize.width / 2);
	_labelTitle->setPositionY(_contentSize.height - 2);
	_spriteTitle->setPosition(_contentSize.width / 2, cc::getBottom(_labelTitle) + 2);
}

void uiPad::setAlpha(bool alpha)
{
	_nodeAlpha->setOpacity(alpha ? 0x88 : 0);
}

void uiPad::show()
{
	setVisible(true);
	++_localZOrder;
	this->setLocalZOrder(_localZOrder - 1);
}

void uiPad::close()
{
	if (onClose != nullptr)
	{
		onClose(_isRemoveOnColse);
	}
	if (_isRemoveOnColse)
	{
		this->removeFromParent();
	}
	else
	{
		setVisible(false);
	}
}
