#include "uiPetHeaders.h"
#include "_cc8.h"
#include "_ccu.h"
#include "uiDialog.h"
#include "uiManager.h"

const int uiPetHeaders::c4 = 4;
const int uiPetHeaders::cTagSprite = 0;
const int uiPetHeaders::cTagFight = 1;
static Size s_size;

// uiPetHeaders* uiPetHeaders::create(const sPets& pets, int fight)
// {
// 	CREATE(uiPetHeaders, pets, fight);
// }
// 
// uiPetHeaders* uiPetHeaders::create()
// {
// 	CREATE(uiPetHeaders, {}, cc::_1);
// }

bool uiPetHeaders::init(/*const sPets& pets, int fight*/)
{
	if (!ui::ScrollView::init())
	{
		return false;
	}

	_select = cc::_1;
//	this->addChild(_scrollView = ui::ScrollView::create());

	this->addChild(_menu = cMenu::create());
	_menu->scheduleUpdate();
	_menu->setSwallowsTouch(false);

	this->addChild(_spriteSelect = cSprite9::create(ccu::uItemSelect));
	_spriteSelect->setVisible(false);

	this->addChild(_spriteFight = Sprite::createWithSpriteFrameName(ccu::cFight));
	_spriteFight->setTag(cTagFight);
	_spriteFight->setVisible(false);
	_spriteFight->setScale(0.7f);


	s_size = Sprite::createWithSpriteFrameName(ccu::cHeader)->getContentSize();
	_spriteSelect->setContentSize(s_size + Size(12, 12));

	// load(pets, fight);
	return true;
}

static void load(sPet* pPet, cButton* button, cSprite1* sprite)
{
	if (pPet == nullptr || !pPet->mod)
	{
		button->setVisible(false);
		return;
	}
	button->setVisible(true);
	pPet->mod.apply();
	sprite->load(pPet->mod.get(eAct::head));
	sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	sprite->setScale((button->getContentSize().width - 8) / std::max(sprite->getContentSize().width, sprite->getContentSize().height));
}

void uiPetHeaders::load(const sPets& pets, int fight)
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
	cSprite1* sprite = nullptr;
	int inv = 4;
	Size s = s_size;
	int size2 = std::ceil(pets.size() * 1.0f / c4) * c4;
	for (int k = 0, size = std::min(_pets.size(), pets.size()); k < size; ++k)
	{
		button = _buttons.at(k);
		button->setPositionY(((size2 - 1 - k) / c4) * (s.height + inv) + s.height / 2);
		sprite = (cSprite1*)button->getChildByTag(cTagSprite);
		::load(pets.at(k), button, sprite);
	}



	for (int k = _pets.size(), size = pets.size(); k < size; ++k)
	{
		_menu->addChild(button = cButton::create2(ccu::cHeader));
		_buttons.push_back(button);
		button->setPosition(Vec2((k % c4) * (s.width + inv), ((size2  - 1 - k) / c4) * (s.height + inv)) + s / 2);
		button->onClick = [this, button]()
		{
			_select = button->getTag();
			_spriteSelect->setVisible(true);
			_spriteSelect->setPosition(button->getPosition());
			if (onSelect != nullptr)
			{
				onSelect(_pets.at(_select), _select);
			}

		};
		button->onKeep = [this, button](bool first)
		{
			int k = button->getTag();
			auto pet = _pets.at(k);
			if (pet == nullptr)
			{
				return;
			}
			ulong uhead = cSp::c0;
			if (pet->mod)
			{
				pet->mod.apply();
				uhead = pet->mod.get(eAct::dialog);
			}
			std::string text = cc8::cFreeBaby + " #R" + pet->name + "#R (";
			if (pet->mod)
			{
				text += txtMod::getMods().at(pet->mod.e).name + " ";
			}
			text += cc8::cLV + cc::toString(pet->lv) + ") ?";
			ccu::getManager()->getDialog()->load(uhead, pet->name, text, { cc8::cConfirm, cc8::cCancel }, 
			[this, k](int select)
			{
				int fight;
				if (select != 0 || onRemove == nullptr || !onRemove(_pets, k, fight))
				{
					return;
				}
				auto pets = _pets;
				pets.erase(pets.begin() + k);
				_select = cc::_1;
				_spriteSelect->setVisible(false);
				load(pets, fight);
			});
		};

		button->addChild(sprite = cSprite1::create());
		sprite->setTag(cTagSprite);
		sprite->setPosition(button->getContentSize() / 2);
		::load(pets.at(k), button, sprite);
		continue;

		Sprite* spriteFight = Sprite::createWithSpriteFrameName(ccu::cFight);
		button->addChild(spriteFight);
		spriteFight->setTag(cTagFight);
		spriteFight->setVisible(false);
		spriteFight->setScale(0.7f);
		spriteFight->setPosition(button->getContentSize() - spriteFight->getBoundingBox().size / 2);
	}
	forv(pets, k)
	{
		_buttons.at(k)->setTag(k);
	}
	_spriteSelect->setContentSize(s + Size(inv, inv));

	_pets = pets;
	size2 /= c4;
	s.width = c4 * (s.width + inv) - inv + 4;
	s.height = size2 * (s.height + inv) - inv;
	if (size2 <= 2)
	{
		this->setDirection(ui::ScrollView::Direction::NONE);
		this->setContentSize(Size(s.width, s.height));	
	}
	else
	{
		this->setDirection(ui::ScrollView::Direction::VERTICAL);
		this->setContentSize(Size(s.width, (s_size.height + inv) * 2.3f));
	}
	// _scrollView->setContentSize(_contentSize);
	this->setInnerContainerSize(s);
	load(fight);
}

void uiPetHeaders::load(int fight)
{
	_fight = fight;
	forv(_buttons, k)
	{
		break;
		_buttons.at(k)->getChildByTag(cTagFight)->setVisible(false);
	}
	if (fight == cc::_1 || fight >= _pets.size())
	{
		_spriteFight->setVisible(false);
		return;
	}
//	_buttons.at(fight)->getChildByTag(cTagFight)->setVisible(true);
	_spriteFight->setVisible(true);
	_spriteFight->setPosition(cc::getRT(_buttons.at(fight)) - _spriteFight->getBoundingBox().size / 2);
}
