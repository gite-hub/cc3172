#include "cSprite.h"

const int cSprite::cRepeatMax = INT_MAX;

cSpriteCache::cSpriteCache()
{
	_iframe = 0;
}

cSpriteCache::~cSpriteCache()
{
	free();
}

bool cSpriteCache::load(ulong uid)
{
	if (uid == _uid)
	{
		return true;
	}
	free();
	if (uid == cSp::c0)
	{
		_uid = uid;
		load0();
		return true;
	}
	_decoder = (sSpDecoder*)cSps::getInstance()->getDecoder(uid);
	if (_decoder == nullptr)
	{
		ccc_msgbox("0x%08X", uid);
		return false;
	}
	_uid = uid;
	return loadInner(0, _iframe);
}

void cSpriteCache::load0()
{

}

bool cSpriteCache::loadInner(int mid, int iframe)
{
	if (!isValid())
	{
		return false;
	}
	if (mid < 0 || iframe < 0 || iframe >= _decoder->info.framesCount)
	{
		return false;
	}
	_iframe = iframe;
	loadInner(mid, _decoder->info.frames[iframe]);
	return true;
}

void cSpriteCache::loadInner(Sprite* sprite, const sAlphaBmp* bmp, const sSpFrame& frame)
{
	if (bmp != nullptr)
	{
		sprite->setTexture((Texture2D*)bmp->texture);
		sprite->setTextureRect(Rect(0, 0, bmp->w, bmp->h));
	}
	sprite->setAnchorPoint(Vec2(frame.x * 1.0f / frame.w, 1 - (frame.y * 1.0f / frame.h)));
}



void cSpriteCache::loadInner(int mid, const sSpFrame& frame)
{

}


bool cSpriteCache::isValid() const
{
	return _uid != cSp::c0 && _decoder != nullptr;
}

void cSpriteCache::free()
{
	if (isValid())
	{
		cSps::getInstance()->freeDecoder(_uid);
	}
	_uid = cSp::c0;
	_decoder = nullptr;
	_iframe = 0;
}


//////////////////////////////////////////////////////////////////////////
cSprite1* cSprite1::create(ulong uid /* = cSp::c0 */)
{
	CREATE(cSprite1, uid);
}


bool cSprite1::init(ulong uid)
{
	if (!Sprite::init())
	{
		return false;
	}
	return load(uid);
}

void cSprite1::load0()
{
	setTexture(nullptr);
}

bool cSprite1::setFrame(int iframe)
{
	return cSpriteCache::loadInner(0, iframe);
}


bool cSprite1::step()
{
	if (!isValid())
	{
		return false;
	}
	int frame = _iframe + 1;
	if (frame >= _decoder->info.framesCount)
	{
		return true;
	}
	setFrame(frame);
	return false;
}


void cSprite1::loadInner(int mid, const sSpFrame& frame)
{
	cSpriteCache::loadInner(this, _decoder->getBitmap(mid, _iframe, eBlend::normal), frame);
}


//////////////////////////////////////////////////////////////////////////
Sprite9* Sprite9::create(const std::string& filename)
{
	CREATE(Sprite9, filename);
}

bool Sprite9::init(const std::string& filename)
{
	if (!ui::Scale9Sprite::initWithSpriteFrameName(filename))
	{
		return false;
	}
	set9(16);
	return true;
}

void Sprite9::load0()
{
	setTexture(nullptr);
}

void Sprite9::set9(int e)
{
	setInsetLeft(e);
	setInsetRight(e);
	setInsetTop(e);
	setInsetBottom(e);
}



//////////////////////////////////////////////////////////////////////////
cSprite9* cSprite9::create(ulong uid)
{
	CREATE(cSprite9, uid);
}



bool cSprite9::init(ulong uid)
{
	if (!ui::Scale9Sprite::init())
	{
		return false;
	}
	_9 = 16;
	load(uid);
	return true;
}

bool cSprite9::setFrame(int iframe)
{
	return cSpriteCache::loadInner(0, iframe);
}

void cSprite9::set9(int e)
{
	Sprite9::set9(_9 = e);
}


void cSprite9::loadInner(int mid, const sSpFrame& frame)
{
	auto size = _contentSize;
	auto bmp = _decoder->getBitmap(mid, _iframe, eBlend::normal);
	if (bmp != nullptr)
	{
		initWithTexture((Texture2D*)bmp->texture, Rect(0, 0, bmp->w, bmp->h));
		set9(_9);
	}
	if (!size.equals(Size::ZERO))
	{
		setContentSize(size);
	}
}



//////////////////////////////////////////////////////////////////////////
void cSprite::sCache::free()
{
	if (isValid())
	{
		_decoder->removeMatrix(matrixid);
		matrixid = 0;
	}
	cSpriteCache::free();
	if (sprite != nullptr)
	{
		sprite->removeFromParent();
		sprite = nullptr;
	}
}

void cSprite::sCache::loadInner(int mid, const sSpFrame& frame)
{
	if (sprite == nullptr)
	{
		return;
	}
	const sAlphaBmp* bmp = nullptr;
	if (!frameOnly || cc::isVisible(sprite->getParent()))
	{
		bmp = _decoder->getBitmap(mid, _iframe, blend);
	}
	cSpriteCache::loadInner(sprite, bmp, frame);
}


void cSprite::sCache::load0()
{
	if (sprite != nullptr)
	{
		sprite->setTexture(nullptr);
	}
}


//////////////////////////////////////////////////////////////////////////

bool cSpriteDelta::stepDelta(float delta)
{
	static float s_delta = 0.12f;
	delta = (_delta += delta * _speed) - s_delta;
	if (_delta >= s_delta)
	{
		_delta -= s_delta;
	}
	return delta > 0;
}


//////////////////////////////////////////////////////////////////////////
cSprite::cSprite()
{
}

cSprite::~cSprite()
{
	freeCache();
}

cSprite* cSprite::create(const sSps& sps)
{
	CREATE(cSprite, sps)
}


cSprite* cSprite::create(ulong uid /* = cSp::c0 */)
{
	CREATE(cSprite, uid)

}

bool cSprite::init(const sSps& sps)
{
	if (!Node::init())
	{
		return false;
	}
	load(sps);
	return true;
}


bool cSprite::init(ulong uid)
{
	sSps sps(1);
	sps.at(0).uid = uid;
	return init(sps);
}

bool cSprite::load(const sSps& sps)
{
	if (_caches.size() == 1 && sps.size() == 1)
	{
		auto& c = _caches.at(0);
		const auto& sp = sps.at(0);
		if (c._uid == sp.uid)
		{
			if (!sp.matrixs.empty() && c.isValid())
			{
				int m = 0;
				forv(sp.matrixs, k)
				{
					m += sp.matrixs.at(k).value;
				}
				if (m != c.matrixid)
				{
					c._decoder->removeMatrix(c.matrixid);
					c.matrixid = c._decoder->getMatrix(sp.matrixs);
					updateFrame(_direction, _frame);
				}
			}
			return true;
		}
	}
	freeCache();
	if (sps.empty() || (sps.size() == 1 && sps.at(0).uid == cSp::c0))
	{
		return true;
	}

	_caches.resize(sps.size());
	forv(sps, k)
	{
		const auto& sp = sps.at(k);
		// 为什么 push_back(sCache()) 会被free??
		auto& c = _caches.at(k);
		if (!c.load(sp.uid) || !c.isValid())
		{
			_caches.erase(_caches.begin() + k);
			continue;
		}
		c.matrixid = c._decoder->getMatrix(sp.matrixs);
		this->addChild(c.sprite = Sprite::create());
		if (_info == nullptr)
		{
			_info = &c._decoder->info;
			setContentSize(Size(_info->width, _info->height));
			setAnchorPoint(Vec2(_info->kx * 1.0f / _info->width, 1 - (_info->ky * 1.0f / _info->height)));
		}
		c.sprite->setPosition(_info->kx, _info->height - _info->ky);
	}
	if (_caches.empty())
	{
		return true;
	}
	if (_shadow)
	{
		setShadow(true);
	}
	else
	{
		for (auto& c : _caches)
		{
			c.sprite->updateOrderOfArrival();
		}
	}
	updateFrame(0);
	return true;
}


bool cSprite::load(ulong uid)
{
	sSps sps(1);
	sps.at(0).uid = uid;
	return load(sps);
}

bool cSprite::isValid() const
{
	return _info != nullptr;
}


const sSpInfo* cSprite::getInfo() const
{
	return _info;
}


void cSprite::setBlend(eBlend e)
{
	for (auto& c : _caches)
	{
		c.blend = e;
	}
}

eBlend cSprite::getBlend() const
{
	for (auto& c : _caches)
	{
		return c.blend;
	}
	return eBlend::normal;
}

void cSprite::setShadow(bool shadow)
{
	_shadow = shadow;
	if (shadow)
	{
		if (_spriteShadow == nullptr)
		{
			this->addChild(_spriteShadow = cSprite1::create(ccu::uShadow));
			if (_info != nullptr)
			{
				_spriteShadow->setPosition(_info->kx, _info->height - _info->ky);
			}
			for (auto& c : _caches)
			{
				if (c.sprite != nullptr)
				{
					c.sprite->updateOrderOfArrival();
				}
			}
			return;
		}
		if (_info != nullptr)
		{
			_spriteShadow->setPosition(_info->kx, _info->height - _info->ky);
		}
	}
	if (!shadow && _spriteShadow != nullptr)
	{
		_spriteShadow->setVisible(shadow);
	}
}

void cSprite::freeCache()
{
	for (auto& c : _caches)
	{
		c.free();
	}
	_caches.clear();
	_info = nullptr;
	_iframe = 0;
}


void cSprite::setFrame(int framePerDirection, bool update /* = true */)
{
	if (getInfo() == nullptr)
	{
		return;
	}
	if (framePerDirection >= getInfo()->framesCountPerDirection)
	{
		framePerDirection = getInfo()->framesCountPerDirection - 1;
	}
	if (update)
	{
		updateFrame(_direction, framePerDirection);
	}
}


void cSprite::setDirection(int direction, bool update /* = true */)
{
	if (getInfo() == nullptr)
	{
		return;
	}
	if (direction >= getInfo()->directionsCount)
	{
		direction = getInfo()->directionsCount - 1;
	}
	if (update)
	{
		updateFrame(direction, _frame);
	}
}


void cSprite::setDirection(bool isClockwise)
{
	if (getInfo() == nullptr)
	{
		return;
	}
	int dc = getInfo()->directionsCount;
	int d;
	if (dc == 8)
	{
		d = cDirection::getDirectionRound8(_direction, isClockwise);
	}
	else if (dc == 4)
	{
		d = cDirection::getDirectionRound4(_direction, isClockwise);
	}
	else if (isClockwise)
	{
		if (_direction >= dc - 1)
		{
			d = 0;
		}
		else
		{
			d = _direction + 1;
		}
	}
	else
	{
		if (_direction <= 0)
		{
			d = dc - 1;
		}
		else
		{
			d = _direction - 1;
		}
	}
	updateFrame(d, _frame);
}


void cSprite::setFrameOnly(bool frameOnly)
{
	for (auto& c : _caches)
	{
		c.frameOnly = frameOnly;
	}
}

void cSprite::updateFrame(int direction, int framePerDirection)
{
	if (direction == _direction && framePerDirection == _frame)
	{
		return;
	}
	_direction = direction;
	_frame = framePerDirection;
	_iframe = direction * getInfo()->framesCountPerDirection + framePerDirection;
	updateFrame(_iframe);
}


void cSprite::updateFrame(int iframe)
{
	if (getInfo() == nullptr)
	{
		return;
	}
	for (auto& c : _caches)
	{
		c.cSpriteCache::loadInner(c.matrixid, iframe);
	}
}


bool cSprite::step()
{
	if (getInfo() == nullptr)
	{
		return false;
	}
	int framePerDirection = _frame + 1;
	if (framePerDirection >= getInfo()->framesCountPerDirection)
	{
		return true;
	}
	updateFrame(_direction, framePerDirection);
	return false;
}



void cSprite::play(int repeat /*= cRepeatMax*/, bool removeSelf /*= false*/)
{
	_repeat = 1;
	_repeatMax = repeat;
	_isRemoveSelf = removeSelf;
	scheduleUpdate();
}


void cSprite::update(float delta)
{
	if (!stepDelta(delta) || !step())
	{
		return;
	}
	if (_repeat >= _repeatMax)
	{
		unscheduleUpdate();
		if (_isRemoveSelf)
		{
			this->removeFromParent();
		}
	}
	else
	{
		updateFrame(_direction, 0);
		++_repeat;
	}
}
