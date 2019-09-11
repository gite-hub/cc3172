#include "uiState.h"
#include "_cc8.h"
#include "_ccu.h"
#include "uiInput.h"
#include "uiDialog.h"
#include "uiManager.h"

uiState* uiState::create(const sRole* role)
{
	CREATE(uiState, role);
}

bool uiState::init(const sRole* role)
{
	if (!Node::init())
	{
		return false;
	}
	Menu* menu = Menu::create();
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	cButton* buttonLvup = cButton::create2(ccu::cButton48, cc8::cLvup);
	buttonLvup->onClick = [this]()
	{
		if (_role == nullptr)
		{
			return;
		}
		if (!_role->isControllabel() || ccu::getManager()->isFight() || !((sRole*)_role)->lvup(true))
		{
			ccu::getManager()->toast(cc8::cYouCant);
			return;
		}
		if (onLvup != nullptr && onLvup(_role))
		{
			loadLv(_role, false);
			loadExp(_role, false);
			loadAttr(_role, false);
		}
	};
	menu->addChild(buttonLvup);

	this->addChild(_attrExp = uiAttr::create(27, cc8::cExp));
	Size s = _attrExp->getContentSize();
	float h = buttonLvup->getContentSize().height;
	_attrExp->setPositionY((h - s.height) / 2);
	buttonLvup->setPosition(s.width + buttonLvup->getContentSize().width / 2, h / 2);

	int inv = 8;
	this->addChild(_stone = uiStone::create(nullptr));
	_stone->setPosition(0, cc::getTop(_attrExp) + inv);

	this->addChild(_labelLv = cLabelEasy::create(cc8::cLV + "9999", eFont::e150));
	_labelLv->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	_labelLv->setPosition(0, cc::getTop(_stone) + inv + _labelLv->getContentSize().height / 2);

	this->addChild(_labelName = cLabel::create(" ", eFont::big));
	float w = 108;
	_labelName->setPosition(cc::getRight(_labelLv) + w, _labelLv->getPositionY() - cLabelEasy::cOffy);

	this->addChild(_labelMenpai = cLabel::create(" ", eFont::big));
	_labelMenpai->setPosition(cc::getRight(_labelName) + w * 2, _labelName->getPositionY());


	DrawNode* node = DrawNode::create(1);
	node->setContentSize(Size(w * 2, _labelName->getContentSize().height + 8));
	node->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	node->setPosition(_labelName->getPosition() - Vec2(0, 1));
	node->drawRect(Vec2::ZERO, node->getContentSize(), Color4F::WHITE);
	this->addChild(node);

	DrawNode* node2 = DrawNode::create(1);
	node2->setContentSize(Size(128, _labelMenpai->getContentSize().height + 8));
	node2->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	node2->setPosition(_labelMenpai->getPosition() - Vec2(0, 1));
	node2->drawRect(Vec2::ZERO, node2->getContentSize(), Color4F::WHITE);
	this->addChild(node2);

	MenuItem* menuItem = MenuItem::create();
	menuItem->setAnchorPoint(node->getAnchorPoint());
	menuItem->setContentSize(node->getContentSize());
	menuItem->setPosition(node->getPosition());
	menuItem->setCallback([this](Ref*)
	{
		if (_role == nullptr)
		{
			return;
		}
		if (!_role->isControllabel() || _role->isTeam() || ccu::getManager()->isFight())
		{
			ccu::getManager()->toast(cc8::cYouCant);
			return;
		}
		auto input = ccu::getManager()->getInput();
		input->setDesc(cc8::cNewName);
		input->setString( _role->name);
		input->show();
		input->onInput = [this](const std::string& name)
		{
			if (_role == nullptr)
			{
				return;
			}
			if (!_role->isControllabel() || _role->isTeam() || ccu::getManager()->isFight())
			{
				ccu::getManager()->toast(cc8::cYouCant);
				return;
			}
			if (onName != nullptr && onName(_role, name))
			{
				load(_role->name);
			}
		};
	});
	menu->addChild(menuItem);


	menu->addChild(menuItem = MenuItem::create());
	menuItem->setAnchorPoint(node2->getAnchorPoint());
	menuItem->setContentSize(node2->getContentSize());
	menuItem->setPosition(node2->getPosition());
	menuItem->setCallback([this](Ref*)
	{
		if (_role == nullptr)
		{
			return;
		}
		if (!_role->isControllabel() || _role->isTeam() || ccu::getManager()->isFight())
		{
			ccu::getManager()->toast(cc8::cYouCant);
			return;
		}
		std::vector<std::string> menpaiNames;
		for (int e = (int)eMenpai::e0; e <= (int)eMenpai::eEnd; ++e)
		{
			menpaiNames.push_back(txtSki::getName((eMenpai)e));
		}
		menpaiNames.push_back(txtSki::getName(eMenpai::eNone));
		ulong uhead = cSp::c0;
		if (_role->mod)
		{
			_role->mod.apply();
			uhead = _role->mod.get(eAct::dialog);
		}
		int size = menpaiNames.size();
		ccu::getManager()->getDialog()->load(uhead, _role->name, cc8::cChangeMenpai, menpaiNames, [this, size](int select)
		{
			if (!_role->isControllabel() || _role->isTeam() || ccu::getManager()->isFight())
			{
				ccu::getManager()->toast(cc8::cYouCant);
				return;
			}
			eMenpai menpai = (select == size - 1) ? eMenpai::eNone : (eMenpai)((int)eMenpai::e0 + select);
			if (onMenpai != nullptr && onMenpai(_role, menpai))
			{
				load(menpai);
			};
		});
	});


	this->addChild(_attr = uiAttribute::create());
	_attr->setPosition(cc::getRight(_stone) + 160,  cc::getTop(buttonLvup) + inv);

	this->addChild(_point = uiPoint::create());
	_point->setPosition(_attr->getPositionX() + _attr->getContentSize().width + 48, _attr->getPositionY());

	this->addChild(_attrHp = uiAttr::create(10, cc8::cPropertyHp));
	this->addChild(_attrMp = uiAttr::create(10, cc8::cPropertyMp));
	this->addChild(_attrAp = uiAttr::create(3, cc8::cPropertyAp));
	std::vector<uiAttr*> attrs =
	{
		_attrHp,
		_attrMp,
	//	_attrAp,
	};
	uiAttr* a = nullptr;
	h = _attr->getPositionY() + _attr->getContentSize().height + uiAttr::cInterval;
	forr(attrs, k)
	{
		a = attrs.at(k);
		a->setPosition(_attr->getPositionX() + _attr->getSpriteX() - a->getSpriteX(), h);
		h += a->getContentSize().height + uiAttr::cInterval;
	}
	h = std::max(_contentSize.height, h - uiAttr::cInterval);

	_attrAp->setPosition(_point->getPosition() + Vec2(0, _point->getContentSize().height + uiAttr::cInterval));
	_attrAp->setCascadeColorEnabled(true);
	_attrAp->setColor(sColor(0xDD, 0xDD, 0x22));

	this->setContentSize(Size(std::max(cc::getRight(buttonLvup), cc::getRight(_point)), cc::getTop(node)));
	load(role);
	return true;
}

void uiState::load(const sRole* role)
{
	_role = role;
	if (role == nullptr)
	{
		return;
	}
	loadLv(role, false);
	loadExp(role, false);
	load(role->name);
	load(role->menpai);
	loadAttr(role, false);
	_stone->load(role);
}

void uiState::load(const std::string& name)
{
	_labelName->setString(name);
}

void uiState::load(eMenpai e)
{
	_labelMenpai->setString(txtSki::getName(e));
}

void uiState::loadAttr(const sRole* role, bool check)
{
	if (check && role == nullptr)
	{
		return;
	}
	sPropertys pros;
	ccp::apply(pros, role);
	_attrHp->setValue(role->hp, pros.attr.hpMax);
	_attrMp->setValue(role->mp, pros.attr.mpMax);
	_attrAp->setValue(role->ap/*, sAttribute::cAp150*/);
	_attr->load(&pros.attr);
	_point->load(&role->point);
}



void uiState::loadLv(const sRole* role, bool check)
{
	if (check && role == nullptr)
	{
		return;
	}
	_labelLv->setString(cc8::cLV + cc::toString(role->lv));
}

void uiState::loadExp(const sRole* role, bool check)
{
	if (check && role == nullptr)
	{
		return;
	}
	_attrExp->setValue(cc::toString(role->exp) + "/" + cc::toString(sExp::getExp(role->lv, role->ispet)));
}
