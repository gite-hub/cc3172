#include "uiRole.h"
#include "_cc8.h"
#include "_ccu.h"
#include "uiState.h"
#include "uiAddpoint.h"
#include "uiSkill.h"
#include "uiXL.h"
#include "uiTab.h"

uiRole* uiRole::create(sRole* role)
{
	CREATE(uiRole, role);
}

bool uiRole::init(sRole* role)
{
	if (!uiPad::init(ccu::cPad))
	{
		return false;
	}
	uiPad::setContentSize(uiPad::cSize);
	this->setContentSize(Size(_contentSize.width - uiTab::c40, _contentSize.height));
	this->setPositionX(_position.x - uiTab::c40 / 2);

	uiTab* tab = uiTab::create();
	tab->load(cc8::cProperty, cc8::cAddpoint, cc8::cSkill, cc8::cXL);
	tab->setPosition(_contentSize.width + 2, 18);
	this->addChild(tab);

	this->addChild(_state = uiState::create(nullptr));
	_state->setTag(0);
	_state->setPosition(_contentSize / 2 - _state->getContentSize() / 2);

	this->addChild(_point = uiAddpoint::create(nullptr));
	_point->setTag(1);
	_point->setPosition(_contentSize / 2 - _point->getContentSize() / 2);

	this->addChild(_skill = uiSkill::create(nullptr));
	_skill->setTag(2);
	_skill->setPosition(_contentSize / 2 - _skill->getContentSize() / 2);

	this->addChild(_xl = uiXL::create(nullptr));
	_xl->setTag(3);
	_xl->setPosition(_contentSize / 2 - _xl->getContentSize() / 2);

	_state->onLvup = [this](const sRole* role)
	{
		if (_role != role)
		{
			return false;
		}
		_role->lvup(false);
		ccp::fillHpMp(_role);
		_point->load(role);
		_skill->load(role);
		_xl->load(role);
		if (onFill != nullptr)
		{
			onFill(_role);
		}
		return true;
	};
	_state->getStone()->onStone = [this](const sRole* role, int k)
	{
		if (_role != role)
		{
			return false;
		}
		_role->stone.switchStone(k);
		_state->loadAttr(_role, false);
		return true;
	};
	_state->onName = [this](const sRole* role, const std::string& name)
	{
		if (_role != role)
		{
			return false;
		}
		_role->name = name;
		return true;
	};
	_state->onMenpai = [this](const sRole* role, eMenpai menpai)
	{
		if (_role != role)
		{
			return false;
		}
		_role->menpai = menpai;
		_skill->load(_role);
		return true;
	};


	_point->onPoint = [this](const sProperty* pro, const sPoint& point)
	{
		if (_role != pro)
		{
			return false;
		}
		_role->point = point;
		ccp::fillHpMp(_role);
		_state->loadAttr(_role, false);
		if (onFill != nullptr)
		{
			onFill(_role);
		}
		return true;
	};

	_skill->onLearn = [this](const sRole* role, const std::vector<int>& skis, u64 exp, u64 money)
	{
		if (_role != role)
		{
			return false;
		}
		forv(skis, k)
		{
			_role->skilvs.at(k) += skis.at(k);
		}
		_role->exp.sub(exp);
		_role->money.sub(money);
		_state->loadExp(_role, false);
		_state->loadAttr(_role, false);
		_xl->load(_role);
		if (onHpMp != nullptr)
		{
			onHpMp(_role);
		}
		return true;
	};

	_xl->onXL = [this](const sRole* role, const sXl& xl, const sXl& bb, u64 exp)
	{
		if (_role != role)
		{
			return false;
		}
		_role->xl += xl;
		_role->xlbb += bb;
		_role->exp.sub(exp);
		_skill->load(_role);
		_state->loadExp(_role, false);
		if (onHpMp != nullptr)
		{
			onHpMp(_role);
		}
		return true;
	};

	tab->onTab = [this](int old, int select)
	{
		if (old == select)
		{
			return;
		}
		hide();
		getChildByTag(select)->setVisible(true);
	};

	load(role);
	tab->onTab(-1, 0);
	return true;
}

void uiRole::load(sRole* role)
{
	_role = role;
	_state->load(role);
	_point->load(role);
	_skill->load(role);
	_xl->load(role);

}

void uiRole::hide()
{
	_state->setVisible(false);
	_point->setVisible(false);
	_skill->setVisible(false);
	_xl->setVisible(false);
}
