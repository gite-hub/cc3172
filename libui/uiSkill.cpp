#include "uiSkill.h"
#include "_cc8.h"
#include "_ccu.h"
#include "uiManager.h"

const int uiSkill::c72 = 72;

const Size uiSkill::cSizeSelect(14, 14);

uiSkill* uiSkill::create(const sRole* role)
{
	CREATE(uiSkill, role);
}

bool uiSkill::init(const sRole* role)
{

	if (!Node::init())
	{
		return false;
	}

	Menu* menu = _menu = Menu::create();
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	_sprites.resize(ccp::main7);
	_labels.resize(_sprites.size());
	_labelShadows.resize(_sprites.size());
	_descs.resize(_sprites.size());
	std::vector<MenuItem*> menuItems(ccp::main7);
	forv (_sprites, k)
	{
		this->addChild(_sprites.at(k) = cSprite1::create());
		this->addChild(_labelShadows.at(k) = cLabelEasy::create(eFont::e100));
		this->addChild(_labels.at(k) = cLabelEasy::create(eFont::e100));
		menu->addChild(menuItems.at(k) = MenuItem::create());
		menuItems.at(k)->setCallback([this, k](Ref*)
		{
			_select = k;
			_spriteSelect->setVisible(true);
			_spriteSelect->setPosition(_sprites.at(k)->getPosition());
			_textDesc->load(false, _descs.at(k));
			_textDesc->show(true, false);
			forv(_labels, i)
			{
				_labels.at(i)->setColor(sColor::WHITE);
			}
			_labels.at(k)->setColor(sColor::GREEN);

			loadLabel(_skilvs.at(k) + 1);
		});
	}
	int c56 = c72, c24 = 32;
	int ix = c56 + c24;
	int iy = c56 + c24 + c56 / 6;
	_sprites[6]->setPosition(ix * 1, iy * 0);
	_sprites[0]->setPosition(ix * 1, iy * 1);
	_sprites[1]->setPosition(ix * 1, iy * 2);

	_sprites[2]->setPosition(ix * 0, iy * 3 / 2);
	_sprites[4]->setPosition(ix * 0, iy * 1 / 2);

	_sprites[3]->setPosition(ix * 2, iy * 3 / 2);
	_sprites[5]->setPosition(ix * 2, iy * 1 / 2);

	setContentSize(Size(ix * 3 - c24, iy * 3));

	this->addChild(_spriteSelect = cSprite9::create(ccu::uItemSelect));
	_spriteSelect->setContentSize(Size(c56, c56) + cSizeSelect);
	_spriteSelect->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_spriteSelect->setVisible(false);


	cButton* buttonLearn = cButton::create(cc8::cLearn);
	buttonLearn->setPosition(Vec2(_contentSize.width + ix / 2, 0) + buttonLearn->getContentSize() / 2);
	buttonLearn->onClick = [this]()
	{
		if (_role == nullptr)
		{
			return;
		}
		if (!_role->isControllabel() || ccu::getManager()->isFight())
		{
			ccu::getManager()->toast(cc8::cYouCant);
			return;
		}
		if (learn(_select, 1))
		{
			apply();
		}
	};
	menu->addChild(buttonLearn);

	
// 	cButton* buttonLearn10 = cButton::create(cc8::cLearn10);
// 	buttonLearn10->setPosition(buttonLearn->getPositionX() + ix, buttonLearn->getPositionY());
// 	buttonLearn10->onClick = [this]()
// 	{
// 	};
//	menu->addChild(buttonLearn10);

	this->addChild(_labelExp = cLabelEasy::create());
	this->addChild(_labelMoney = cLabelEasy::create());
	this->addChild(_labelNeedExp = cLabelEasy::create());
	this->addChild(_labelNeedMoney = cLabelEasy::create());

	std::vector<cLabelEasy*> labels =
	{
		_labelExp,
		_labelNeedExp,
		_labelMoney,
		_labelNeedMoney,
	};
	std::vector<std::string> names = { cc8::cExp, cc8::cLearn, cc8::cMoney, cc8::cLearn };

	Size s = Size::ZERO;
	iy = 8;
	float h = buttonLearn->getContentSize().height + iy;
	float x = _contentSize.width + c24;
	forv(names, k)
	{
		cLabel* label = cLabel::create(names.at(k) + ": ");
		this->addChild(label);
		if (s.equals(Size::ZERO))
		{
			s = label->getContentSize();
		}
		label->setPosition(Vec2((k % 2) * 192 + x, h + ((_size_ - 1 - k) / 2) * (s.height + iy)) + s / 2);
		labels.at(k)->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		labels.at(k)->setPosition(label->getPosition() + Vec2(s.width / 2, cLabelEasy::cOffy));
	}
	h += (s.height + iy) * 2;

	float w = 640;
	this->addChild(_textDesc = uiDesc::create(w - _contentSize.width - c24));
//	_textDesc->setVerticalSpace(8);
	_textDesc->setRemoveOnClose(false);
	_textDesc->setCloseOnOut(false);
	_textDesc->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	_textDesc->setPosition(x, 400);

	float hSprite = cSprite1::create(txtIcon::getIcons().at(eIcon::ski).at((int)eSki::eSpecial0).uid)->getContentSize().height;
	this->addChild(_spriteSpecialSelect = cSprite9::create(ccu::uItemSelect));
	_spriteSpecialSelect->setContentSize(Size(hSprite, hSprite) + cSizeSelect);
	_spriteSpecialSelect->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_spriteSpecialSelect->setVisible(false);

	cLabel* labelSpecial = cLabel::create(cc8::cEquipSpecial + cc8::cColon, eFont::smaller);
	labelSpecial->setPosition(Vec2(0, hSprite + iy) + labelSpecial->getContentSize() / 2);
	this->addChild(labelSpecial);

	hSprite = c24 + cc::getTop(labelSpecial) + iy; // _textDesc->getPositionY() / 2 - _contentSize.height / 2
	forv(_sprites, k)
	{
		auto sprite = _sprites.at(k);
		sprite->setPosition(sprite->getPosition() + Vec2(c56 / 2, hSprite));
		menuItems.at(k)->setPosition(sprite->getPosition());
		menuItems.at(k)->setContentSize(Size(c56, c56));
		cLabelEasy* label = _labels.at(k);
		label->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		label->setPosition(cc::getLB(menuItems.at(k)));

		cLabelEasy* labelShadow = _labelShadows.at(k);
		labelShadow->setColor(sColor::BLACK);
		labelShadow->setAnchorPoint(label->getAnchorPoint());
		labelShadow->setPosition(label->getPosition() + Vec2(2, -2));
	}

	this->setContentSize(Size(w, _textDesc->getPositionY()));
	buttonLearn->setPositionX(x + 160);
	load(role);
	return true;
}

void uiSkill::load(const sRole* role)
{
	_role = role;
	_isLearned = false;
	_spriteSelect->setVisible(false);
	_select = cc::_1;
	if (role == nullptr)
	{
		return;
	}
	_expOri = _exp = role->exp;
	_moneyOri = _money = role->money;
	_skiOri = _skilvs = role->skilvs;

	_lv = role->lv;
	forv(_skiOri, k)
	{
		loadLabel(k, _skiOri.at(k));
	}

	const auto& icons = txtIcon::getIcons().at(eIcon::ski);
	_sprites.at(0)->load(ccu::uStrong);
	int e = (int)txtSki::get0(role->menpai);
	int r = (int)txtSki::getEnd(role->menpai);
	const auto& skis = txtSki::getSkis();

	std::vector<int> eskis(ccp::main7, (int)eSki::eNone);
	for (int k = 0; k < ccp::main7; ++k)
	{
		auto sprite = _sprites.at(k);
		if (role->menpai == eMenpai::eNone || k == 0 || (e + k - 1) > r)
		{
			sprite->load(ccu::uStrong);
			_descs.at(k).clear();
			_descs.at(k).uhead = ccu::uStrong;
		}
		else
		{
			eskis.at(k) = e + k - 1;
			sprite->load(icons.at(eskis.at(k)).uid);
		}
	}
	for (auto sprite : _sprites)
	{
		sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		sprite->setScale(c72 * 1.0f / sprite->getContentSize().width);
	}

	forv(_descs, k)
	{
		sDescs& descs = _descs.at(k);
		r = eskis.at(k);
		if (r == (int)eSki::eNone)
		{
			descs.name = cc8::cStrong;
		}
		else
		{
			cSki::toDescs((eSki)r, descs);
		}
		descs.push(cc8::cLearn + cc8::cColon + cc8::cImprove + cEquip::getName((cEquip::eProPerty)k), s888::GREEN);
	}

	// ÌØ¼¼
	sPropertys pros;
	ccp::apply(pros, _role);
	for (int k = pros.specials.size(), size = _menuItemSpecials.size(); k < size; ++k)
	{
		_menuItemSpecials.at(k)->setVisible(false);
		_spriteSpecials.at(k)->setVisible(false);
	}
	if (pros.specials.empty())
	{
		return;
	}
	cSprite1* sprite = nullptr;
	for (int k = 0, size = std::min(_menuItemSpecials.size(), pros.specials.size()); k < size; ++k)
	{
		_menuItemSpecials.at(k)->setVisible(true);
		sprite = _spriteSpecials.at(k);
		sprite->load(icons.at((int)pros.specials.at(k)).uid);
		sprite->setVisible(true);
		cSki::toDescs(pros.specials.at(k), _descSpecials.at(k));
	}
	for (int k = _menuItemSpecials.size(), size = pros.specials.size(); k < size; ++k)
	{
		eSki e = pros.specials.at(k);
		this->addChild(sprite = cSprite1::create(icons.at((int)e).uid));
		_spriteSpecials.push_back(sprite);

		MenuItem* menuItem = MenuItem::create();
		menuItem->setCallback([this, sprite, k](Ref*)
		{
			_spriteSpecialSelect->setVisible(true);
			_spriteSpecialSelect->setPosition(_spriteSpecials.at(k)->getPosition());
			_textDesc->load(false, _descSpecials.at(k));
			_textDesc->show(true, false);
		});
		_menu->addChild(menuItem);
		_menuItemSpecials.push_back(menuItem);
		menuItem->setContentSize(sprite->getContentSize());

		sDescs desc;
		cSki::toDescs(pros.specials.at(k), desc);
		_descSpecials.push_back(desc);
	}
	Size s = sprite->getContentSize();
	forv(_menuItemSpecials, k)
	{
		sprite = _spriteSpecials.at(k);
		sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		sprite->setPosition(Vec2(k * (s.width + 16), 0) + s / 2);
		_menuItemSpecials.at(k)->setPosition(sprite->getPosition());
	}
}


bool uiSkill::learn(int index, int ilv)
{
	auto ui = ccu::getManager();
	if (index < 0 || _skilvs[index] >= _lv + cSki::cGap)
	{
		ui->toast(cc8::cYouCant);
		return false;
	}
	int skilv = _skilvs[index];
	u64 exp = 0, money = 0;
	int k = 0;
	for (; k < ilv && skilv + k < _lv + cSki::cGap; ++k)
	{
		exp += cSki::getExp(skilv + k + 1);
		money += cSki::getMoney(skilv + k + 1);
	}
	if (_exp < exp || _money < money)
	{
		ui->toast(cc8::cYouCant);
		return false;

	}
	_isLearned = true;
	_exp -= exp;
	_money -= money;
	_skilvs[index] = skilv += std::max(0, k);
	loadLabel(skilv + 1);
	loadLabel(index, skilv);
	return true;
}


void uiSkill::loadLabel(int skilv)
{
	_labelNeedExp->setNumber(cSki::getExp(skilv));
	_labelNeedMoney->setNumber(cSki::getMoney(skilv), true);
}

void uiSkill::loadLabel(int index, int skilv)
{
	_labels[index]->setNumber(skilv);
	_labelShadows[index]->setNumber(_labels[index]->getNumber());
	_labelExp->setNumber(_exp);
	_labelMoney->setNumber(_money, true);
}

void uiSkill::apply()
{
// 	if (_role == nullptr || !_isLearned)
// 	{
// 		return;
// 	}
// 	if (ccu::getManager()->isFight())
// 	{
// 		ccu::getManager()->toast(cc8::cYouCant);
// 		return;
// 	}
	if (onLearn == nullptr)
	{
		return;
	}
	auto skilvs = _skilvs;
	forv(skilvs, k)
	{
		skilvs[k] -= _skiOri[k];
	}
	if (!onLearn(_role, skilvs, _expOri - _exp, _moneyOri - _money))
	{
		return;
	}
	_expOri = _exp;
	_moneyOri = _money;
	_skiOri = _skilvs;
	_isLearned = false;
}


