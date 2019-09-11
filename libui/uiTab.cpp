#include "uiTab.h"
#include "_ccu.h"

const int uiTab::c40 = 54;
// uiTab* uiTab::create(const std::string& tab, const std::string& tab2, const std::string& tab3 /*= ""*/, const std::string& tab4 /*= ""*/, const std::string& tab5 /*= ""*/)
// {
// 	std::vector<std::string> tabs;
// 	tabs.push_back(tab);
// 	tabs.push_back(tab2);
// 	if (!tab3.empty())
// 	{
// 		tabs.push_back(tab3);
// 	}
// 	if (!tab4.empty())
// 	{
// 		tabs.push_back(tab4);
// 	}
// 	if (!tab5.empty())
// 	{
// 		tabs.push_back(tab5);
// 	}
// 	CREATE(uiTab, tabs);
// }
// 
// uiTab* uiTab::create(const std::vector<std::string>& tabs)
// {
// 	CREATE(uiTab, tabs);
// }

bool uiTab::init(/*const std::vector<std::string>& tabs*/)
{
	if (!Node::init())
	{
		return false;
	}
	this->addChild(_menu = Menu::create());
	_menu->setPosition(Vec2::ZERO);
	this->addChild(_spriteDark = Sprite::createWithSpriteFrameName(ccu::cTabDark));
	_spriteDark->setPositionX(_spriteDark->getContentSize().width / 2 - 6);
	// load(tabs);
	return true;
}

void uiTab::load(const std::string& tab, const std::string& tab2, const std::string& tab3 /*= ""*/, const std::string& tab4 /*= ""*/, const std::string& tab5 /*= ""*/)
{
	std::vector<std::string> tabs;
	tabs.push_back(tab);
	tabs.push_back(tab2);
	if (!tab3.empty())
	{
		tabs.push_back(tab3);
	}
	if (!tab4.empty())
	{
		tabs.push_back(tab4);
	}
	if (!tab5.empty())
	{
		tabs.push_back(tab5);
	}
	load(tabs);
}

void uiTab::load(const std::vector<std::string>& tabs)
{
	for (int k = tabs.size(), size = _menuItems.size(); k < size; ++k)
	{
		_menuItems.at(k)->setVisible(false);
		_spriteLights.at(k)->setVisible(false);
		_labels.at(k)->setVisible(false);
	}
	for (int k = 0; k < _menuItems.size(); ++k)
	{
		_menuItems.at(k)->setVisible(true);
		_spriteLights.at(k)->setVisible(true);
		_labels.at(k)->setVisible(true);
	}
	Sprite* sprite = nullptr;
	for (int k = _menuItems.size(), index = 0, size = tabs.size(); k < size; ++k, ++index)
	{
		MenuItem* menuItem = MenuItem::create();
		menuItem->setCallback([this, k](Ref*)
		{
			if (_select == k)
			{
				return;
			}
			_spriteDark->setPositionY(_spriteLights.at(k)->getPositionY());
			if (onTab == nullptr)
			{
				return;
			}
			onTab(_select, k);
			_select = k;
		});
		_menu->addChild(menuItem);
		_menuItems.push_back(menuItem);

		Sprite* spriteLight = Sprite::createWithSpriteFrameName(ccu::cTabLight);
		Size s = spriteLight->getContentSize();
		this->addChild(spriteLight);
		_spriteLights.push_back(spriteLight);
		if (k == 0)
		{
			spriteLight->setPosition(s.width / 2, -s.height);
		}
		else
		{
			sprite = _spriteLights.at(k - 1);
			spriteLight->setPosition(sprite->getPosition() - Vec2(0, s.height + 2));
		}
		menuItem->setContentSize(s);

		cLabel* label = cLabel::create(tabs.at(index), eFont::big);
		label->setDimensions(label->getContentSize().height, 0/*label->getContentSize().width + (int)label->getContentSize().height / 2*/);
		this->addChild(label);
		_labels.push_back(label);
	}
	sprite = _spriteLights.back();
	int h = sprite->getContentSize().height / 2 - sprite->getPositionY();
	forv(_spriteLights, k)
	{
		sprite = _spriteLights.at(k);
		sprite->setPositionY(sprite->getPositionY() + h);
		_menuItems.at(k)->setPosition(sprite->getPosition());
		_labels.at(k)->setPosition(sprite->getPosition());
	}
	sprite = _spriteLights.front();
	this->setContentSize(Size(cc::getRT(sprite)));

// 	if (_spriteDark->getPositionX() < 1)
// 	{
// 		_spriteDark->setPositionX(cc::getRight(sprite) - _spriteDark->getContentSize().width + sprite->getContentSize().width / 2 + 10);
// 	}
	_spriteDark->updateOrderOfArrival();
	_spriteDark->setPositionY(sprite->getPositionY());
	forv(_labels, k)
	{
		_labels.at(k)->updateOrderOfArrival();
	}
	_select = 0;
	if (onTab != nullptr)
	{
		onTab(0, 0);
	}
}
