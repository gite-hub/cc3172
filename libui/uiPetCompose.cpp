#include "uiPetCompose.h"
#include "_cc8.h"
#include "_ccu.h"
#include "uiPad.h"
#include "uiPetSelect.h"
#include "uiManager.h"


bool uiPetCompose1::init()
{
	if (!Node::init())
	{
		return false;
	}
	this->addChild(_zz = uiZz::create(true, nullptr));
	this->addChild(_ski = uiPetSki::create());

	_buttonAdd = cButton::create2(ccu::cAddBaby);
	_buttonAdd->onClick = [this]()
	{
		if (_role == nullptr || _role->pets.empty())
		{
			return;
		}
		auto petSelector = ccu::getManager()->getPetSelector();
		petSelector->load(_role->pets);
		petSelector->setPosition(_button->getParent()->convertToWorldSpace(cc::getLB(_button)));
		petSelector->setPosition(petSelector->getPosition() - Vec2(0, petSelector->getContentSize().height) + petSelector->getContentSize() / 2);
		petSelector->onSelect = [this, petSelector](const sPet* pet, int select)
		{
			petSelector->close();
			_select = select;
			_pet = _role->pets.at(select);
			cPetSelect::loadButton(pet, _button);
			load(pet);
			_buttonAdd->setVisible(false);
			_button->setVisible(true);
		};
		petSelector->show();
	};
	_button = cPetSelect::createButton(nullptr, cPetSelect::c8);
	_button->onClick = _buttonAdd->onClick;

	Menu* menu = Menu::create(_buttonAdd, _button, nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	int inv = 16;
	_ski->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	_zz->setPositionY(inv);
	_button->setPosition(Vec2(0, cc::getTop(_zz) + inv) + _button->getContentSize() / 2);
	_buttonAdd->setPosition(cPetSelect::c8 + _buttonAdd->getContentSize().width / 2, _button->getPositionY());

	this->setContentSize(Size(_zz->getContentSize().width, cc::getTop(_button)));
	clear();
	return true;
}

void uiPetCompose1::load(const sPet* pet)
{
	if (pet == nullptr)
	{
		_zz->setVisible(false);
		_ski->setVisible(false);
		return;
	}
	_zz->setVisible(true);
	_ski->setVisible(true);
	const auto& zz = pet->zz;
	_zz->load(&pet->zz);
	_ski->load(pet->eskis);
	_ski->setPositionX(_zz->getContentSize().width / 2 - _ski->getContentSize().width / 2);
}

void uiPetCompose1::check()
{
	if (_role == nullptr || _select == cc::_1 || _role->pets.empty() || _select >= _role->pets.size() || _pet != _role->pets.at(_select))
	{
		clear();
	}
}

void uiPetCompose1::clear()
{
	_button->setVisible(false);
	_buttonAdd->setVisible(true);
	_zz->setVisible(false);
	_ski->setVisible(false);
	_select = cc::_1;
	_pet = nullptr;
}



//////////////////////////////////////////////////////////////////////////
uiPetCompose* uiPetCompose::create(sRole* role)
{
	CREATE(uiPetCompose, role);
}

bool uiPetCompose::init(sRole* role)
{
	if (!Node::init())
	{
		return false;
	}

	this->addChild(_left = uiPetCompose1::create());
	this->addChild(_right = uiPetCompose1::create());

	_button = cButton::create2(ccu::cCompose);
	_button->onClick = [this]()
	{
		if (_role == nullptr)
		{
			return;
		}
		int l = _left->_select;
		int r = _right->_select;
		if (l == cc::_1 || r == cc::_1 || l == r || !_role->isControllabel() || ccu::getManager()->isFight())
		{
			ccu::getManager()->toast(cc8::cYouCant);
			return;
		}
		if (onCompose != nullptr && onCompose(_role, l, r))
		{
			clear();
		}
	};
	
	Menu* menu = Menu::create(_button, nullptr);
	this->addChild(menu);
	menu->setPosition(Vec2::ZERO);

	int inv = 32;
	_button->setPosition(Vec2(cc::getRight(_left), 0) + _button->getContentSize() / 2);
	_right->setPosition(cc::getRight(_button), 0);

	this->setContentSize(Size(cc::getRT(_right)));
	_button->setPositionY(_contentSize.height - uiPad::cSize.height / 2);

	load(role);
	return true;
}

void uiPetCompose::load(sRole* role)
{
	_role = role;
	if (_role == nullptr)
	{
		return;
	}
	_left->setRole(role);
	_right->setRole(role);
	clear();
}

void uiPetCompose::check()
{
	_left->check();
	_right->check();
}

void uiPetCompose::clear()
{
	_left->clear();
	_right->clear();
}
