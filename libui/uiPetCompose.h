#pragma once
#include "uiAttr.h"
#include "uiPetSki.h"

class uiPetCompose1 : public Node
{
public:
	CREATE_FUNC(uiPetCompose1);

protected:
	bool init();

public:
	void load(const sPet* pet);

	void setRole(sRole* role) { _role = role; }
	void check();
	void clear();

protected:
	sRole* _role = nullptr;
	int _select;
	const sPet* _pet = nullptr;

	cButton* _button = nullptr;
	cButton* _buttonAdd = nullptr;

	uiZz* _zz = nullptr;
	uiPetSki* _ski = nullptr;

friend class uiPetCompose;
};


class uiPetCompose : public Node
{
public:
	static uiPetCompose* create(sRole* role);

protected:
	bool init(sRole* role);

public:
	void load(sRole* role);
	void check();
	void clear();
protected:
	sRole* _role = nullptr;

	cButton* _button = nullptr;
	uiPetCompose1* _left = nullptr;
	uiPetCompose1* _right = nullptr;

public:
	// Ö¸Õë ¿É¿Ø Õ½¶· 
	std::function<bool(const sRole*, int, int)> onCompose = nullptr;
};