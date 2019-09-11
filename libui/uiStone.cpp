#include "uiStone.h"
#include "_cc8.h"
#include "uiManager.h"

const int uiStone::c72 = 72;
uiStone* uiStone::create(const sRole* role)
{
	CREATE(uiStone, role);
}

bool uiStone::init(const sRole* role)
{
	if (!Node::init())
	{
		return false;
	}
	Menu* menu = Menu::create();
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	_sprites.resize(cEquip::c4);
	_labels.resize(cEquip::c4);
	std::vector<cButton*> buttons(cEquip::c4);
	cButton* button = nullptr;
	cLabel* label = nullptr;
	cSprite1* sprite = nullptr;
	int x;
	forv(buttons, k)
	{
		menu->addChild(button = buttons.at(k) = cButton::create2());
		button->setContentSize(Size(c72, c72));
		button->setPosition(c72 / 2, (_size_ - 1 - k) * (c72 + 8) + c72 / 2);

		this->addChild(label = cLabel::create(txtIcon::getName(cEquip::getType(k)) + "+"));
		label->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		label->setPosition(button->getPosition() + Vec2(button->getContentSize().width / 2 + 8, 0));
		x = cc::getRight(label);

		this->addChild(label = _labels.at(k) = cLabel::create());
		label->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		label->setPosition(x, button->getPositionY());

		button->addChild(sprite = _sprites.at(k) = cSprite1::create());
		sprite->setPosition(button->getContentSize() / 2);

		button->onClick = [this, k]()
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
			// _stone.switchStone(k);
			if (onStone != nullptr && onStone(_role, k))
			{
				loadStone(k, false);
			}
		};
	}
	this->addChild(label = cLabel::create(cc8::cEquipAdd + cc8::cColon, eFont::smaller));
	label->setPosition(Vec2(0, cc::getTop(buttons.front()) + 4) + label->getContentSize() / 2);
	this->setContentSize(Size(x, cc::getTop(label)));

	load(role);
	return true;
}

void uiStone::load(const sRole* role)
{
	_role = role;
	if (role == nullptr)
	{
		return;
	}
	for (int k = 0; k < cEquip::c4; ++k)
	{
		loadStone(k, false);
	}
}


void uiStone::loadStone(int k, bool check)
{
	if (check && _role == nullptr)
	{
		return;
	}
	const auto& stones = txtIcon::getIcons().at(eIcon::stone);
	eStone e = ((sRole*)_role)->stone.getStone(k);
	cEquip::sPropertys props;
	cEquip::setStone(e, props);
	_labels.at(k)->setString(cEquip::getName(props.front().pro));
	auto sprite = _sprites.at(k);
	sprite->load(stones.at((int)e).uid);
	sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	sprite->setScale(c72 / sprite->getContentSize().height);
}
