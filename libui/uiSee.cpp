#include "uiSee.h"
#include "_ccu.h"

// cSee* cSee::create(bool name)
// {
// 	CREATE(cSee, name);
// }
//
// bool cSee::init(bool name)
// {
// 	return init(this, name);
// }

bool cSee::init(Node* parent, bool name)
{
	int inv = 16;
	parent->addChild(_attr = uiAttribute::create(true, 7));
	parent->addChild(_point = uiPoint::create(false));
	_point->setPosition(cc::getRight(_attr) + 32, 0);
	parent->addChild(_mod = uiMod::create(145));
	_mod->setPosition(cc::getRight(_attr) + 16, cc::getTop(_point) + inv);
	float h = std::max(cc::getTop(_attr), cc::getTop(_mod));
	parent->addChild(_labelName = cLabel::create());
	if(name)
	{
		_labelName->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
		_labelName->setPosition(0, h + inv);
		h = cc::getTop(_labelName);
	}
	else
	{
		_labelName->setVisible(false);
	}
	parent->addChild(_zz = uiZz::create(true, nullptr));
	float w = std::max(cc::getRight(_point), cc::getRight(_mod));
	_zz->setPosition(w + inv, h - _zz->getContentSize().height);
	parent->addChild(_ski = uiPetSki::create());
	_ski->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
	_ski->setPosition(cc::getBM(_zz) - Vec2(0, inv));
	parent->setContentSize(Size(cc::getRight(_zz), h));
	return true;
}


void cSee::load(const sPet* pet)
{
	if (pet == nullptr)
	{
		return;
	}
	_labelName->setString(pet->name);
	_mod->load(pet);
	sPropertys pros;
	ccp::apply(pros, pet);
	_attr->load(&pros.attr);
	_point->load(&pet->point);
	_zz->load(&pet->zz);
	_ski->load(pet->eskis);
}

//////////////////////////////////////////////////////////////////////////
bool uiSee::init()
{
	if (!uiPad::init(ccu::cPad))
	{
		return false;
	}
	Node* node = Node::create();
	cSee::init(node, false);
	this->addChild(node);

	this->setContentSize(node->getContentSize() + Size(54, 32) * 2);
	node->setPosition(_contentSize / 2 - node->getContentSize() / 2 - Size(0, 12));
	
	return true;
}

void uiSee::load(const sPet* pet)
{
	cSee::load(pet);
	setTitle(pet->name);
}
