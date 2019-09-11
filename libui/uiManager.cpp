#include "uiManager.h"
#include "_cc8.h"
#include "_ccu.h"

#include "uiAddpoint.h"
#include "uiDialog.h"
// #include "uiAccelator.h"
// #include "uiAddpoint.h"
#include "uiChannel.h"
// #include "uiDazao.h"
// #include "uiDye.h"
// #include "uiFriend.h"
// #include "uiFoot.h"
// #include "uiGrids.h"

#include "uiHeader.h"
#include "uiInput.h"
// #include "uiItem.h"
// #include "uiJob.h"
// #include "uiLearn.h"
#include "uiMenu.h"
#include "uiModSelect.h"
#include "uiPet.h"
#include "uiPets.h"
#include "uiPetSelect.h"
// #include "uiRank.h"
#include "uiRole.h"
#include "uiSee.h"
// #include "uiShichen.h"
// #include "uiShop.h"
// #include "uiSkill.h"
// #include "uiSkiSelect.h"
// #include "uiSmap.h"
#include "uiState.h"
// #include "uiWorld.h"




static uiManager* s_ui = nullptr;
uiManager* ccu::getManager()
{
	return s_ui;
}

void ccu::setManager(uiManager* ui)
{
	s_ui = ui;
}


bool uiManager::init()
{
	if (!Node::init())
	{
		return false;
	}

	this->setPosition(cc::vsOrigin());
	Menu* menu = Menu::create();
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	this->addChild(_addpointer = uiAddpointer::create(nullptr));
	_addpointer->setVisible(false);

 	this->addChild(_channel = uiChannel::create(eFont::smaller));

	menu->addChild(_buttonMsg = cButton::create2(ccu::cMessageUnfold));
	_buttonMsg->setPosition(Vec2(0, cc::getTop(_channel)) +  _buttonMsg->getContentSize() / 2);

	this->addChild(_chat = uiChat::create(eFont::smal));
	_chat->setPosition(_chat->getContentSize().width / 2 + 2, cc::vsCenter().y);
	_chat->setVisible(false);
	_chat->onClose = [this](bool)
	{
		_buttonMsg->setVisible(_isShown);
		_channel->setVisible(_isShown);
	};
	_buttonMsg->onClick = [this]()
	{
		_buttonMsg->setVisible(false);
		_channel->setVisible(false);
		_chat->show();
	};


 	this->addChild(_dialog = uiDialog::create(), ccu::zDialog);
	_dialog->setVisible(false);

//	this->addChild(_dye = uiDye::create());


	const int inv = 2;
	this->addChild(_headerRole = uiHeader::create(false));
	_headerRole->setPosition(cc::vsSize().width - inv - _headerRole->getContentSize().width, cc::vsSize().height - _headerRole->getContentSize().height - inv);
	_headerRole->onClick = [this](const sProperty* pro, const sRole* role, bool left)
	{
		if (left)
		{
			if (_role == role)
			{
				_uirole->load(_role);
				_uirole->show();
			}
		}
	};
	_headerRole->onFill = [this](const sProperty* pro, const sRole* role)
	{
		if (_role != role)
		{
			return false;
		}
		ccp::fillHpMp(_role);
		_uirole->getState()->loadAttr(role, true);
		return true;
	};

	this->addChild(_headerPet = uiHeader::create(true));
	_headerPet->setPosition(_headerRole->getPositionX() - inv - _headerPet->getContentSize().width, cc::vsSize().height - _headerPet->getContentSize().height - inv);
	_headerPet->onClick = [this](const sProperty* pro, const sRole* role, bool left)
	{
		if (left)
		{
			if (_role == role)
			{
				_pet->load(_role);
				_pet->show();
			}
		}
	};
	_headerPet->onFill = [this](const sProperty* pro, const sRole* role)
	{
		if (_role != role)
		{
			return false;
		}
		for (auto pet : role->pets)
		{
			ccp::fillHpMp(pet);
			if (pet == pro)
			{

			}
		}
		return true;
	};

	this->addChild(_input = uiInput::create());
	_input->setVisible(false);

// 	this->addChild(_item = uiItem::create());
// 
// 	this->addChild(_job = uiJob::create(), ccu::zJob);
 

	cButton* buttonMenuVisi = cButton::create2(ccu::cMenuVisible);
	buttonMenuVisi->setVisible(false);
	buttonMenuVisi->setPosition(cc::vsSize().width - buttonMenuVisi->getContentSize().width / 2, buttonMenuVisi->getContentSize().height / 2 + 3);
	menu->addChild(buttonMenuVisi);
	// ÏµÍ³²Ëµ¥
	this->addChild(_menu = uiMenu::create());

	this->addChild(_modSelect = uiModSelect::create());
	_modSelect->setVisible(false);
 
 	this->addChild(_pet = uiPets::create(nullptr));
	_pet->getuiPet()->onHeader = [this](const sProperty* pro, const sRole* role)
	{
		if (_role == role)
		{
			_headerPet->load(pro, _role);
		}
	};
	_pet->setVisible(false);

	this->addChild(_petSelector = uiPetSelector::create());
	_petSelector->setVisible(false);

	this->addChild(_uirole = uiRole::create(nullptr));
	_uirole->onFill = [this](sRole* role)
	{
		if (_role == role)
		{
			ccp::fillHpMp(_role);
			_headerRole->load(role, role->hp, role->mp);
		}
	};
	_uirole->onHpMp = [this](sRole* role)
	{
		if (_role == role)
		{
			_headerRole->load(_role, role);
		}
	};
	_uirole->setVisible(false);

 	this->addChild(_see = uiSee::create());
	_see->setVisible(false);
 
//  	this->addChild(_shichen = uiShichen::create(), ccu::zShichen);
// 	this->addChild(_shop = uiShop::create());
// 
// 	this->addChild(_skill = uiSkill::create());
// 	this->addChild(_skillSelect = uiSkiSelect::create());
// 	this->addChild(_smap = uiSmap::create());


	_menu->onHiden = [this, buttonMenuVisi]()
	{
		buttonMenuVisi->setVisible(true);
		show(false);
	};
	buttonMenuVisi->onClick = [this, buttonMenuVisi]()
	{
		buttonMenuVisi->setVisible(false);
		show(true);
	};
	return true;
}

void uiManager::load(sRole* role)
{
	_role = role;
	_headerRole->load(role, role);
	_headerPet->load(role->getPet(), role);
	_pet->load(role);
	_uirole->load(role);
}




void uiManager::toast(const std::string& text, float second /* = 5 */)
{
	cToastManager::getInstance()->add(this, text, second);
}


void uiManager::addChannel(const std::string& name, const std::string& text)
{
	_channel->add(name, text);
	_chat->add(name, text);
}

void uiManager::addChannel(const std::string& text)
{
	addChannel("", text);
}


void uiManager::addChannelSys(const std::string& text)
{
	addChannel(std::string("#R") + cc8::cChannelSys + "#R: " + text);
}

// void uiManager::setCursor(eCursor e)
// {
// 	_cursor->setState(e);
// }
// 
// const eCursor& uiManager::getCursor()
// {
// 	return _cursor->getState();
// }
// 
void uiManager::addJob(const std::string& title, const std::string& text)
{
//	_job->add(title, text);
}





void uiManager::show(bool shown)
{
	_isShown = shown;
	_buttonMsg->setVisible(shown);
	_channel->setVisible(shown && !_chat->isVisible());
//	_chat->setVisible(shown);
	_menu->setVisible(shown);
	_headerRole->setVisible(shown);
	_headerPet->setVisible(shown);

}

bool uiManager::isFight()
{
	return onFight != nullptr && onFight();
}

