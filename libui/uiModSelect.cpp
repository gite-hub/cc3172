#include "uiModSelect.h"
#include "_cc8.h"
#include "_ccu.h"


bool uiModSelect::init()
{
	if (!uiPad::init(ccu::cPad))
	{
		return false;
	}
	_select = cc::_1;
// 	_mods.push_back(eMod::xiaomaotou);
// 	_mods.push_back(eMod::xiaoxianling);
// 	_mods.push_back(eMod::xiaomotou);
// 	_mods.push_back(eMod::xiaoyaya);
// 	_mods.push_back(eMod::xiaoxiannv);
// 	_mods.push_back(eMod::xiaojingling);
	_mods.push_back(eMod::jianxiake);
	_mods.push_back(eMod::hutouguai);

	cButton* button = cButton::create(cc8::cConfirm);
	button->onClick = [this]()
	{
		if (_select >= 0 && onSelect != nullptr)
		{
			onSelect(_mods.at(_select));
		}
	};
	Menu* menu = Menu::create(button, nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	int inv = 24;
	button->setPosition(Vec2(0, inv) + button->getContentSize() / 2);

	float h = cc::getTop(button) + inv;
	float iw = 120, ih = 135;
	int ix = 6;
	sMod m;
	MenuItem* menuItem = nullptr;
	forv(_mods, k)
	{
		int x = k;
		if (k == 6 || k == 7)
		{
			x += 2;
		}
		menu->addChild(menuItem = MenuItem::create());
		menuItem->setContentSize(Size(iw, ih));
		menuItem->setPosition(Vec2(inv, h) + Vec2((x % ix) * iw, ((ix * 2 - 1 - k) / ix) * (ih + inv)));
		menuItem->setCallback([this, menuItem, k](Ref*)
		{
			_select = k;
			_spriteSelect->setVisible(true);
			_spriteSelect->setPosition(menuItem->getPosition());
		});

		m.setMod(_mods.at(k));
		m.apply();
		cSprite* sprite = cSprite::create(m.get(eAct::stand, false));
		sprite->setShadow(true);
		auto info = sprite->getInfo();
		sprite->setPosition(menuItem->getPosition() + Vec2(iw / 2, 32)/* + Vec2(info->kx, info->height  -info->ky)*/);
		this->addChild(sprite);
		sprite->play();

		menuItem->setPosition(menuItem->getPosition() + menuItem->getContentSize() / 2);
		if (k == ix - 1)
		{
			this->setContentSize(Size(cc::getRT(menuItem)) + Size(inv, inv + 48));
		}
	}
	this->setTitle(cc8::cMod);

	this->addChild(_spriteSelect = cSprite9::create(ccu::uItemSelect));
	_spriteSelect->setContentSize(menuItem->getContentSize());
	_spriteSelect->setVisible(false);

	button->setPositionX(_contentSize.width / 2);

	return true;
}
