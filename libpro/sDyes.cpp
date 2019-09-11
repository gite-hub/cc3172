#include "sDyes.h"

const int sDyes::c4 = 4;
sDyes::sDyes()
{
	reset(1);
}

void sDyes::reset(int partsCount)
{
	while (_idxs.size() > partsCount)
	{
		_idxs.pop_back();
	}
	while (_idxs.size() < partsCount)
	{
		_idxs.push_back(cDye::sIdxs());
		resetZero(_idxs.back());
	}
}

void sDyes::resetZero()
{
	for (auto& idxs : _idxs)
	{
		resetZero(idxs);
	}
}

void sDyes::resetZero(cDye::sIdxs& idxs)
{
	idxs.resize(c4);
	std::fill(idxs.begin(), idxs.end(), 0);
}



void sDyes::resetZero(int part)
{
	resetZero(_idxs.at(part));
}

const cDye::sIdxs& sDyes::get(int part) const
{
	return _idxs.at(part);
}

cDye::sIdxs& sDyes::get(int part)
{
	return _idxs.at(part);
}



void sDyes::save()const
{
	sStream& sav = *cSave::getSave();
	sav << _idxs.size() << s_space;
	forr(_idxs, k)
	{
		const auto& idxs = _idxs.at(k);
		forr(idxs, i)
		{
			sav << idxs[i] << s_space;
		}
	}
}

void sDyes::load()
{
	sStream& sav = *cSave::getLoad();
	int size;
	sav >> size;
	_idxs.resize(size);
	forr(_idxs, k)
	{
		auto& idxs = _idxs.at(k);
		forr(idxs, i)
		{
			sav >> idxs[i];
		}
	}
}


