#include "uiMod.h"
#include "_cc8.h"
#include "_ccu.h"
#include "uiModSelect.h"
#include "uiManager.h"

const int uiMod::c180 = 180;
// uiMod* uiMod::create(int wh, const sMod& mod, int lv, int tlv)
// {
// 	CREATE(uiMod, wh, mod, lv, tlv);
// }
// uiMod* uiMod::create(int wh, const sMod& mod, int lv)
// {
// 	CREATE(uiMod, wh, mod, lv, cc::_1);
// }
uiMod* uiMod::create(int wh)
{
	sMod mod;
	CREATE(uiMod, wh/*, mod, 0, cc::_1*/);
}
// uiMod* uiMod::create(const sMod& mod, int lv, int tlv)
// {
// 	CREATE(uiMod, c180, mod, lv, tlv);
// }
// 
// uiMod* uiMod::create(const sMod& mod, int lv)
// {
// 	CREATE(uiMod, c180, mod, lv, cc::_1);
// }
uiMod* uiMod::create()
{
	sMod mod;
	CREATE(uiMod, c180/*, mod, 0, cc::_1*/);
}



bool uiMod::init(int wh/*, const sMod& mod, int lv, int tlv*/)
{
	if (!Node::init())
	{
		return false;
	}

	Sprite9* sprite9 = Sprite9::create(ccu::cRect);
	sprite9->setColor(ccu::cColorRect);
	sprite9->setContentSize(Size(wh, wh));
	sprite9->setPosition(sprite9->getContentSize() / 2);
	this->addChild(sprite9);

	cButton* button9 = cButton::create2();
	button9->setContentSize(sprite9->getContentSize());
	button9->setPosition(sprite9->getPosition());
	button9->onClick = [this]()
	{
		if (!_mod)
		{
			return;
		}
		if (ccu::getManager()->isFight())
		{
			ccu::getManager()->toast(cc8::cYouCant);
			return;
		}
		sMod mod = _mod;
		cDyeRender::apply(mod.e, mod.jdx, mod.dyes);
		if (onMod != nullptr && onMod(mod))
		{
			_mod = mod;
			load(mod);
		}
	};
	button9->onKeep = [this](bool first)
	{
		if (!first || !_mod)
		{
			return;
		}
		if (ccu::getManager()->isFight())
		{
			ccu::getManager()->toast(cc8::cYouCant);
			return;
		}
		if (_isJJ)
		{
			sMod mod = _mod;
			mod.setJdx(1 - mod.jdx);
			if (onMod != nullptr && onMod(mod))
			{
				load(mod);
			}
		}
		else
		{
			auto modSelect = ccu::getManager()->getModSelect();
			modSelect->onSelect = [this](eMod e)
			{
				sMod mod = _mod;
				mod.setMod(e);
				mod.setJdx(_mod.jdx);
				if (onMod != nullptr && onMod(mod))
				{
					load(mod);
				}
			};
			modSelect->show();
		}
	};
	cMenu* menuOnce = cMenu::create(button9, nullptr);
	menuOnce->scheduleUpdate();
	this->addChild(menuOnce);

	this->addChild(_labelLv = cLabelEasy::create(cc8::cLV + "999", eFont::e100));
	_labelLv->setColor(sColor::BLACK);
	_labelLv->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	_labelLv->setPosition(4, cc::getTop(sprite9) - _labelLv->getContentSize().height / 2);

	cLabel* label = cLabel::create(cc8::cJoinFight + " ", eFont::smal);
	label->setColor(sColor::BLACK);
	label->setPosition(cc::getRight(sprite9) - 32 - label->getContentSize().width / 2, _labelLv->getPositionY() - cLabelEasy::cOffy);
	this->addChild(_labelTlv = label);
	_labelTlv->setVisible(false);

	this->addChild(_labelTakelv = cLabelEasy::create(eFont::e100));
	_labelTakelv->setColor(sColor::BLACK);
	_labelTakelv->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	_labelTakelv->setPosition(cc::getRight(label), _labelLv->getPositionY());

	this->addChild(_sprite = cSprite::create());
	_sprite->setShadow(true);
	_sprite->play();
	_sprite->setPosition(cc::getBM(sprite9) + Vec2(0, 24));

	this->setContentSize(Size(cc::getRT(sprite9)));
	// load(mod, lv, tlv);
	return true;
}

void uiMod::load(const sPet* pet)
{
	int tlv = cc::_1;
	if (pet == nullptr)
	{
		_mod = sMod();
		loadTakeLv(tlv);
		return;
	}
	if (pet->mod)
	{
		const auto& zz = txtZz::getZzs().at(pet->mod.e);
		tlv = zz.takelv;
	}
	load(pet->mod, pet->lv, tlv);
}


void uiMod::load(const sMod& mod, int lv, int tlv)
{
	load(mod);
	load(lv);
	loadTakeLv(tlv);
}


void uiMod::load(const sMod& mod)
{
	_mod = mod;
	if (!mod)
	{
		return;
	}
	mod.apply();
	_sprite->load(mod.get(eAct::fight, false));
}


void uiMod::load(int lv)
{
	_labelLv->setString(cc8::cLV + cc::toString(lv));
}

void uiMod::loadTakeLv(int tlv)
{
	if (tlv == cc::_1)
	{
		_labelTlv->setVisible(false);
		_labelTakelv->setVisible(false);
		return;
	}
//	_labelTlv->setVisible(true);
	_labelTakelv->setVisible(true);
	_labelTakelv->setString(cc::toString(tlv));
}

void uiMod::setJJ(bool isjj)
{
	_isJJ = isjj;
}
