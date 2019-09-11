#pragma once
#include "uiAttr.h"
#include "uiPetSki.h"


class uiPetAttr : public Node
{
public:
	static uiPetAttr* create(sPet* pet);

protected:
	bool init(sPet* pet);

public:
	void load(sPet* pet);

protected:
	sPet* _pet = nullptr;
	uiAttr* _attrHp = nullptr;
	uiAttr* _attrMp = nullptr;
	uiAttribute* _attr = nullptr;
	uiPoint* _point = nullptr;
	uiAttr* _attrExp = nullptr;

	Node* _node1 = nullptr;
	Node* _node2 = nullptr;
	uiPetSki* _ski = nullptr;
	uiZz* _zz = nullptr;
public:
	// ÷∏’Î ’Ω∂∑
	std::function<bool(const sPet*, const sPoint&)> onPoint = nullptr;
};