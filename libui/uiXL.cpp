#include "uiXL.h"
#include "_cc8.h"
#include "_ccu.h"
#include "uiManager.h"


uiXL* uiXL::create(const sRole* role)
{
	CREATE(uiXL, role);
}

bool uiXL::init(const sRole* role)
{
	if (!Node::init())
	{
		return false;
	}
	Menu* menu = Menu::create();
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	menu->addChild(_buttonLearn = cButton::create(cc8::cLearn));
	_buttonLearn->setPosition(_buttonLearn->getContentSize() / 2);
	_buttonLearn->onClick = [this]()
	{
		if (_role == nullptr)
		{
			return;
		}
		if (!_role->isControllabel() ||_select < 0 || ccu::getManager()->isFight() || !learn(_select))
		{
			ccu::getManager()->toast(cc8::cYouCant);
			return;
		}
		apply();
	};

	int inv = 36, w = 172, w2 = w + 64;
	float h = _buttonLearn->getContentSize().height + inv / 2;

	cLabel* label = cLabel::create(cc8::cExp + ": ");
	label->setPosition(Vec2(0, h) + label->getContentSize() / 2);
	this->addChild(label);

	this->addChild(_labelExp = cLabelEasy::create());
	_labelExp->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	_labelExp->setPosition(cc::getRight(label), label->getPositionY() + cLabelEasy::cOffy);


	this->addChild(label = cLabel::create(cc8::cLearn + ": "));
	label->setColor(sColor::YELLOW);
	label->setPosition(Vec2(w2, h) + label->getContentSize() / 2);

	this->addChild(_labelNeed = cLabelEasy::create());
	_labelNeed->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	_labelNeed->setPosition(cc::getRight(label), label->getPositionY() + cLabelEasy::cOffy);

	h += label->getContentSize().height + inv;

	std::vector<std::string> xl2s = { cc8::cRole, cc8::cBaby };
	std::vector<std::string> xl4s = { cc8::cPhysics + cc8::cXLA, cc8::cPhysics + cc8::cXLD, cc8::cMagic + cc8::cXLA, cc8::cMagic + cc8::cXLD };
	_labelLvs.resize(sXl::c4 * 2);
	cLabelEasy* labelEasy = nullptr;
	MenuItem* menuItem = nullptr;
	float x, y;
	int h2 = h;
	forr(xl2s, k)
	{
		h = h2;
		x = k * w2;
		forr(xl4s, i)
		{
			this->addChild(label = cLabel::create(xl4s.at(i) + "    "));
			label->setPosition(Vec2(x, h) + label->getContentSize() / 2);
			y = label->getPositionY();

			int tag = k * sXl::c4 + i;
			this->addChild(labelEasy = _labelLvs.at(tag) = cLabelEasy::create());
			labelEasy->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
			labelEasy->setPosition(cc::getRight(label), y);

			menu->addChild(menuItem = MenuItem::create());
			menuItem->setContentSize(Size(w + inv, label->getContentSize().height + inv));
			menuItem->setPosition(cc::getLeft(label) + menuItem->getContentSize().width / 2 - inv / 2, y);
			menuItem->setCallback([this, menuItem, tag](Ref*)
			{
				_select = tag;
				_sprite->setVisible(true);
				_sprite->setPosition(menuItem->getPosition());
				loadLabel(getlv(_select));
			});

			h += label->getContentSize().height + inv;
		}
		this->addChild(label = cLabel::create((k == 0 ? cc8::cRole : cc8::cBaby) + cc8::cXL + ":"));
		label->setColor(sColor::YELLOW);
		label->setPosition(Vec2(x, h) + label->getContentSize() / 2);
		h += label->getContentSize().height;
	}
	this->addChild(_sprite = cSprite9::create(ccu::uItemSelect));
	_sprite->setContentSize(menuItem->getContentSize());
	_sprite->setVisible(false);

	this->setContentSize(Size(w + w2, h));
	_buttonLearn->setPositionX(_contentSize.width / 2);

	load(role);
	return true;
}

void uiXL::load(const sRole* role)
{
	_role = role;
	_select = cc::_1;
	_isLearned = false;
	_sprite->setVisible(false);
	if (role == nullptr)
	{
		return;
	}
	_xlOri = _xl = role->xl;
	_xlbbOri = _xlbb = role->xlbb;
	_moneyOri = _money = role->exp;
	_maxlv = sXl::getLv(role->lv);

	forv(_labelLvs, k)
	{
		loadLabel(k, getlv(k));
	}
	_labelExp->setString(cc::toString(_money));
}

bool uiXL::learn(int select)
{
	if (select < 0)
	{
		return false;
	}
	int& xlv = getlv(select);
	if (xlv >= _maxlv)
	{
		return false;
	}
	int need = sXl::getExp(xlv + 1) * sXl::c2000;
	if (_money < need)
	{
		return false;
	}
	++xlv;
	_money -= need;
	_isLearned = true;
	loadLabel(select, xlv);
	_labelExp->setString(cc::toString(_money));
	return true;
}

void uiXL::loadLabel(int select, int xlv)
{
	_labelLvs.at(select)->setString(cc::toString(xlv) + "/" + cc::toString(_maxlv));
	loadLabel(xlv);
}

void uiXL::loadLabel(int xlv)
{
	_labelNeed->setString(xlv == sXl::c25 ? "------" : cc::toString(sXl::getExp(xlv + 1) * sXl::c2000));
}

void uiXL::apply()
{
// 	if (_role == nullptr || !_isLearned)
// 	{
// 		return;
// 	}
// 
// 	if (ccu::getManager()->isFight())
// 	{
// 		ccu::getManager()->toast(cc8::cYouCant);
// 		return;
// 	}
	if (onXL == nullptr)
	{
		return;
	}
	if (!onXL(_role, _xl - _xlOri, _xlbb - _xlbbOri, _moneyOri - _money))
	{
		return;
	}
	_xlOri = _xl;
	_xlbbOri = _xlbb;
	_moneyOri = _money;
	_isLearned = false;
}

int& uiXL::getlv(int select)
{
	return select >= sXl::c4 ? _xlbb.lvs.at(select - sXl::c4) : _xl.lvs.at(select);
}