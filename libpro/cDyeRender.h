#pragma once
#include "sDyes.h"

class cDyeRender
{
public:
	struct sPart
	{
		int partIdx;
		ulong uid, cid;
	};
	static cDyeRender* getInstance();
	static void load(eMod e, int jdx, const sDyes& dyes, std::vector<sPart>& parts);
	void load(eMod e, int jdx, const sDyes& dyes);
	void load();

	void swtichPart();
	void resetPart();
	void addMatrix(int sectionIdx, bool randIdx);

	void apply();
	static void apply(eMod e, int jdx, sDyes& dyes);
private:
	std::vector<sPart> _parts;
	sDyes _dyes;
	int _partIdx = 0;
	cDye::sSections _sections;
	sSp _spMatrixs;
public:
	struct sShow { int idx, total; };
	std::function<void(const sSp&, std::vector<sShow>&)> onLoad = nullptr;
	std::function<void(const sDyes& dyes)> onApply = nullptr;
};