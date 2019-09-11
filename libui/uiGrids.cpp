#include "uiGrids.h"
#include "_ccu.h"
#include "uiManager.h"

const int cGrids::c72 = 72;
const int cGrids::cTagHead = 1;
const int cGrids::cTagCount = 2;
const int cGrids::cTagCountBack = 3;
const int cGrids::cTagSelect = 4;

cButton* cGrids::createButton(const sItem* item)
{
	cButton* button = cButton::create2(ccu::cRect);
	button->setContentSize(Size(c72, c72));

	cSprite1* sprite = cSprite1::create();
	sprite->setTag(cTagHead);
	sprite->setPosition(button->getContentSize() / 2);
	button->addChild(sprite);

	cLabelEasy* label = cLabelEasy::create("8", eFont::e100);
	label->setTag(cTagCount);
	label->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
	label->setPosition(4, 4);
	label->setVisible(false);

	cLabelEasy* labelBack = cLabelEasy::create("8", eFont::e100);
	labelBack->setColor(sColor::BLACK);
	label->setTag(cTagCountBack);
	label->setAnchorPoint(label->getAnchorPoint());
	label->setPosition(label->getPosition() + Vec2(2, -2));
	button->addChild(labelBack);
	button->addChild(label);
	labelBack->setVisible(false);

	cSprite9* spriteSelect = cSprite9::create(ccu::uItemSelect);
	spriteSelect->setTag(cTagSelect);
	spriteSelect->setContentSize(button->getContentSize() + Size(12, 12));
	button->addChild(spriteSelect);
	spriteSelect->setVisible(false);

	loadButton(button, item);
	return button;
}

void cGrids::loadButton(cButton* button, const sItem* item)
{
	if (item == nullptr || !item->isValid())
	{

		return;
	}
	loadButton(button, item->getIcon()->uid);
	loadButton(button, item->getCount());
}

void cGrids::loadButton(cButton* button, ulong uhead)
{
	auto sprite = (cSprite1*)button->getChildByTag(cTagHead);
	sprite->load(uhead);
	if (sprite->isValid())
	{
		sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		sprite->setScale((button->getContentSize().width - 6) / std::max(sprite->getContentSize().width, sprite->getContentSize().height));
	}
}

void cGrids::loadButton(cButton* button, int count)
{
	cLabelEasy* label = (cLabelEasy*)button->getChildByTag(cTagCount);
	cLabelEasy* labelBack = (cLabelEasy*)button->getChildByTag(cTagCountBack);
	label->setVisible(count > 1);
	labelBack->setVisible(count > 1);
	label->setNumber(count);
	labelBack->setNumber(count);
}

void cGrids::loadButton(cButton* button, bool selected)
{
	button->getChildByTag(cTagSelect)->setVisible(selected);
}

bool cGrids::init(ui::ScrollView* scrollView)
{
	scrollView->setContentSize(Size(c72 * cItem::c5, c72 * cItem::c4));
	scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
	scrollView->addChild(_menu = Menu::create());
	_menu->setPosition(Vec2::ZERO);
	return true;
}

void cGrids::load(const sItems& items)
{
	for (int k = items.size(), size = _items.size(); k < size; ++k)
	{
		_buttons.at(k)->setVisible(false);
	}
	if (items.empty())
	{
		_items = items;
		return;
	}
	cButton* button = nullptr;
	int inv = 0;
	int size2 = std::ceil(items.size() * 1.0f / cItem::c5) * cItem::c5;
	for (int k = 0, size = std::min(_items.size(), items.size()); k < size; ++k)
	{
		button = _buttons.at(k);
		button->setPositionY(((size2 - 1 - k) / cItem::c5) * (c72 + inv) + c72 / 2);
		loadButton(button, items.at(k));
	}

	for (int k = _items.size(), size = items.size(); k < size; ++k)
	{
		_menu->addChild(button = createButton(items.at(k)));
		_buttons.push_back(button);
		button->setPosition((k % cItem::c5) * (c72 + inv) + c72 / 2, ((size2 - 1 - k) / cItem::c5) * (c72 + inv) + c72 / 2);
		button->onClick = [this, button]()
		{
			int old = getSelect();
			int select = button->getTag();
			bool isSame = old == select;
			if (_isMutex)
			{
				if (!_selects.empty())
				{
					loadButton(_buttons.at(_selects.back()), false);
				}
				_selects.clear();
				_selects.push_back(select);
				loadButton(button, true);
			}
			else
			{
				if (_selects.back() == select)
				{
					_selects.pop_back();
					loadButton(button, false);
				}
				else
				{
					_selects.push_back(select);
					loadButton(button, true);
				}
			}
			if (!isValid(select) || onSelect == nullptr)
			{
				return;
			}
			auto it = _items.at(select);
			if (it == nullptr || !it->isValid())
			{
				return;
			}
			if (_isMutex)
			{
				if (!isSame)
				{
					onSelect(it, select, true);
				}
			}
			else
			{
				onSelect(it, select, !isSame);
			}
		};
	}
	forv(items, k)
	{
		_buttons.at(k)->setTag(k);
	}
}

void cGrids::load(int index, int count)
{
	if (!isValid(index))
	{
		return;
	}
	_items.at(index)->clear();
	_items.at(index)->add(count);
	loadButton(_buttons.at(index), count);
}

void cGrids::setMutex(bool mutex)
{
	_isMutex = mutex;
	if (!mutex)
	{
		forv(_selects, k)
		{
			loadButton(_buttons.at(_selects.at(k)), false);
		}
		if (!_selects.empty())
		{
			int k = _selects.back();
			loadButton(_buttons.at(k), true);
			_selects.clear();
			_selects.push_back(k);
		}
	}
}

int cGrids::getSelect() const
{
	if (_selects.empty())
	{
		return cc::_1;
	}
	return _selects.back();
}


void cGrids::clearSelects()
{
	forv(_buttons, k)
	{
		loadButton(_buttons.at(k), false);
	}
	_selects.clear();
}

void cGrids::setButtonString(const std::string& str1, const std::string& str2 /*= ""*/)
{
	_str1 = str1;
	_str2 = str2;
}


bool cGrids::isValid(int index)
{
	return index >= 0 && index < _items.size();
}
