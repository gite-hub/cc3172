#include "uiPetSelect.h"
#include "_cc8.h"
#include "_ccu.h"
#include "uiInput.h"
#include "uiModSelect.h"
#include "uiManager.h"

const int cPetSelect::c5 = 4;
const int cPetSelect::c8 = 8;
const int cPetSelect::c56 = 56;
const int cPetSelect::cTagSprite = 1;
const int cPetSelect::cTagName = 2;
const int cPetSelect::cTagLv = 3;

static void load(const sPet* pPet, float w8, cSprite1* sprite, cLabel* labelName, cLabelEasy* labelLv)
{
	if (pPet == nullptr)
	{
		return;
	}
	pPet->mod.apply();
	sprite->load(pPet->mod.get(eAct::head));
	sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	sprite->setScale((w8 - 8) / std::max(sprite->getContentSize().width, sprite->getContentSize().height));
	labelName->setString(pPet->name);
	labelLv->setString(cc8::cLV + cc::toString(pPet->lv));
}


Node* cPetSelect::createHeader(const sPet* pet, int inv)
{
	Size s(234, c56 + inv * 2);
	Node* node = Node::create();
	node->setTag(cTagSprite);
	node->setContentSize(s);

	Sprite* spriteBack = nullptr;
	node->addChild(spriteBack = Sprite::createWithSpriteFrameName(ccu::cHeader));
	spriteBack->setScale(c56 / spriteBack->getContentSize().width);
	spriteBack->setPosition(inv + c56 / 2, inv + c56 / 2);

	cSprite1* sprite = nullptr;
	cLabel* labelName = nullptr;
	cLabelEasy* labelLv = nullptr;
	node->addChild(sprite = cSprite1::create());
	sprite->setTag(cTagSprite);
	sprite->setPosition(spriteBack->getPosition());

	node->addChild(labelName = cLabel::create(" "));
	labelName->setTag(cTagName);
	labelName->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	labelName->setPosition(c56 + inv * 2, s.height - inv - labelName->getContentSize().height / 2);

	node->addChild(labelLv = cLabelEasy::create(" ", eFont::e100));
	labelLv->setTag(cTagLv);
	labelLv->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	labelLv->setPosition(labelName->getPositionX(), cc::getBottom(labelName) - labelLv->getContentSize().height / 4);

	loadHeader(pet, node);

	return node;
}

cButton* cPetSelect::createButton(const sPet* pet, int inv)
{
	cButton *button = cButton::create2(ccu::cBtn64);
	button->set9(44, 12);
	Node* node = createHeader(pet, inv);
	button->addChild(node);
	button->setContentSize(node->getContentSize());
	return button;
}

void cPetSelect::loadHeader(const sPet* pet, Node* node)
{
	cSprite1* sprite = (cSprite1*)node->getChildByTag(cPetSelect::cTagSprite);
	cLabel* labelName = (cLabel*)node->getChildByTag(cPetSelect::cTagName);
	cLabelEasy* labelLv = (cLabelEasy*)node->getChildByTag(cPetSelect::cTagLv);
	::load(pet, cPetSelect::c56, sprite, labelName, labelLv);
}

void cPetSelect::loadButton(const sPet* pet, cButton* button)
{
	loadHeader(pet, button->getChildByTag(cTagSprite));
}


bool cPetSelect::init(Node* parent)
{
	parent->addChild(_scrollView = ui::ScrollView::create());
	_scrollView->addChild(_menu = cMenu::create());
//	_menu->scheduleUpdate();
	_menu->setSwallowsTouch(false);
	return true;
}

void cPetSelect::load(int showSize, Node* parent, const sPets& pets)
{
	for (int k = pets.size(), size = _pets.size(); k < size; ++k)
	{
		_buttons.at(k)->setVisible(false);
	}
	if (pets.empty())
	{
		_pets = pets;
		return;
	}
	cButton* button = nullptr;
	for (int k = 0, size = std::min(_pets.size(), pets.size()); k < size; ++k)
	{
		button = _buttons.at(k);
		loadButton(pets.at(k), button);
	}

	for (int k = _pets.size(), size = pets.size(); k < size; ++k)
	{
		_menu->addChild(button = createButton(pets.at(k), c8));
		_buttons.push_back(button);
		button->onClick = [this, button]()
		{
			int tag = button->getTag();
			if (onSelect != nullptr)
			{
				onSelect(_pets.at(tag), tag);
			}

		};
	}
	float inv = 4;
	Size s = button->getChildByTag(cTagSprite)->getContentSize();
	forv(pets, k)
	{
		button = _buttons.at(k);
		button->setTag(k);
		button->setPosition(Vec2(0, (_size_ - 1 - k) * (s.height + inv)) + s / 2);
	}
	_pets = pets;
	Size size = s;
	Size s2 = s;
	size.height = pets.size() * (s.height + inv);
	s2.height = std::min((int)pets.size(), showSize) * (s.height + inv);
	parent->setContentSize(s2);
	_scrollView->setContentSize(s2);
	_scrollView->setInnerContainerSize(size);
}


//////////////////////////////////////////////////////////////////////////
// uiPetSelect* uiPetSelect::create(int showSize, const sPets& pets)
// {
// 	CREATE(uiPetSelect, showSize, pets);
// }
uiPetSelect* uiPetSelect::create(int showSize)
{
	CREATE(uiPetSelect, showSize/*, {}*/);
}
uiPetSelect* uiPetSelect::create()
{
	CREATE(uiPetSelect, c5/*, {}*/);
}


bool uiPetSelect::init(int showSize/*, const sPets& pets*/)
{
	if (!Node::init())
	{
		return false;
	}
	cPetSelect::init(this);
	// load(showSize, pets);
	return true;
}

void uiPetSelect::load(const sPets& pets)
{
	load(c5, pets);
}

void uiPetSelect::load(int showSize, const sPets& pets)
{
	cPetSelect::load(showSize, this, pets);
}



//////////////////////////////////////////////////////////////////////////
// uiPetSelector* uiPetSelector::create(int showSize, const sPets& pets)
// {
// 	CREATE(uiPetSelector, showSize, pets);
// }

uiPetSelector* uiPetSelector::create(int showSize)
{
	CREATE(uiPetSelector, showSize/*, {}*/);
}

uiPetSelector* uiPetSelector::create()
{
	CREATE(uiPetSelector, c5/*, {}*/);
}

bool uiPetSelector::init(int showSize/*, const sPets& pets*/)
{
	if (!uiPad::init(ccu::cDesc))
	{
		return false;
	}
	uiPad::setClose(false);
	uiPad::setCloseOnOut(true);
	uiPad::setAlpha(false);

	this->addChild(_node = Node::create());
	cPetSelect::init(_node);
	_node->setPosition(16, 16);
	// load(showSize, pets);
	return true;
}

void uiPetSelector::load(const sPets& pets)
{
	load(c5, pets);
}

void uiPetSelector::load(int showSize, const sPets& pets)
{
	cPetSelect::load(showSize, _node, pets);
	this->setContentSize(_node->getContentSize() + Size(_node->getPosition()) * 2);
}
