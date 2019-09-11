#pragma once
#include "_inc.h"

class uiAttr : public Node
{
public:
	static uiAttr* create(int length, const std::string& field, const std::string& value = "");
	static uiAttr* create(const std::string& field, const std::string& value = "");
protected:
	bool init(int length, const std::string& field, const std::string& value);
public:
	void load(const std::string& field, const std::string& value);
	void load(const std::string& field, int value);
	void load(const std::string& field, u64 value);
	void load(const std::string& field);
	void setValue(const std::string& value);
	void setValue(int value);
	void setValue(int value, int valueMax);
	void setValue(u64 value);
	void setValue(u64 value, u64 valueMax);
	static int getSpriteX();
protected:
	int _spriteX;
	cLabel* _labelField = nullptr;
	cLabelEasy* _labelValue = nullptr;
public:
	static const int c4, cInterval;
};


class uiAttribute : public Node
{
public:
	static uiAttribute* create(bool hpmp, int interval, const sAttribute* attr = nullptr);
	static uiAttribute* create(bool hpmp, const sAttribute* attr = nullptr);
	static uiAttribute* create(int interval, const sAttribute* attr = nullptr);
	static uiAttribute* create(const sAttribute* attr = nullptr);
protected:
	bool init(bool hpmp, int interval, const sAttribute* attr);

public:
	void load(const sAttribute* attr);

	int getSpriteX() const;
protected:
	uiAttr* _attrHp = nullptr;
	uiAttr* _attrMp = nullptr;
	uiAttr* _attrHit = nullptr;
	uiAttr* _attrAtk = nullptr;
	uiAttr* _attrDef = nullptr;
	uiAttr* _attrMtk = nullptr;
	uiAttr* _attrMef = nullptr;
	uiAttr* _attrSpeed = nullptr;
	uiAttr* _attrAvoid = nullptr;
};


class uiPoint : public Node
{
public:
	static uiPoint* create(bool remain, int interval, const sPoint* point = nullptr);
	static uiPoint* create(bool remain, const sPoint* point = nullptr);
	static uiPoint* create(int interval, const sPoint* point = nullptr);
	static uiPoint* create(const sPoint* point = nullptr);
protected:
	bool init(bool remain, int interval, const sPoint* point);

public:
	void load(const sPoint* point);

protected:
	uiAttr* _attrBody = nullptr;
	uiAttr* _attrMana = nullptr;
	uiAttr* _attrStr = nullptr;
	uiAttr* _attrDex = nullptr;
	uiAttr* _attrAgi = nullptr;
	uiAttr* _attrRemain = nullptr;
};

class uiZz : public Node
{
public:
	static uiZz* create(const sZz* zz);
	static uiZz* create(int interval, const sZz* zz);
	static uiZz* create(bool is2, const sZz* zz);
	static uiZz* create(int interval, bool is2, const sZz* zz);
protected:
	virtual bool init(int interval, bool is2, const sZz* zz);

public:
	virtual void load(const sZz* zz);

protected:
	uiAttr* _attrAtk = nullptr;
	uiAttr* _attrDef = nullptr;
	uiAttr* _attrHp = nullptr;
	uiAttr* _attrMana = nullptr;
	uiAttr* _attrSpeed = nullptr;
	uiAttr* _attrAviod = nullptr;
	uiAttr* _attrGrow = nullptr;
};