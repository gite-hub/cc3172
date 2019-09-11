#include "uiInput.h"
#include "_cc8.h"
#include "_ccu.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "../proj.win32/_utf.h"
#endif
bool uiInput::init()
{
	if (!uiPad::init(ccu::cPad))
	{
		return false;
	}
	setContentSize(Size(480, 0));
	setClose(false);

	int inv = 24;
	eFont e = eFont::normal;

	cButton* buttonCancel = cButton::create(cc8::cCancel, e);
	Size s = buttonCancel->getContentSize();
	buttonCancel->setPosition(Vec2(inv, inv) + s / 2);
	buttonCancel->onClick = [this]()
	{
		this->setVisible(false);
	};
	_menu->addChild(buttonCancel);
	float h = s.height + inv * 2;

	cButton* buttonConfirm = cButton::create(cc8::cConfirm, e);
	buttonConfirm->setPosition(_contentSize.width - inv - s.width / 2,  inv + s.height / 2);
	buttonConfirm->onClick = _buttonClose->onClick;
	_menu->addChild(buttonConfirm);
	
	Sprite9* sprite = Sprite9::create(ccu::cRect);
	sprite->setColor(ccu::cColorRect);
	int ih = 12;
	s.width = _contentSize.width - inv * 2;
	s.height = (int)e + ih * 2;
	sprite->setContentSize(s);
	sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	sprite->setPosition(inv, h + s.height / 2);
	this->addChild(sprite);
	h += s.height + inv / 2;

	this->addChild(_textField = ui::TextField::create());
	s.width -= ih;
	_textField->setTouchAreaEnabled(true);
	_textField->setTouchSize(s);
	_textField->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	_textField->setPosition(sprite->getPosition() + Vec2(ih, 0));
	_textField->setFontName(ccu::cFnt);
	_textField->setFontSize((int)e);
	_textField->setPlaceHolderColor(Color4B::BLACK);
	_textField->setTextColor(Color4B::BLACK);
	_textField->setCursorEnabled(true);
// 	_textField->setMaxLengthEnabled(true);
// 	_textField->setMaxLength(12);

	this->addChild(_labelDesc = cLabel::create(" ", e));
	s = _labelDesc->getContentSize();
	_labelDesc->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	_labelDesc->setPosition(inv, h);
	h += s.height + inv;
	setContentSize(Size(_contentSize.width, h));
	setPosition(cc::vsCenter().x, cc::vsY(0.95f) - _contentSize.height / 2);

	onClose = [this](bool)
	{
		if (onInput != nullptr)
		{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			onInput(cc::utf2gbk(_textField->getString()));
#else
			onInput(_textField->getString());
#endif
		}
	};
	return true;
}

void uiInput::setString(const std::string& text)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	_textField->setString(cc::gbk2utf(text));
#else
	_textField->setString(text);
#endif
}

void uiInput::setDesc(const std::string& desc)
{

	_labelDesc->setString(cc8::cPlaseInput + desc + cc8::cColon);
}


void uiInput::setPlaceHolder(const std::string& placeHolder)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	_textField->setPlaceHolder(cc::gbk2utf(placeHolder));
#else
	_textField->setPlaceHolder(placeHolder);
#endif
}
