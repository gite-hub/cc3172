#include "uiMap.h"
#include "_ccu.h"
#include "cObject.h"
#include "audio/include/SimpleAudioEngine.h"

static uiMap* s_map = nullptr;
uiMap* ccu::getMap()
{
	return s_map;
}

void ccu::setMap(uiMap* map)
{
	s_map = map;
}

//////////////////////////////////////////////////////////////////////////
uiMap::uiMap()
{
	cMapFollow::getInstance()->setSpeedMax(5);
}

uiMap::~uiMap()
{
	cMapRender::getInstance()->setMap(nullptr);
	cMapFollow::getInstance()->setTarget(nullptr, nullptr);
}



bool uiMap::init()
{
	if (!Node::init())
	{
		return false;
	}

	this->addChild(_nodeMap = Node::create());
	this->addChild(_menuTrans = Menu::create(), 1);
	_menuTrans->setPosition(Vec2::ZERO);
	this->addChild(_nodeNpcs = Node::create(), 2);
	this->addChild(_nodeMask = Node::create(), 3);


	auto listener = EventListenerTouchOneByOne::create();
	// listener->setSwallowTouches(_swallowsTouches);
	listener->onTouchBegan = CC_CALLBACK_2(uiMap::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(uiMap::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(uiMap::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(uiMap::onTouchCancelled, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, _nodeNpcs);
	// _touchListener = listener;

	_selectObj = nullptr;
	_touchState = Menu::State::WAITING;

	this->scheduleUpdate();
	return true;
}


void uiMap::clearNpcs()
{
	if (_viewer != nullptr && _viewer->getParent() == _nodeNpcs)
	{

	}
	_nodeNpcs->removeAllChildren();
}


void uiMap::clearTrans()
{
	_menuTrans->removeAllChildren();
}

static void loadRand(sMap* pMap, int& x, int& y)
{
	int w = pMap->info.mw / cMapReader::c20, h = pMap->info.mh / cMapReader::c20;
	pMap->loadObstacles();
	do
	{
		x = cc::random(0, w);
		y = cc::random(0, h);
	} while (pMap->isObstacle(x, y));
}


void uiMap::load(eMap e)
{
	if (e == eMap::eNone || e == _emap)
	{
		return;
	}

	if (_viewer != nullptr)
	{
		_viewer->retain();
	}

	_nodeMap->removeAllChildren();
	_nodeMask->removeAllChildren();
	clearTrans();
	clearNpcs();
	_emap = e;
	const auto& m = txtMap::getMaps().at(e);

	cMapReader::getInstance()->freeCache(_cache);
	cMapRender::getInstance()->setMap(nullptr);

	_cache = cMapReader::getInstance()->getCache(m.mapid);
	auto pMap = _cache.pMap;
	pMap->loadMask();
	pMap->loadObstacles();

	cMapRender::getInstance()->setMap(pMap);
	this->setContentSize(Size(pMap->info.mw, pMap->info.mh));
	_nodeMap->setContentSize(_contentSize);
	_nodeMask->setContentSize(_contentSize);
	_nodeNpcs->setContentSize(_contentSize);
	_menuTrans->setContentSize(_contentSize);

	const auto& info = pMap->info;
	for (int k = 0, i, tag = 0, j; k < info.bh; ++k)
	{
		for (i = 0; i < info.bw; ++i, ++tag)
		{
			Node* node = Node::create();
			node->setTag(tag);
			node->setPosition(i * cMapReader::c320, (info.bh - 1 - k) * cMapReader::c240);
			_nodeMask->addChild(node);

			const auto& alphas = pMap->blocks.at(tag).alphas;
			for (j = alphas.size() - 1; j >= 0; --j)
			{
				Sprite* sprite = Sprite::create();
				const auto& a = alphas.at(j);
				sprite->setTag(j);
			//	sprite->setGlobalZOrder(ccu::zMapMask);
			//	sprite->setOpacity(0x88);
				sprite->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
				sprite->setPosition(a.bx, cMapReader::c240 - a.by);
				node->addChild(sprite);
				sprite->setVisible(false);
			}


			Sprite* sprite = Sprite::create();
			sprite->setContentSize(Size(cMapReader::c320, cMapReader::c240));
			sprite->setPosition(node->getPosition() + sprite->getContentSize() / 2);
			sprite->setTag(tag);
		//	sprite->setGlobalZOrder(ccu::zMap);
			_nodeMap->addChild(sprite);
			sprite->setVisible(false);
		}
	}

	float sw = cc::vsSize().width;
	float sh = cc::vsSize().height;
	cMapRender::getInstance()->onSize(sw, sh);
	cMapFollow::getInstance()->onSize(sw, sh);

	// 先load出map的大小再setTagrt
	cMapFollow::getInstance()->setTarget(this, _viewer);

	for (const auto& npc : m.npcs)
	{
		load(npc, false);
	}
	for (const auto& tr : m.transmits)
	{
		load(tr);
	}

	forv (m.mines, k)
	{
		for (int i = 0; i < 8; ++i)
		{
			sMod mod;
			mod.setMod(m.mines.at(k));
			cObject* obj = cObject::create(mod);
			obj->setTag(111);
			obj->setScript(toString("mine_%d", (int)mod.e));
			int x, y;
			loadRand(pMap, x, y);
			obj->setPosition(toPosition(x, y));
			obj->setName(txtMod::getMods().at(mod.e).name);
			_nodeNpcs->addChild(obj);
		}
	}

	if (_viewer != nullptr)
	{
		_nodeNpcs->addChild(_viewer);
		_viewer->scheduleUpdate();
		_viewer->release();
	}

	loadMusic();
}

void uiMap::load(int x20, int y20)
{
	int y2 = y20; // _contentSize.height / cMapReader::c20 - 1 - y20;
	this->setPosition(cc::vsCenter() - (Vec2(x20, y2) * cMapReader::c20));
	cMapFollow::correctPosition(this);

	if (_viewer != nullptr)
	{
		_viewer->setPosition(toPosition(x20, y20));
		_viewer->clearWays();
	}
}


void uiMap::load(const txtMap::sTransmit& transmit)
{
	MenuItem* menuItem = MenuItem::create();
	menuItem->setPosition(toPosition(transmit.x, transmit.y));

	cSprite* sprite = cSprite::create(ccu::uTransmit);
	menuItem->setContentSize(sprite->getContentSize());
	auto info = sprite->getInfo();
	sprite->setPosition(info->kx, info->height - info->ky);
//	sprite->setGlobalZOrder(ccu::zMapObj);
	sprite->play();
	menuItem->addChild(sprite);

	cLabel* label = cLabel::create(txtMap::getMaps().at(transmit.e).mapname, eFont::smal);
	label->enableShadow();
	label->setPosition(sprite->getContentSize() / 2);
	label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	label->setColor(ccu::cColorNpc);
	label->enableShadow();
	menuItem->addChild(label);

	menuItem->setCallback([this, transmit, menuItem](Ref*)
	{
		menuItem->retain();
		load(transmit.e);
		load(transmit.tx, transmit.ty);
		menuItem->release();
	});
	_menuTrans->addChild(menuItem);
}


void uiMap::load(const txtMap::sNpc& npc, bool smap)
{
	sMod mod;
	if (npc.mod == eMod::eNone)
	{
		mod.setMod(eMod::leiheizi);
	}
	else
	{
		mod.setMod(npc.mod);
	}
	cObject* obj = cObject::create(mod);
	if (npc.name.empty())
	{
		obj->setName(txtMod::getMods().at(npc.mod).name);
	}
	else
	{
		obj->setName(npc.name);
	}
	obj->setHead(txtMod::getMods().at(mod.e).head.at(eAct::dialog));
	obj->setScript(npc.script);
	obj->getBody()->setDirection(npc.direction);
	obj->setPosition(toPosition(npc.x, npc.y));
	_nodeNpcs->addChild(obj);
}

void uiMap::loadMusic()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	if (audio->isBackgroundMusicPlaying())
	{
		audio->stopBackgroundMusic();
	}
	if (_emap == eMap::eNone)
	{
		return;
	}
	audio->playBackgroundMusic(toString("%s%08X.mp3", (cPath::getRoot() + cPath::cMusic).c_str(), txtMap::getMaps().at(_emap).music).c_str(), true);
}


cocos2d::Vec2 uiMap::toPosition(int x20, int y20)
{
	return Vec2(x20 * cMapReader::c20 + cMapReader::c20 / 2, /*_contentSize.height - */y20 * cMapReader::c20 /*-*/+ cMapReader::c20 / 2);
}


void uiMap::toPosition(const Vec2& vMap, int& x20, int& y20)
{
	x20 = vMap.x / cMapReader::c20;
	y20 = (/*_contentSize.height - 1 - */vMap.y) / cMapReader::c20;
}


bool uiMap::isObstacle(int x20, int y20)
{
	if (_cache.pMap != nullptr && _cache.pMap->loadObstacles())
	{
//		y20 = _cache.pMap->info.bh * cMapReader::c12 - 1 - y20;
		y20 = _contentSize.height / cMapReader::c20 - 1 - y20;
		return _cache.pMap->isObstacle(x20, y20);
	}
	return true;
}


void uiMap::setViewer(cObject* viewer)
{
	cMapFollow::getInstance()->setTarget(this, viewer);
	if (viewer != _viewer)
	{
		if (_viewer != nullptr)
		{
			_viewer->removeFromParent();
		}
		if (viewer->getParent() == nullptr)
		{
			_nodeNpcs->addChild(viewer);
		}
		_viewer = viewer;
	}
}


static void moving(uiMap* uimap,  sMap* pMap, cObject* obj, int tx, int ty)
{
	int x, y;
	uimap->toPosition(obj->getPosition(), x, y);
	std::vector<cAstar::sXY> paths;
	pMap->search(x, y, tx, ty, paths);
	std::vector<Vec2> ways;
	Vec2 v;
	forv(paths, k)
	{
		const auto& xy = paths.at(k);
		v = uimap->toPosition(xy.x, xy.y);
		ways.push_back(v);
	}
	obj->setWays(ways);
}


void uiMap::update(float delta)
{
	cMapFollow::getInstance()->step();

	auto r = cMapRender::getInstance();
	static Vec2 v;
	v = cc::vsCenter();
	v = this->convertToNodeSpace(v);
	v.y = _contentSize.height - v.y;
	r->step(v, true);
	r->draw(_nodeMap);
	r->drawMask(_nodeMask);
	if (_viewer != nullptr)
	{
		_viewer->moving(5);
	}

	for (auto& node : _nodeNpcs->getChildren())
	{
		if (node == nullptr || node->getTag() != 111)
		{
			continue;
		}
		cObject* obj = (cObject*)node;
		if (obj->isWays())
		{
			obj->moving(3);
			continue;
		}
	}

	static int x = 0;
	if (++x >= _nodeNpcs->getChildrenCount())
	{
		x = 0;
	}
	auto obj = (cObject*)_nodeNpcs->getChildren().at(x);
	if (obj->getTag() == 111 && !obj->isWays())
	{
		int tx, ty;
		loadRand(_cache.pMap, tx, ty);
		moving(this, _cache.pMap, obj, tx, ty);
	}
}


bool uiMap::onTouchBegan(Touch* touch, Event* /*event*/)
{
	auto camera = Camera::getVisitingCamera();
	if (_touchState != Menu::State::WAITING || camera == nullptr)
	{
		return false;
	}

	_selectObj = getObject(touch);

	if (_selectObj != nullptr)
	{
		_selectObj->setLight(1);
		_touchState = Menu::State::TRACKING_TOUCH;

		return true;
	}

	cSprite* spriteClick = cSprite::create(ccu::uMapClick);
//	spriteClick->setGlobalZOrder(ccu::zMap);
	spriteClick->play(0, true);
	this->addChild(spriteClick);
	Vec2 v = touch->getLocation();
	v = spriteClick->getParent()->convertToNodeSpace(v);
	spriteClick->setPosition(v);

	if (_viewer != nullptr)
	{
		int tx, ty;
		toPosition(v, tx, ty);
		if (!_cache.pMap->isObstacle(tx, _cache.pMap->info.bh * cMapReader::c12 - 1 - ty))
		{
			moving(this, _cache.pMap, _viewer, tx, ty);
			if (!_viewer->isWays())
			{
				load(tx, ty);
			}
		}
	}

	return false;
}

void uiMap::onTouchEnded(Touch* touch, Event* /*event*/)
{
	CCASSERT(_touchState == Menu::State::TRACKING_TOUCH, "[Map ccTouchEnded] -- invalid state");
	this->retain();
	auto obj = getObject(touch);
	if (obj == _selectObj)
	{
		obj->runScript();
		if (obj->getTag() == 111)
		{
			obj->removeFromParent();
		}
	}
	_touchState = Menu::State::WAITING;
	this->release();



}

void uiMap::onTouchCancelled(Touch* /*touch*/, Event* /*event*/)
{
	CCASSERT(_touchState == Menu::State::TRACKING_TOUCH, "[Map ccTouchCancelled] -- invalid state");
	_touchState = Menu::State::WAITING;
}

void uiMap::onTouchMoved(Touch* touch, Event* /*event*/)
{
}

static cObject* getObject(Touch* touch, Node* node, const Camera *camera)
{
	Vec2 touchLocation = touch->getLocation();
	for (const auto &item : node->getChildren())
	{
		cObject* obj = dynamic_cast<cObject*>(item);
		if (nullptr == obj || false == obj->isVisible())
		{
			continue;
		}
		Rect rect;
		rect.size = obj->getContentSize();
		if (isScreenPointInRect(touchLocation, camera, obj->getWorldToNodeTransform(), rect, nullptr))
		{
			return obj;
		}
	}
	return nullptr;
}

cObject* uiMap::getObject(Touch *touch)
{
	auto camera = Camera::getVisitingCamera();
	auto obj = ::getObject(touch, _nodeNpcs, camera);
	if (obj != nullptr)
	{
		return obj;
	}
	return ::getObject(touch, _menuTrans, camera);
}
