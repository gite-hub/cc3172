#pragma once
#include "_inc.h"

// È¾É«·½°¸
class sDyes
{
public:
	sDyes();
	void reset(int partsCount);
	void resetZero();
	void resetZero(cDye::sIdxs& idxs);
	void resetZero(int part);

	const cDye::sIdxs& get(int part) const;
	cDye::sIdxs& get(int part);

	void save()const;
	void load();
private:
	std::vector<cDye::sIdxs> _idxs;
public:
	static const int c4;
};

