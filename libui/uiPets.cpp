#include "uiPets.h"
#include "_cc8.h"
#include "_ccu.h"
#include "uiPet.h"
#include "uiPetCompose.h"
#include "uiSee.h"
#include "uiManager.h"
#include "uiTab.h"


uiPets* uiPets::create(sRole* role)
{
	CREATE(uiPets, role);
}

bool uiPets::init(sRole* role)
{
	if (!uiPad::init(ccu::cPad))
	{
		return false;
	}
	uiPad::setContentSize(uiPad::cSize);
	this->setContentSize(Size(_contentSize.width - uiTab::c40, _contentSize.height));
	this->setPositionX(_position.x - uiTab::c40 / 2);

	uiTab* tab = uiTab::create();
	tab->load(cc8::cBaby, cc8::cCompose);
	tab->setPosition(_contentSize.width + 2, 240);
	this->addChild(tab);

	this->addChild(_pet = uiPet::create(nullptr));
	_pet->setTag(0);
	_pet->setPosition(_contentSize / 2 - _pet->getContentSize() / 2);

	this->addChild(_petCompose = uiPetCompose::create(nullptr));
	_petCompose->setTag(1);
	_petCompose->setPosition(_contentSize.width / 2 - _petCompose->getContentSize().width / 2, _contentSize.height - _petCompose->getContentSize().height - 32);
	_petCompose->onCompose = [this](const sRole* role, int l, int r)
	{
		if (_role != role)
		{
			return false;
		}
		auto pl = _role->getPet(l);
		auto pr = _role->getPet(r);
		pl = ccp::compose(pl, pr);
		int fight = _role->fight;
		_role->removePet(l, false);
		_role->removePet(r > l ? r - 1 : r, true);
		if (_role->fight == cc::_1 && _role->fight != fight)
		{
			if (_pet->onHeader != nullptr)
			{
				_pet->onHeader(nullptr, _role);
			}
		}

		auto see = ccu::getManager()->getSee();
		see->load(pl);
		see->show();

		_role->addPet(pl);
		// See界面用了之前的染色
		// 结果你的pet界面吧染色去掉了
		// 解决: 染色表用mutilmap/引用计数
		_pet->load(_role);
		return true;
	};


// 	this->addChild(_point = uiAddpoint::create(nullptr));
// 	_point->setTag(1);
// 	_point->setPosition(_contentSize / 2 - _point->getContentSize() / 2);
// 
// 	this->addChild(_skill = uiSkill::create(nullptr));
// 	_skill->setTag(2);
// 	_skill->setPosition(_contentSize / 2 - _skill->getContentSize() / 2);
// 
// 	this->addChild(_xl = uiXL::create(nullptr));
// 	_xl->setTag(3);
// 	_xl->setPosition(_contentSize / 2 - _xl->getContentSize() / 2);
//
// 	_state->onLvup = [this](sRole* role)
// 	{
// 		_point->load(role);
// 		_skill->load(role);
// 		_xl->load(role);
// 
// 	};
// 	_point->onPoint = [this](sProperty* pro)
// 	{
// 		ccp::fillHpMp(pro);
// 		_state->loadProperty((sRole*)pro, false);
// 	};
// 
// 	_skill->onLearn = [this](const sRole* role, const std::vector<int>& skis, u64 exp, u64 money)
// 	{
// 		sRole* r = (sRole*)role;
// 		forv(skis, k)
// 		{
// 			r->skilvs.at(k) += skis.at(k);
// 		}
// 		r->exp.sub(exp);
// 		r->money.sub(money);
// 		_state->loadProperty(r, false);
// 	};
// 
// 	_xl->onXL = [this](const sRole* role, const sXl& xl, const sXl& bb, u64 exp)
// 	{
// 		sRole* r = (sRole*)role;
// 		r->xl += xl;
// 		r->xlbb += bb;
// 		r->exp.sub(exp);
// 	};
// 
// 	onClose = [this](bool remove)
// 	{
// 		_skill->apply();
// 		_xl->apply();
// 	};

	tab->onTab = [this](int old, int select)
	{
		if (old == select)
		{
			return;
		}
		_pet->setVisible(false);
		_petCompose->setVisible(false);
//		hide();
		getChildByTag(select)->setVisible(true);
		if (select == _petCompose->getTag())
		{
			_petCompose->check();
		}
	};

	load(role);
	tab->onTab(-1, 0);
	return true;
}


void uiPets::load(sRole* role)
{
	_role = role;
	_pet->load(role);
	_petCompose->load(role);
//	load(role->getPet());
// 	_point->load(role);
// 	if (role != nullptr)
// 	{
// 		_point->setControllable(role->isControllabel());
// 	}
// 	_skill->load(role);
// 	_xl->load(role);

}