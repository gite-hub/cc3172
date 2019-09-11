#include "cMenu.h"
#include "ui/UIScrollView.h"

static float s_distance = 8;

cMenu* cMenu::create()
{
	return cMenu::create(nullptr, nullptr);
}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
cMenu * cMenu::variadicCreate(MenuItem* item, ...)
{
	va_list args;
	va_start(args, item);

	cMenu *ret = cMenu::createWithItems(item, args);

	va_end(args);

	return ret;
}
#else


cMenu * cMenu::create(MenuItem* item, ...)
{
	va_list args;
	va_start(args, item);

	cMenu *ret = cMenu::createWithItems(item, args);

	va_end(args);

	return ret;
}
#endif


cMenu* cMenu::createWithArray(const Vector<MenuItem*>& arrayOfItems)
{
	auto ret = new (std::nothrow) cMenu();
	if (ret && ret->initWithArray(arrayOfItems))
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}

	return ret;
}

cMenu* cMenu::createWithItems(MenuItem* item, va_list args)
{
	Vector<MenuItem*> items;
	if (item)
	{
		items.pushBack(item);
		MenuItem *i = va_arg(args, MenuItem*);
		while (i)
		{
			items.pushBack(i);
			i = va_arg(args, MenuItem*);
		}
	}

	return cMenu::createWithArray(items);
}


cMenu* cMenu::createWithItem(MenuItem* item)
{
	return cMenu::create(item, nullptr);
}

bool cMenu::init()
{
	return initWithArray(Vector<MenuItem*>());
}

bool cMenu::initWithArray(const Vector<MenuItem*>& arrayOfItems)
{
	if (Layer::init())
	{
		_enabled = true;
		// menu in the center of the screen
//		Size s = Director::getInstance()->getWinSize();
//
// 		this->setIgnoreAnchorPointForPosition(true);
// 		setAnchorPoint(Vec2(0.5f, 0.5f));
// 		this->setContentSize(s);
// 
// 		setPosition(s.width / 2, s.height / 2);

		int z = 0;

		for (auto& item : arrayOfItems)
		{
			this->addChild(item, z);
			z++;
		}

		_selectedItem = nullptr;
		_state = Menu::State::WAITING;

		// enable cascade color and opacity on menus
		setCascadeColorEnabled(true);
		setCascadeOpacityEnabled(true);


		_touchListener = EventListenerTouchOneByOne::create();

		_touchListener->onTouchBegan = CC_CALLBACK_2(Menu::onTouchBegan, this);
		_touchListener->onTouchMoved = CC_CALLBACK_2(Menu::onTouchMoved, this);
		_touchListener->onTouchEnded = CC_CALLBACK_2(Menu::onTouchEnded, this);
		_touchListener->onTouchCancelled = CC_CALLBACK_2(Menu::onTouchCancelled, this);

		_eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);

		return true;
	}
	return false;
}



bool cMenu::onTouchBegan(Touch* touch, Event* /*event*/)
{
	auto camera = Camera::getVisitingCamera();
	if (_state != Menu::State::WAITING || !_visible || !_enabled || !camera)
	{
		return false;
	}

	ui::ScrollView* scrollView = dynamic_cast<ui::ScrollView*>(_parent->getParent());
	if (scrollView != nullptr)
	{
		Rect rect;
		rect.size = scrollView->getContentSize();
		if (!isScreenPointInRect(touch->getLocation(), camera, scrollView->getWorldToNodeTransform(), rect, nullptr))
		{
			return false;
		}
	}

	for (Node *c = this->_parent; c != nullptr; c = c->getParent())
	{
		if (c->isVisible() == false)
		{
			return false;
		}
	}
	_selectedItem = this->getItemForTouch(touch, camera);

	if (_selectedItem)
	{
		_state = Menu::State::TRACKING_TOUCH;
		_selectedWithCamera = camera;
		_selectedItem->selected();
		_touch = touch;
		return true;
	}

	return false;
}

void cMenu::onTouchEnded(Touch* touch, Event* /*event*/)
{
	CCASSERT(_state == Menu::State::TRACKING_TOUCH, "[Menu ccTouchEnded] -- invalid state");
	this->retain();
	if (_selectedItem)
	{
		_selectedItem->unselected();
		_selectedItem->removeComponent(cc::cComponentMenuItemLongPress1);
		_selectedItem->removeComponent(cc::cComponentMenuItemLongPress);
		// 触发长按以后,后面就没法点击了
		if (_keepTimes == 0 && touch->getLocation().distance(touch->getStartLocation()) < s_distance)
		{
			_selectedItem->activate();
		}
	}
	_state = Menu::State::WAITING;
	_selectedWithCamera = nullptr;
	this->release();
}

void cMenu::onTouchCancelled(Touch* /*touch*/, Event* /*event*/)
{
	CCASSERT(_state == Menu::State::TRACKING_TOUCH, "[Menu ccTouchCancelled] -- invalid state");
	this->retain();
	if (_selectedItem)
	{
		_selectedItem->unselected();
		_selectedItem->removeComponent(cc::cComponentMenuItemLongPress1);
		_selectedItem->removeComponent(cc::cComponentMenuItemLongPress);
	}
	_state = Menu::State::WAITING;
	this->release();
}

void cMenu::onTouchMoved(Touch* touch, Event* /*event*/)
{
	CCASSERT(_state == Menu::State::TRACKING_TOUCH, "[Menu ccTouchMoved] -- invalid state");
	MenuItem *currentItem = this->getItemForTouch(touch, _selectedWithCamera);
	if (currentItem != _selectedItem)
	{
		if (_selectedItem)
		{
			_selectedItem->unselected();
			_selectedItem->removeComponent(cc::cComponentMenuItemLongPress1);
			_selectedItem->removeComponent(cc::cComponentMenuItemLongPress);
		}
		_selectedItem = currentItem;
		if (_selectedItem)
		{
			_selectedItem->selected();
		}
	}
}

void cMenu::setSwallowsTouch(bool swallowTouches)
{
	_touchListener->setSwallowTouches(swallowTouches);
}


void cMenu::update(float delta)
{
	if (_state != Menu::State::TRACKING_TOUCH)
	{
		_delta = 0;
		_keepTimes = 0;
		return;
	}
	if ((_delta += delta) > 0.7f)
	{
		if (_selectedItem && _touch->getLocation().distance(_touch->getStartLocation()) < s_distance)
		{
			++_keepTimes;
			if (_keepTimes <= 2)
			{
				auto c = Component::create();
				if (_keepTimes == 1)
				{
					c->setName(cc::cComponentMenuItemLongPress1);
				}
				else
				{
					_selectedItem->removeComponent(cc::cComponentMenuItemLongPress1);
					c->setName(cc::cComponentMenuItemLongPress);
				}
				_selectedItem->addComponent(c);
			}
			_selectedItem->activate();
		}
	}
}