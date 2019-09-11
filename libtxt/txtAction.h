#pragma once
#include "_inc.h"
#include "eAct.h"

class txtAction
{
public:
	typedef std::map<eAct, ulong> sAction;

	static void insert(sAction& act, ulong stand, ulong  walk, ulong  fight, ulong  go, ulong  atk, ulong  atk2, ulong  magic, ulong  def, ulong  suffer, ulong  dead, ulong  back, bool check0 = false);

	static void insert(sAction& act, ulong  fight, ulong  go, ulong  atk, ulong  atk2, ulong  magic, ulong  def, ulong  suffer, ulong  dead, ulong  back, bool check0 = false);

	static void insert(sAction& act, ulong stand, ulong  walk);

	static void insertHead(sAction& act, ulong head, ulong  dialog);

	static void insert(sAction& act, ulong  atk, ulong  atk2, ulong  suffer, ulong  magic, ulong  def, ulong  dead);
};