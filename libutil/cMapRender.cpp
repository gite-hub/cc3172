#include "cMapRender.h"


cMapRender* cMapRender::getInstance()
{
	static cMapRender* s_mapRender = new cMapRender();
	return s_mapRender;
}

static const int c320 = cMapReader::c320, c240 = cMapReader::c240, c12 = cMapReader::c12, c16 = cMapReader::c16, c20 = cMapReader::c20;

void cMapRender::getScrew(int x0, int y0, int row, int cel, int bw, int bh, int& x1, int& y1, int& x2, int& y2)
{
	x1 = std::max(0, x0 - row);
	y1 = std::max(0, y0 - cel);
	x2 = std::min(bw, x0 + row + 1);
	y2 = std::min(bh, y0 + cel + 1);

// 	if (x0 == bw - 1)
// 	{
// 		x1 = std::max(0, x0 - row - 1);
// 	}
// 	else if (y0 == bh - 1)
// 	{
// 		y1 = std::max(0, y0 - cel - 1);
// 	}
}


int cMapRender::forScrew(int x0, int y0, bool limit)
{
	int idx = y0 * _bw + x0;
	const auto& bmps = _pMap->blocks;
	if (!bmps.at(idx).isValid())
	{
		return idx;
	}
	static const int ds[][2] = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };
	int x1 = limit ? _x1 : 0;
	int x2 = limit ? _x2 : _bw;
	int y1 = limit ? _y1 : 0;
	int y2 = limit ? _y2 : _bh;

	bool isL = false;
	bool isR = false;
	bool isU = false;
	bool isD = false;
	bool isok = false;
	for (int n = 0;; ++n)
	{
		for (int i = 0; i < (n / 2 + 1); ++i)
		{
			x0 += ds[n % 4][0];
			y0 += ds[n % 4][1];

			if (x0 < x1)
			{
				isL = true;
				continue;
			}
			if (x0 >= x2)
			{
				isR = true;
				continue;
			}

			if (y0 < y1)
			{
				isD = true;
				continue;
			}
			if (y0 >= y2)
			{
				isU = true;
				continue;
			}

			idx = y0 * _bw + x0;
			if (!bmps.at(idx).isValid())
			{
				isok = true;
				break;
			}
		}
		if (isok)
		{
			break;
		}
		if (isL && isR && isU && isD)
		{
			break;
		}
	}
	if (isok)
	{
		return idx;
	}
	return -1;
}



void cMapRender::setMap(sMap* pMap)
{
	_pMap = pMap;
	if (_pMap == nullptr)
	{
		reset();
		_x2 = _y2 = 0;
	}
	else 
	{
		_bw = _pMap->info.bw;
		_bh = _pMap->info.bh;
	}
}

void cMapRender::reset()
{
	_alphas = nullptr;
	_alpha = nullptr;
	_flag = _mask = -1;
	_isLoaded = false;
}

void cMapRender::onSize(float sw, float sh)
{
	_row = std::ceil(sw / c320);
	_cel = std::ceil(sh / c240);
}


bool cMapRender::step(const cocos2d::Vec2& vCenter, bool limit)
{
	if (_pMap == nullptr)
	{
		return false;
	}
	_x320 = std::max(0, (int)vCenter.x / c320);
	_y240 = std::max(0, (int)vCenter.y / c240);
	_x320 = std::min(_x320, _bw - 1);
	_y240 = std::min(_y240, _bh - 1);
	getScrew(_x320, _y240, _row, _cel, _bw, _bh, _x1, _y1, _x2, _y2);
	if (_isLoaded)
	{
		return false;
	}
	auto& info = _pMap->info;
	if (_flag == -1 && _mask == -1)
	{
		_x320 = std::max(0, (int)vCenter.x / c320);
		_y240 = std::max(0, (int)vCenter.y / c240);
		_x320 = std::min(_x320, _bw - 1);
		_y240 = std::min(_y240, _bh - 1);
		getScrew(_x320, _y240, _row, _cel, _bw, _bh, _x1, _y1, _x2, _y2);
		_flag = forScrew(_x320, _y240, limit);
	}
	else if (_mask == -1)
	{
		if (_pMap->getBitmap(_flag) != nullptr)
		{
			_alphas = &_pMap->blocks.at(_flag).alphas;
			if (_alphas->empty())
			{
				if (_pMap->isLoaded())
				{
					_isLoaded = true;
				}
				else
				{
					reset();
				}
			}
			else 
			{
				_mask = 0;
				_alpha = &_alphas->at(0);
			}
		}

	}
	else 
	{
		auto m = _pMap->masks + _alpha->maskIdx;
		if (m->decode((uchar*)_pMap->ptr + *(_pMap->maskOffs + _alpha->maskIdx)))
		{
			_alpha->getAlpha(_pMap->blocks.at(_flag).image->getData(), *m);
		}
		if((++_mask) == _alphas->size())
		{
			if (_pMap->isLoaded())
			{
				_isLoaded = true;
			}
			else
			{
				reset();
			}
		}
		else
		{
			_alpha = &_alphas->at(_mask);
		}
	}
	return true;
}


void cMapRender::draw(Node* node)
{
	if (_pMap == nullptr)
	{
		return;
	}
	int idx;
	Sprite* sprite = nullptr;
	for (int k = _y1; k < _y2; ++k)
	{
		bool broken = false;
		for (int i = _x1; i < _x2; ++i)
		{
			idx = k * _bw + i;
			const auto& block = _pMap->blocks.at(idx);
			if (!block.isValid())
			{
				continue;
			}
			sprite = (Sprite*)node->getChildByTag(idx);
			if (sprite == nullptr)
			{
				continue;
			}
			if (!sprite->isVisible())
			{
				sprite->setVisible(true);
 				sprite->setTexture(_pMap->getBitmap(idx));
				sprite->setTextureRect(Rect(0, 0, c320, c240));
				bool broken = true;
				break;
			}
		}
		if (broken)
		{
			break;
		}
	}
}


void cMapRender::drawMask(Node* node)
{
	if (_pMap == nullptr)
	{
		return;
	}
	int idx;
	Node* nodeBlock = nullptr;
	Sprite* sprite = nullptr;
	for (int k = _y1; k < _y2; ++k)
	{
		bool broken = false;
		for (int i = _x1; i < _x2; ++i)
		{
			idx = k * _bw + i;
			const auto& ms = _pMap->blocks.at(idx).alphas;
			if (ms.empty())
			{
				continue;
			}
			nodeBlock = node->getChildByTag(idx);
			if (node == nullptr)
			{
				continue;
			}
			bool broken2 = false;
			forv (ms, j)
			{
				const auto& m = ms.at(j);
				if (!m.isValid())
				{
					continue;
				}
				sprite = (Sprite*)nodeBlock->getChildByTag(j);
				if (sprite == nullptr)
				{
					continue;
				}
				if (!sprite->isVisible())
				{
					sprite->setVisible(true);
					sprite->setTexture(m.texture);
					sprite->setTextureRect(Rect(0, 0, m.w, m.h));
					broken2 = true;
					break;
				}
			}
			if (broken2)
			{
				broken = true;
				break;
			}
		}
		if (broken)
		{
			break;
		}
	}
}
