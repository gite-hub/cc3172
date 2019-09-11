#pragma once
#include "uiMod.h"
#include "uiAttr.h"
#include "uiPetSki.h"
#include "uiPad.h"

class cSee /*: public Node*/
{
// public:
// 	static cSee* create(bool name);

protected:
//	bool init(bool name);
	bool init(Node* parent, bool name);

public:
	void load(const sPet* pet);

protected:
	cLabel* _labelName = nullptr;
	uiMod* _mod = nullptr;
	uiAttribute* _attr = nullptr;
	uiPoint* _point = nullptr;
	uiZz* _zz = nullptr;
	uiPetSki* _ski = nullptr;
};


class uiSee : public uiPad, public cSee
{
public:
	CREATE_FUNC(uiSee);

protected:
	bool init();

public:
	void load(const sPet* pet);
};