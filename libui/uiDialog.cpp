#include "uiDialog.h"
#include "_ccu.h"
#include "uiPad.h"


const int uiDialog::c160 = 160;

bool uiDialog::init()
{
	if (!Node::init())
	{
		return false;
	}

	Size s = cc::vsSize();
	cNode* node = cNode::create(Color3B::BLACK);
	node->setContentSize(s);
	node->setOpacity(0x88);
	this->addChild(node);
	this->setPosition(cc::vsOrigin());

	MenuItem* menuItemScreen = MenuItem::create();
	// Ä¬ÈÏ¾ÓÖÐ
//	menuItemScreen->setAnchorPoint(node->getAnchorPoint());
	menuItemScreen->setContentSize(s);
	menuItemScreen->setPosition(s / 2);
	menuItemScreen->setCallback([this](Ref*)
	{
		if (_spriteSelect->isVisible() && onClick != nullptr)
		{
			setVisible(false);
			onClick();
		}
	});
	Menu* menuScreen = Menu::create(menuItemScreen, nullptr);
	menuScreen->setPosition(Vec2::ZERO);
	this->addChild(menuScreen);


	this->addChild(_spriteDialog = Sprite9::create(ccu::cPad));
	_spriteDialog->set9(32);
	_spriteDialog->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	_spriteDialog->setPosition(s.width / 2, 4);
	_spriteDialog->setContentSize(Size(s.width - 8, c160));

	this->addChild(_spriteSelect = Sprite9::create(ccu::cDesc));
	_spriteSelect->set9(32);
	_spriteSelect->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	_spriteSelect->addChild(_scrollView = ui::ScrollView::create());
	_scrollView->setPosition(Vec2(16, 16));
	_scrollView->setBounceEnabled(true);
	_spriteSelect->setPositionX(s.width - 16);

	Menu* menu = Menu::create(_buttonClose = cButton::create2(ccu::cClose), nullptr);
	this->addChild(menu);
	menu->setPosition(Vec2::ZERO);
	_buttonClose->onClick = [this]()
	{
		setVisible(false);
	};
	_buttonClose->setPositionX(s.width - 32);

	this->addChild(_spriteHead = cSprite1::create());
	this->addChild(_spriteName = cSprite9::create(ccu::uDialogName));
	_spriteName->set9(_spriteName->getContentSize().height / 2);
	_spriteName->addChild(_labelName = cLabel::create());
	_labelName->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	this->addChild(_textContent = cText::create(s.width - _buttonClose->getContentSize().width - 32));
	_textContent->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
//	_labelText->setMaxLineWidth(_spriteDialog->getContentSize().width - 64);
//	_textContent->setDimensions(_spriteDialog->getContentSize().width - 64, 0);
	return true;
}

void uiDialog::load(ulong head, const std::string& name, const std::string& text, const std::vector<std::string>& selects /* =  */, const CB& cb /* = nullptr */)
{
	loadInner(head, name, text, selects);
	forv(selects, k)
	{
		cButton* button = (cButton*)_scrollView->getChildren().at(0)->getChildByTag(k);
		button->onClick = [this, cb, k]()
		{
			setVisible(false);
			if (cb != nullptr)
			{
				cb(k);
			}
		};
	}
	setVisible(true);
	updateOrderOfArrival();
}

void uiDialog::load(const sHeadName& headName, const std::string& text, const std::vector<std::string>& selects /* =  */, const CB& cb /* = nullptr */)
{
	load(headName.head, headName.name, text, selects, cb);
}


void uiDialog::loadInner(ulong head, const std::string& name, const std::string& text, const std::vector<std::string>& selects)
{
	_spriteHead->load(head);
	_spriteHead->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	
	_labelName->setString(name);
	_spriteName->setContentSize(Size(_labelName->getContentSize().width + 32, _spriteName->getContentSize().height));
	_labelName->setPosition(_spriteName->getContentSize() / 2);

	

	_textContent->setString(text);
	float h = c160 * 1.0f;
	_spriteDialog->setContentSize(Size(_spriteDialog->getContentSize().width, std::max(h, _textContent->getContentSize().height)));
	h = _spriteDialog->getPositionY() + _spriteDialog->getContentSize().height;
	_textContent->setPosition(Vec2(32, h - 16));

	_buttonClose->setPositionY(h - 32);

	_spriteName->setAnchorPoint(Vec2::ANCHOR_MIDDLE_BOTTOM);
	_spriteName->setPosition(16 + _spriteHead->getContentSize().width / 2, h + 2);
	_spriteHead->setPosition(Vec2(16, h + 2) + _spriteHead->getAnchorPointInPoints());

	_scrollView->removeAllChildren();
	cMenu* menu = cMenu::create();
	menu->setSwallowsTouch(false);
	_scrollView->addChild(menu);
	if (selects.empty())
	{
		_spriteSelect->setVisible(false);
	}
	else
	{
		_spriteSelect->setVisible(true);
		float w = 0;
		forv(selects, k)
		{
			w = std::max(w, cLabel::create(selects.at(k))->getContentSize().width);
		}
		w = std::max(w + 32, 240.0f);
		int c64 = 0;
		forv(selects, k)
		{
			cButton* button = cButton::create2(ccu::cBtn64, selects.at(k));
			if (c64 == 0)
			{
				c64 = button->getContentSize().height;
			}
			button->set9(40, 16);
			button->setContentSize(Size(w, c64));
			button->setTag(k);
			menu->addChild(button);
		}
		_scrollView->setInnerContainerSize(Size(w, 4 + selects.size() * (c64 + 4)));
		forv(selects, k)
		{
			menu->getChildByTag(_size_ - 1 - k)->setPosition(w / 2, c64 / 2 + 4 + k * (c64 + 4));
		}
		_scrollView->setContentSize(Size(_scrollView->getInnerContainerSize().width, std::min(_scrollView->getInnerContainerSize().height, cc::vsSize().height - h - c64)));
		_spriteSelect->setContentSize(Size(_scrollView->getPosition()) * 2 + _scrollView->getContentSize());
		_spriteSelect->setPositionY(h + 2);
	}
}

