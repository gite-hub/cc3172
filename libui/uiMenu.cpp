#include "uiMenu.h"
#include "_ccu.h"

bool uiMenu::init()
{
	if (!Node::init())
	{
		return false;
	}
	std::map<eOperate, std::string> maps =
	{
	//	{ eOperate::atk, ccu::cMenuAtk },
	//	{ eOperate::act,ccu::cMenuAct },
	//	{ eOperate::achi, ccu::cMenuAchieve },
		{ eOperate::job, ccu::cMenuJob },
		{ eOperate::pack, ccu::cMenuPack },
		{ eOperate::team, ccu::cMenuTeam },
		{ eOperate::sys,ccu::cMenuSys },
	//	{ eOperate::fri,ccu::cMenuFriend },
		{ eOperate::visi, ccu::cMenuVisible}
	};

	Menu* menu = Menu::create();
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
	cButton* button;
	float w = 0;
	int inv = 8;
	for (const auto& it : maps)
	{
		menu->addChild(button = cButton::create2(it.second));
		button->setPosition(button->getContentSize() / 2 + Size(w, 0));
		w += button->getContentSize().width + inv;
		auto e = it.first;
		button->onClick = [this, e]()
		{
			if (e == eOperate::visi)
			{
				if (onHiden != nullptr)
				{
					onHiden();
				}
			}
			if (onOperate != nullptr)
			{
				onOperate(e);
			}
		};
	}
	this->setPosition(cc::vsSize().width - w + inv, 3);
	return true;
}