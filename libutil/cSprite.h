#pragma once
#include "_inc.h"
#include "ui/UIScale9Sprite.h"

class cSpriteCache
{
public:
	cSpriteCache();
	virtual ~cSpriteCache();
public:
	virtual bool load(ulong uid);
protected:
	virtual void load0();
	bool loadInner(int mid, int iframe);
	static void loadInner(Sprite* sprite, const sAlphaBmp* bmp, const sSpFrame& frame);
	virtual void loadInner(int mid, const sSpFrame& frame);
public:
	virtual bool isValid() const;
	virtual void free();
protected:
	ulong _uid = cSp::c0;
	sSpDecoder* _decoder = nullptr;
	int _iframe;
	friend class cSprite;
};

class cSprite1 : public Sprite, public cSpriteCache
{
public:
	static cSprite1* create(ulong uid = cSp::c0);

protected:
	bool init(ulong uid);
	void load0();
public:
	bool setFrame(int iframe);
	bool step();
protected:
	void loadInner(int mid, const sSpFrame& frame);
};

class Sprite9 : public ui::Scale9Sprite
{
public:
	static Sprite9* create(const std::string& filename);

protected:
	bool init(const std::string& filename);
	void load0();
public:
	virtual void set9(int e);
};


class cSprite9 : public Sprite9, public cSpriteCache
{
public:
	static cSprite9* create(ulong uid);
	bool setFrame(int iframe);
	void set9(int e);
protected:
	bool init(ulong uid);
	void loadInner(int mid, const sSpFrame& frame);

	int _9;
};

class cSpriteDelta
{
public:
	void setSpeed(float speed) { _speed = speed; }
protected:
	bool stepDelta(float delta);
	float _delta = 0;
	float _speed = 1;

};

class cSprite : public Node, public cSpriteDelta
{
public:
	cSprite();
	~cSprite();
protected:
	bool init(const sSps& sps);
	bool init(ulong uid);
public:
	static cSprite* create(const sSps& sps);

	static cSprite* create(ulong uid = cSp::c0);

	bool load(const sSps& sps);
	bool load(ulong uid);

	bool isValid() const;

	const sSpInfo* getInfo() const;

	void setBlend(eBlend e);

	eBlend getBlend() const;

	void setShadow(bool shadow);

	void play(int repeat = cRepeatMax, bool removeSelf = false);

protected:
	void freeCache();
public:
	void setFrame(int framePerDirection, bool update = true);

	void setDirection(int direction, bool update = true);
	void setDirection(bool isClockwise);
	int getDirection() const { return _direction; }
	// without textture when !visible
	void setFrameOnly(bool frameOnly);
protected:
	void updateFrame(int iframe);
	void updateFrame(int direction, int framePerDirection);
public:
	bool step();
protected:
	void update(float delta);

	struct sCache : public cSpriteCache 
	{
		int matrixid = 0; 
		eBlend blend = eBlend::normal;
		Sprite* sprite = nullptr;
		bool frameOnly = false;
		void free();
		void loadInner(int mid, const sSpFrame& frame);
		void load0();
	};
	std::vector<sCache> _caches;
	bool _shadow = false;
	cSprite1* _spriteShadow = nullptr;


	sSpInfo* _info = nullptr;

	int _frame = 0, _direction = 0, _iframe = 0;

	int _repeat = 0;
	static const int cRepeatMax;
	int _repeatMax = cRepeatMax;
	bool _isRemoveSelf = false;
};
