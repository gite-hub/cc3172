#include "uiPet.h"
#include "_cc8.h"
#include "_ccu.h"
#include "uiInput.h"
#include "uiMod.h"
#include "uiPetHeaders.h"
#include "uiAttr.h"
#include "uiPetAttr.h"
#include "uiManager.h"


uiPet* uiPet::create(sRole* role)
{
	CREATE(uiPet, role);
}

bool uiPet::init(sRole* role)
{
	if (!Node::init())
	{
		return false;
	}
	int inv = 16;
	this->addChild(_headers = uiPetHeaders::create());
	_headers->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	_headers->onSelect = [this](const sPet* pet, int select)
	{
		int old = _select;
		_select = select;
		if (getPet(pet, false) == pet)
		{
			load(_select);
			_buttonFight->setString((_select == _role->fight) ? cc8::cRest : cc8::cJoinFight);
		}
		else
		{
			_select = old;
		}

	};
	_headers->onRemove = [this](const sPets& pets, int select, int& fight)
	{
		auto p = getPet(nullptr, false);
		if (p == nullptr)
		{
			return false;
		}
		int old = _role->fight;
		_role->removePet(select, true);
		fight = _role->fight;
		if (fight == cc::_1 && fight != old)
		{
			if (onHeader != nullptr)
			{
				onHeader(nullptr, _role);
			}
		}
		return true;
	};


	this->addChild(_mod = uiMod::create());
	_mod->onMod = [this](const sMod& mod)
	{
		auto p = getPet(nullptr, false);
		if (p == nullptr)
		{
			return false;
		}
		p->mod = mod;
		return true;
	};

	this->addChild(_labelName = cLabel::create(" "));
	_labelName->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);

	DrawNode* node = DrawNode::create(1);
	node->setContentSize(Size(_mod->getContentSize().width, _labelName->getContentSize().height + inv));
	node->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	node->drawRect(Vec2::ZERO, node->getContentSize(), Color4F::WHITE);
	this->addChild(node);

	MenuItem* menuItem = MenuItem::create();
	menuItem->setContentSize(node->getContentSize());
	menuItem->setAnchorPoint(node->getAnchorPoint());
	menuItem->setCallback([this](Ref*)
	{
		auto p = getPet(nullptr, false);
		if (p == nullptr)
		{
			return;
		}
		auto input = ccu::getManager()->getInput();
		input->setDesc(cc8::cNewName);
		input->setString(p->name);
		input->show();
		input->onInput = [this](const std::string& name)
		{
			auto p = getPet(nullptr, false);
			if (p == nullptr)
			{
				return;
			}
			if (!_role->isControllabel() || _role->isTeam() || ccu::getManager()->isFight())
			{
				ccu::getManager()->toast(cc8::cYouCant);
				return;
			}
			// if (onName != nullptr && onName(p, name))
			{
				p->name = name;
				load(name);
			}
		};
	});

	_buttonFight = cButton::create2(ccu::cBtn64);
	_buttonFight->setPosition(Vec2(0, 0) + _buttonFight->getContentSize() / 2);
	_buttonFight->onClick = [this]()
	{
		auto pet = getPet(nullptr, false);
		if (pet == nullptr)
		{
			return;
		}
		if (_select == _role->fight)
		{
			_role->unPet();	
			_buttonFight->setString(cc8::cJoinFight);
			if (onHeader != nullptr)
			{
				onHeader(nullptr, _role);
			}
		}
		else
		{
			// if (onFight != nullptr && onFight(_role, _select))
			if (!_role->setPet(_select, true))
			{
				ccu::getManager()->toast(cc8::cYouCant);
				return;
			}
			_role->setPet(_select, false);
			{
				_buttonFight->setString(cc8::cRest);
			}
			if (onHeader != nullptr)
			{
				onHeader(pet, _role);
			}
		}
		_headers->load(_role->fight);
	};

	Menu* menu = Menu::create(menuItem, _buttonFight, nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
	
	this->addChild(_attr = uiPetAttr::create(nullptr));
	_attr->setPosition(320/*cc::getRight(_headers) + inv*/, cc::getTop(_buttonFight) + inv);
	_attr->onPoint = [this](const sProperty* pro, const sPoint& point)
	{
		auto pet = getPet(pro, false);
		if (pet == nullptr)
		{
			return false;
		}
		pet->point = point;
		ccp::fillHpMp(pet);
		_attr->load(pet);
		return true;
	};

	this->setContentSize(Size(cc::getRT(_attr)));
	_buttonFight->setPositionX(cc::getBM(_attr).x);

	node->setPosition(0, _contentSize.height - node->getContentSize().height / 2);
	menuItem->setPosition(node->getPosition());
	_labelName->setPosition(node->getPosition() + Vec2(4, 0));
	
	_mod->setPositionY(cc::getBottom(node) - 8 - _mod->getContentSize().height);
	cLabel* label = cLabel::create(cc8::cSupportLong, eFont::smaller);
	this->addChild(label);
	label->setPosition(Vec2(0, cc::getBottom(_mod) - label->getContentSize().height) + label->getContentSize() / 2);
	_headers->setPositionY(cc::getBottom(label));

	load(role);
	return true;
}


void uiPet::load(sRole* role)
{
	_role = role;
	if (role == nullptr)
	{
		return;
	}
	if (_select == cc::_1 || _select >= role->pets.size())
	{
		_select = role->pets.empty() ? cc::_1 : 0;
	}
	_headers->load(_role->pets, _role->fight);
	if (_select != cc::_1)
	{
		load(_select);
	}
}

void uiPet::load(int select)
{
	auto pet = _role->pets.at(select);
	_attr->load(pet);
	_mod->load(pet);
	if (pet != nullptr)
	{
		load(pet->name);
	}
	if (_role != nullptr)
	{
		bool rest = select == _role->fight;
		_buttonFight->setString(rest ? cc8::cJoinFight : cc8::cRest);
	}
}


void uiPet::load(const std::string& name)
{
	_labelName->setString(name);
}

sPet* uiPet::getPet(const sProperty* pro, bool checkTeam)
{
	if (_role == nullptr || _select < 0)
	{
		return nullptr;
	}
	
	if (!_role->isControllabel() || (checkTeam && _role->isTeam()) || ccu::getManager()->isFight())
	{
		ccu::getManager()->toast(cc8::cYouCant);
		return nullptr;
	}
	auto pet = _role->getPet(_select);
	if (pro != nullptr && pet != pro)
	{
		return nullptr;
	}
	return pet;
}

