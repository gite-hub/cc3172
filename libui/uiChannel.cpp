#include "uiChannel.h"
#include "_ccu.h"

bool uiChannel::init(eFont eFnt)
{
	if (!Node::init())
	{
		return false;
	}
	_eFont = eFnt;
	Sprite9* sprite = Sprite9::create(ccu::cRect);
	sprite->setContentSize(Size(360, 64));
	sprite->setColor(sColor::BLACK);
	sprite->setOpacity(0x88);
	this->setContentSize(sprite->getContentSize());
	sprite->setPosition(_contentSize / 2);
	this->addChild(sprite);

	_v.x = _v.y = 4;
	_s = _contentSize - Size(_v * 2);
	return true;
}


void uiChannel::add(const std::string& name, const std::string& text)
{
	cText* t = cText::create(_eFont, _s.width);
	t->setString(name, text);
	float h = t->getContentSize().height + 2;
	for (auto text : _texts)
	{
		text->setPositionY(text->getPositionY() + h);
	}
	while (true)
	{
		if (_texts.empty())
		{
			break;
		}
		cText* text = _texts.front();
		if (text->getPositionY() + text->getContentSize().height < _contentSize.height)
		{
			break;
		}
		text->removeFromParent();
		_texts.pop_front();

	}
	t->setAnchorPoint(Vec2::ZERO);
	t->setPosition(_v);
	this->addChild(t);
	_texts.push_back(t);
}



//////////////////////////////////////////////////////////////////////////
bool uiChat::init(eFont eFnt)
{
	if (!uiPad::init(ccu::cPad, false))
	{
		return false;
	}
	_eFont = eFnt;
	setClose(false);
	setAlpha(false);

	setContentSize(Size(400, 520));
// 	cSprite9* sprite = cSprite9::create(ccu::uDesc);
// 	this->addChild(sprite);

	this->addChild(_scrollView = ui::ScrollView::create());
	int edge = 8;
	_scrollView->setContentSize(_contentSize - Size(edge, edge * 2 + 56));
	_scrollView->setPosition(Vec2(edge, edge + 56));
	_scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
	_scrollView->setBounceEnabled(true);

// 	sprite->setContentSize(Size(_scrollView->getContentSize().width, _scrollView->getContentSize().height + edge));
// 	sprite->setPosition(_scrollView->getPosition() - Vec2(edge, edge) / 2 + sprite->getContentSize() / 2);


	cButton* button = cButton::create2(ccu::cMessageFold);
	button->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	button->setPosition(Vec2(_contentSize.width - 4, _contentSize.height / 2));
	_menu->addChild(button);
	button->onClick = _buttonClose->onClick;
	return true;
}


void uiChat::add(const std::string& name, const std::string& text)
{
	float w = _scrollView->getContentSize().width;
	cText* t = cText::create(_eFont, w);
	t->setString(name, text);
	float h = t->getContentSize().height + 4;
	for (auto text : _scrollView->getChildren())
	{
		text->setPositionY(text->getPositionY() + h);
	}
	w = _scrollView->getInnerContainerPosition().y - h;
	_scrollView->setInnerContainerSize(Size(w, _h += h));
	t->setAnchorPoint(Vec2::ZERO);
	_scrollView->addChild(t);
	_scrollView->setInnerContainerPosition(Vec2(0, w));
}

void uiChat::show()
{
	uiPad::show();
	int h1 = _scrollView->getContentSize().height;
	int h2 = _scrollView->getInnerContainerSize().height;
	_scrollView->setInnerContainerPosition(Vec2(0, std::max(0, h1 - h2)));
}

