#include "cDyeRender.h"


cDyeRender* cDyeRender::getInstance()
{
	static cDyeRender* s_colorRender = new cDyeRender();
	return s_colorRender;
}

void cDyeRender::load(eMod e, int jdx, const sDyes& dyes, std::vector<sPart>& parts)
{
	const auto& m = txtMod::getMods().at(e);
	const auto& jjs = m.jjs.at(jdx);
	parts.resize(jjs.size());
	forv(jjs, k)
	{
		auto& p = parts.at(k);
		p.partIdx = jjs.at(k);
		const auto& part = m.parts.at(p.partIdx);
		p.cid = part.color;
		p.uid = part.maps.at(eAct::stand);
	}
}



void cDyeRender::load(eMod e, int jdx, const sDyes& dyes)
{
	load(e, jdx, dyes, _parts);
	_dyes = dyes;
	_partIdx = 0;
	load();
}

void cDyeRender::load()
{
	const auto& p = _parts.at(_partIdx);
	cDye::toSections(_sections, p.cid);
	if (onLoad == nullptr)
	{
		return;
	}
	_spMatrixs.uid = p.uid;
	const auto& idxs = _dyes.get(p.partIdx);
	cDye::toMatrixs(_spMatrixs.matrixs, _sections, idxs);

	std::vector<sShow> shows;
	forv (_sections, k)
	{
		sShow show;
		show.total = _sections.at(k).matrix9s.size();
		show.idx = idxs.at(k) + 1;
		shows.push_back(show);
	}
	onLoad(_spMatrixs, shows);
}


void cDyeRender::swtichPart()
{
	int size = _parts.size();
	if (size <= 1)
	{
		return;
	}
	if (++_partIdx >= size)
	{
		_partIdx = 0;
	}
	cDye::toSections(_sections, _parts.at(_partIdx).cid);
	load();
}


void cDyeRender::resetPart()
{
	const auto& p = _parts.at(_partIdx);
	_dyes.resetZero(p.partIdx);
	load();
}



void cDyeRender::addMatrix(int sectionIdx, bool randIdx)
{
	if (sectionIdx < 0 || sectionIdx >= _sections.size())
	{
		return;
	}
	const auto& p = _parts.at(_partIdx);
	auto& idxs = _dyes.get(p.partIdx);
	auto& count = idxs.at(sectionIdx);
	int size = _sections.at(sectionIdx).matrix9s.size() - 1;
	if (randIdx)
	{
		count = cc::random(0, size);
	}
	else if (++count > size)
	{
		count = 0;
	}
	load();
}



void cDyeRender::apply()
{
	if (onApply == nullptr)
	{
		return;
	}
	onApply(_dyes);
}


void cDyeRender::apply(eMod e, int jdx, sDyes& dyes)
{
	std::vector<sPart> parts;
	load(e, jdx, dyes, parts);
	cDye::sSections sections;
	bool is0 = cc::random() < 0.1f;
	for (const auto& p : parts)
	{
		cDye::toSections(sections, p.cid);
		forv(sections, k)
		{
			auto& idxs = dyes.get(p.partIdx);
			auto& count = idxs.at(k);
			count = is0 ? 0 : cc::random(0U, sections.at(k).matrix9s.size() - 1);
		}
	}
}
