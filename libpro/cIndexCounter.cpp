#include "cIndexCounter.h"
#include "_inc.h"

sUnique::sUnique()
{
	unique = cc::_1;
}

void sUnique::save() const
{
	sStream& sav = *cSave::getSave();
	sav << unique << s_space;
}

void sUnique::load()
{
	sStream& sav = *cSave::getLoad();
	sav >> unique;
}

//////////////////////////////////////////////////////////////////////////
cIndexCounter* cIndexCounter::getInstance()
{
	static cIndexCounter* s_autoAdd = new cIndexCounter();
	return s_autoAdd;
}

int cIndexCounter::getValue(int add)
{
	int value = _value;
	_value += add;
	return value;
}

void cIndexCounter::setValue(int value)
{
	_value = value;
}

cIndexCounter::cIndexCounter()
{
	_value = 0;
}

