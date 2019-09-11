#include "uiPetAttr.h"
#include "_cc8.h"
#include "_ccu.h"
#include "uiPad.h"
#include "uiAddpoint.h"
#include "uiManager.h"

uiPetAttr* uiPetAttr::create(sPet* pet)
{
	CREATE(uiPetAttr, pet);
}

bool uiPetAttr::init(sPet* pet)
{
	if (!Node::init())
	{
		return false;
	}
	this->addChild(_node1 = Node::create());
	this->addChild(_node2 = Node::create());
	Menu* menu1 = Menu::create();
	menu1->setPosition(Vec2::ZERO);
	_node1->addChild(menu1);

	Menu* menu2 = Menu::create();
	menu2->setPosition(Vec2::ZERO);
	_node2->addChild(menu2);


	_node1->addChild(_attrExp = uiAttr::create(16, cc8::cExp));

	_node1->addChild(_attr = uiAttribute::create());
	_attr->setPosition(0, cc::getTop(_attrExp) + uiAttr::cInterval/*cButton::create2(ccu::cBtn48)->getContentSize().height - uiAttr::create(cc8::cPointBody)->getContentSize().height*/);

	_node1->addChild(_point = uiPoint::create());
	_point->setPosition(_attr->getPositionX() + _attr->getContentSize().width + 48, _attr->getPositionY() + _attr->getContentSize().height - _point->getContentSize().height);

	_node1->addChild(_attrHp = uiAttr::create(10, cc8::cPropertyHp));
	_node1->addChild(_attrMp = uiAttr::create(10, cc8::cPropertyMp));
	std::vector<uiAttr*> attrs = { _attrHp,_attrMp };
	uiAttr* a = nullptr;
	float h = _attr->getPositionY() + _attr->getContentSize().height + uiAttr::cInterval;
	forr(attrs, k)
	{
		a = attrs.at(k);
		a->setPosition(_attr->getPositionX() + _attr->getSpriteX() - a->getSpriteX(), h);
		h += a->getContentSize().height + uiAttr::cInterval;
	}

	
	_node2->addChild(_zz = uiZz::create(true, nullptr));
	_zz->setPosition(_attr->getPositionX() /*-_zz->getContentSize().width - 54*/, cc::getTop(_attrHp) - _zz->getContentSize().height);

	_node2->addChild(_ski = uiPetSki::create());

	setContentSize(Size(cc::getRight(_point), cc::getTop(_attrHp)));

	MenuItem* menuItem = MenuItem::create();
	menu1->addChild(menuItem);
	menuItem->setContentSize(_attr->getContentSize() + Size(0, (attrs.front()->getContentSize().height + uiAttr::cInterval) * attrs.size()));
	menuItem->setPosition(_attr->getPosition());
	menuItem->setAnchorPoint(_attr->getAnchorPoint());
	menuItem->setCallback([this, menuItem](Ref*)
	{
		_node1->setVisible(false);
		_node2->setVisible(true);
	});


	menu1->addChild(menuItem = MenuItem::create());
	menuItem->setContentSize(_point->getContentSize());
	menuItem->setPosition(_point->getPosition());
	menuItem->setAnchorPoint(_point->getAnchorPoint());
	menuItem->setCallback([this](Ref*)
	{
		if (_pet == nullptr)
		{
			return;
		}
		if (ccu::getManager()->isFight())
		{
			ccu::getManager()->toast(cc8::cYouCant);
			return;
		}
		auto addpointer = ccu::getManager()->getAddpointer();
		addpointer->setTitle(_pet->name);
		addpointer->onPoint = [this](const sProperty* pro, const sPoint& p)
		{
			if (_pet != pro)
			{
				return false;
			}
			if (onPoint == nullptr || !onPoint(_pet, p))
			{
				return false;
			}
			load(_pet);
			return true;
		};
		addpointer->load(_pet);
		addpointer->show();
	});

// 	Menu* menu = Menu::create();
// 	menu->setPosition(Vec2::ZERO);
// 	this->addChild(menu);

	menu2->addChild(menuItem = MenuItem::create());
	menuItem->setContentSize(_zz->getContentSize());
	menuItem->setPosition(_zz->getPosition());
	menuItem->setAnchorPoint(_zz->getAnchorPoint());
	menuItem->setCallback([this, menuItem](Ref*)
	{
		if (_node1->isVisible())
		{
			_node1->setVisible(false);
			_node2->setVisible(true);
		}
		else
		{
			_node1->setVisible(true);
			_node2->setVisible(false);
		}
	});

	load(pet);
	_node2->setVisible(false);
//	_node2->setPositionX(_node2->getPositionX() - 96);
	return true;
}

void uiPetAttr::load(sPet* pet)
{
	_pet = pet;
	if (pet == nullptr)
	{
		return;
	}
	sPropertys pros;
	ccp::apply(pros, pet);
	_attrHp->setValue(pet->hp, pros.attr.hpMax);
	_attrMp->setValue(pet->mp, pros.attr.mpMax);
	_attr->load(&pros.attr);
	_point->load(&pet->point);
	_attrExp->setValue(cc::toString(pet->exp) + "/" + cc::toString(sExp::getExp(pet->lv, pet->ispet)));
	_zz->load(&pet->zz);
	_ski->load(pet->eskis);
	_ski->setPosition(cc::getLeft(_zz) + _zz->getContentSize().width / 2 - _ski->getContentSize().width / 2, cc::getBottom(_zz) - 24 - _ski->getContentSize().height);
}