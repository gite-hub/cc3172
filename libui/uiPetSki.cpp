#include "uiPetSki.h"
#include "_cc8.h"
#include "_ccu.h"
#include "uiDesc.h"
#include "uiManager.h"

const int uiPetSki::c4 = 4;
// uiPetSki* uiPetSki::create(const eSkis& eskis)
// {
// 	CREATE(uiPetSki, eskis);
// }
// uiPetSki* uiPetSki::create()
// {
// 	CREATE(uiPetSki, {});
// }

uiDesc* uiPetSki::toDesc(eSki eski, Node* target)
{
	uiDesc* desc = uiDesc::create();
	sDescs descs;
	cSki::toDescs(eski, descs);
	desc->load(false, descs);
	desc->show(true, true);
	ccu::getManager()->addChild(desc);
//	target->getParent()->addChild(desc, target->getLocalZOrder());
	desc->correctPosition(target);
	return desc;
}

bool uiPetSki::init(/*const eSkis& eskis*/)
{
	if (!Node::init())
	{
		return false;
	}
	this->addChild(_menu = Menu::create());
	_menu->setPosition(Vec2::ZERO);
	this->addChild(_spriteSelect = cSprite9::create(ccu::uItemSelect));
	_spriteSelect->setVisible(false);
	// load(eskis);
	return true;
}

void uiPetSki::load(const eSkis& eskis)
{
	for (int k = eskis.size(), size = _menuItems.size(); k < size; ++k)
	{
		_menuItems.at(k)->setVisible(false);
		_sprites.at(k)->setVisible(false);
	}
	if (eskis.empty())
	{
		return;
	}
	cSprite1* sprite = nullptr;
	const auto& skis = txtIcon::getIcons().at(eIcon::ski);
	for (int k = 0, size = std::min(_menuItems.size(), eskis.size()); k < size; ++k)
	{
		_menuItems.at(k)->setVisible(true);
		sprite = _sprites.at(k);
		sprite->load(skis.at((int)eskis.at(k)).uid);
		sprite->setVisible(true);
	}
	for (int k = _menuItems.size(), size = eskis.size(); k < size; ++k)
	{
		eSki e = eskis.at(k);
		this->addChild(sprite = cSprite1::create(skis.at((int)e).uid));
		_sprites.push_back(sprite);

		MenuItem* menuItem = MenuItem::create();
		menuItem->setCallback([this, sprite, menuItem](Ref*)
		{
			_spriteSelect->setPosition(sprite->getPosition());
			_spriteSelect->setVisible(true);
			toDesc((eSki)menuItem->getTag(), sprite);
		});
		_menu->addChild(menuItem);
		_menuItems.push_back(menuItem);
		menuItem->setContentSize(sprite->getContentSize());
	}
	Size s = sprite->getContentSize();
	int inv = 4;
	for(int k = 0, size = eskis.size(), size2 = std::ceil(size * 1.0f / c4) * c4; k < size; ++k)
	{
		sprite = _sprites.at(k);
		sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		sprite->setPosition(Vec2((k % c4) * (s.width + inv), (size2 - 1 - k) / c4 * (s.height + inv)) + s / 2);
		_menuItems.at(k)->setTag((int)eskis.at(k));
		_menuItems.at(k)->setPosition(sprite->getPosition());
	}
	_spriteSelect->setContentSize(sprite->getContentSize() + Size(4, 4));
	_spriteSelect->updateOrderOfArrival();

	int c3 = std::ceil(eskis.size() * 1.0f / c4);
	this->setContentSize(Size(s.width * c4 + inv * (c4 - 1), s.height * c3 + inv * (c3 - 1)));
}

