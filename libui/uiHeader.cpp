#include "uiHeader.h"
#include "_cc8.h"
#include "_ccu.h"
#include "uiPad.h"
#include "uiManager.h"


bool uiHeader::init(bool pet)
{
	if (!Node::init())
	{
		return false;
	}
	cButton* buttonHeader = cButton::create2(ccu::cHeader);
	_sizeBack = buttonHeader->getContentSize();

	_sizeBar.height = 16;
	_sizeBar.width = 72;
	int hmax = pet ? 3 : 4;
	_sizeBack = Size(_sizeBar.height, _sizeBar.height) * hmax;
	int iy = 0;
	_sizeBack.width += (hmax - 1) * iy;
	_sizeBack.height += (hmax - 1) * iy;
	_sizeBar.width += 3 * iy;
	buttonHeader->setContentSize(_sizeBack);
	buttonHeader->setPosition(buttonHeader->getContentSize() / 2);
	buttonHeader->onClick = [this]()
	{
		if (/*_pro == nullptr || */_role == nullptr || onClick == nullptr)
		{
			return;
		}
		onClick(_pro, _role, true);
	};

	Menu* menu = Menu::create(buttonHeader, nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
	
	buttonHeader->addChild(_spriteHead = cSprite1::create());
	_spriteHead->setPosition(buttonHeader->getContentSize() / 2);

	int ix = 1;
	std::vector<std::string> names = { ccu::cBarHp, ccu::cBarMp, ccu::cBarAp, ccu::cBarExp };
	std::vector<Sprite*> sprites(names.size()), spriteBacks(names.size());
	Sprite* sprite = nullptr, *spriteBack = nullptr;
	forr(sprites, k)
	{
		this->addChild(spriteBack = spriteBacks[k] = Sprite::createWithSpriteFrameName(ccu::cBarBack));
		this->addChild(sprite = sprites[k] = Sprite::createWithSpriteFrameName(names.at(k)));
		
 		Vec2 ori = sprite->getTextureRect().origin;
 		sprite->setTextureRect(Rect(ori, _sizeBar));

		ori = spriteBack->getTextureRect().origin;
		spriteBack->setTextureRect(Rect(ori, _sizeBar));
		sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		spriteBack->setAnchorPoint(sprite->getAnchorPoint());
		sprite->setPosition(_sizeBack.width + ix, (_sizeBack.height) - k * (_sizeBar.height + iy) - _sizeBar.height / 2 - iy);
		spriteBack->setPosition(sprite->getPosition());
	}

	this->setContentSize(Size(_sizeBack.width + ix + _sizeBar.width, _sizeBack.height));

	_spriteHp = sprites.at(0);
	_spriteMp = sprites.at(1);
	_spriteAp = sprites.at(2);
	_spriteExp = sprites.at(3);

	if (pet)
	{
		spriteBacks.back()->setVisible(false);
		_spriteAp->setVisible(false);
		_spriteExp->setPosition(_spriteAp->getPosition());
	}

	MenuItem* menuItem = MenuItem::create();
	menu->addChild(menuItem);
	menuItem->setContentSize(Size(_sizeBar.width, _sizeBack.height));
	menuItem->setPosition(Vec2(_spriteHp->getPositionX(), 0) + menuItem->getContentSize() / 2);
	menuItem->setCallback([this](Ref*)
	{
		// if (_pro != nullptr)
		{
			auto pad = createPad();
			pad->setPosition(_position + Vec2(_contentSize.width - 4, _contentSize.height / 2) - pad->getContentSize() / 2);
			_parent->addChild(pad);
		}
		if (/*_pro == nullptr || */_role == nullptr || onClick == nullptr)
		{
			return;
		}
		onClick(_pro, _role, false);
	});
	return true;
}



void uiHeader::load(const sProperty* pro, int hpMax, int mpMax)
{
	if (pro->mod)
	{
		txtAction::sAction heads;
		pro->mod.apply(heads, false);
		load(heads.at(eAct::head));
	}
	float w;
	if (pro->hp >= 0 && hpMax > 0)
	{
		w = std::min(pro->hp, hpMax) * _sizeBar.width / hpMax;
		Vec2 ori = _spriteHp->getTextureRect().origin;
		_spriteHp->setTextureRect(Rect(ori, Size(w, _spriteHp->getContentSize().height)));
	}
	if (pro->mp >= 0 && mpMax > 0)
	{
		w = std::min(pro->mp, mpMax) * _sizeBar.width / mpMax;
		Vec2 ori = _spriteMp->getTextureRect().origin;
		_spriteMp->setTextureRect(Rect(ori, Size(w, _spriteMp->getContentSize().height)));
	}
	if (pro->ap >= 0)
	{
		w = std::min(pro->ap, sAttribute::cAp) * _sizeBar.width / sAttribute::cAp;
		Vec2 ori = _spriteAp->getTextureRect().origin;
		_spriteAp->setTextureRect(Rect(ori, Size(w, _spriteAp->getContentSize().height)));
	}
	
	int expMax = sExp::getExp(pro->lv, pro->ispet);
	int exp = ((u64)pro->exp > (u64)expMax) ? expMax : (u64)pro->exp;
	w = exp * _sizeBar.width / expMax;
	Vec2 ori = _spriteExp->getTextureRect().origin;
	_spriteExp->setTextureRect(Rect(ori, Size(w, _spriteExp->getContentSize().height)));
}



void uiHeader::load(ulong uhead)
{
	_spriteHead->load(uhead);
	_spriteHead->setVisible(uhead != cSp::c0);
	_spriteHead->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	if (_spriteHead->isValid())
	{
		_spriteHead->setScale((_sizeBack.width - 6) / std::max(_spriteHead->getContentSize().width, _spriteHead->getContentSize().height));
	}
}


void uiHeader::load(const sProperty* pro, const sRole* role)
{
	_pro = pro;
	_role = role;
	if (pro == nullptr)
	{
		load(cSp::c0);
		return;
	}
	sPropertys pros;
	ccp::apply(pros, pro);
	load(pro, pros.attr.hpMax, pros.attr.mpMax);
}



uiPad* uiHeader::createPad()
{
	auto pro = _pro;

	bool remove = true;
	uiPad* pad = uiPad::create(ccu::cDesc, false);
	pad->setClose(false);
	pad->setCloseOnOut(true);
	pad->setRemoveOnClose(remove);
	pad->setAlpha(false);

	int ih = 0, inv = 16;
	float w = 0;
	if (pro != nullptr)
	{
		sPropertys pros;
		ccp::apply(pros, pro);
		int hpMax = pros.attr.hpMax;
		int mpMax = pros.attr.mpMax;

		std::vector<cLabel*> labels;
		std::string str = cc8::cExp;
		str += ": ";
		str += cc::toString(pro->exp);
		str += " / ";
		str += cc::toString(sExp::getExp(pro->lv, pro->ispet));
		labels.push_back(cLabel::create(str));

		if (!pro->ispet)
		{
			str = cc8::cPropertyAp;
			str += ": ";
			str += cc::toString(pro->ap);
			str += " / ";
			str += cc::toString(sAttribute::cAp);
			labels.push_back(cLabel::create(str));
		}

		str = cc8::cPropertyMp;
		str += ": ";
		str += cc::toString(pro->mp);
		str += " / ";
		str += cc::toString(mpMax);
		labels.push_back(cLabel::create(str));

		str = cc8::cPropertyHp;
		str += ": ";
		str += cc::toString(pro->hp);
		str += " / ";
		str += cc::toString(hpMax);
		labels.push_back(cLabel::create(str));

		forv(labels, k)
		{
			cLabel* label = labels.at(k);
			label->setAnchorPoint(Vec2::ZERO);
			if (ih == 0)
			{
				ih = label->getContentSize().height + 2;
			}
			label->setPosition(inv, inv + k * ih);
			w = std::max(w, label->getContentSize().width);
			pad->addChild(label);
		}
		ih *= labels.size();
	}

	cButton* button = cButton::create2(ccu::cBtn48, pro == nullptr ? cc8::cWuyi : (pro->ispet ? cc8::cLV + cc::toString(pro->lv) :  cc8::cJiushi));
//	button->setContentSize(cButton::cSize);
	button->onClick = [this,  pad, remove]()
	{
		if (/*_pro == nullptr || */ccu::getManager()->isFight())
		{
			return;
		}
		if (onFill != nullptr && onFill(_pro, _role))
		{
			if (_pro != nullptr)
			{
				load(_pro, _pro->hp, _pro->mp);
			}
			pad->close();
		}
	};
	pad->getMenu()->addChild(button);
	Size s = button->getContentSize();
	button->setPosition(Vec2(inv, inv + ih + 4) + s / 2);
	w = std::max(w, s.width);
	pad->setContentSize(Size(w + inv * 2, button->getPositionY() + s.height / 2 + inv));
	return pad;
}