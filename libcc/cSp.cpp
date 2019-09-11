#include "cSp.h"

#define  ccc_wdf 1

cWdf* cWdf::getColor()
{
	static cWdf* s_color = new cWdf();
	return s_color;
}

cWdf* cWdf::getMp3()
{
	static cWdf* s_mp3 = new cWdf();
	return s_mp3;
}

cWdf* cWdf::getWav()
{
	static cWdf* s_wav = new cWdf();
	return s_wav;
}


cWdf::~cWdf()
{
	if (_file != nullptr)
	{
		fclose(_file);
	}
	_file = nullptr;
}


bool cWdf::load(const std::string &filename, bool onlyCheck /* = false */)
{
#if ccc_wdf
	_file = fopen(filename.c_str(), "rb");
	if (_file == nullptr)
	{
		return false;
	}
	uint offset;
	fread(&offset, 1, 4, _file);
	if (offset != 'WDFP') // 0x57444650
	{
		fclose(_file);
		return false;
	}
	if (!onlyCheck)
	{
		fread(&_indexsCount, 1, 4, _file);
		fread(&offset, 1, 4, _file);

		_indexs = new sIndex[_indexsCount];
		fseek(_file, offset, SEEK_SET);

		auto indexs = _indexs;
		for (int k = 0; k < _indexsCount; ++k, ++indexs)
		{
			fread(indexs, 1, 12, _file);
			// space
			fseek(_file, 4, SEEK_CUR);
		}
	}
#endif
	_filename = filename;
	return true;
}



const cWdf::sIndex* cWdf::search2(ulong uid)
{
	uint begin = 0, end = _indexsCount - 1, middle;

	if (uid < (_indexs + begin)->uid || uid >(_indexs + end)->uid)
	{
		return nullptr;
	}

	auto _middle = _indexs;
	while (begin <= end)
	{
		middle = (begin + end) >> 1;
		_middle = _indexs + middle;
		if (_middle->uid == uid)
		{
			return _middle;
		}
		else if (_middle->uid < uid)
		{
			begin = middle + 1;
		}
		else
		{
			end = middle - 1;
		}
	}
	return nullptr;
}


const char* cWdf::getData(const sIndex* idx, bool isJudgeSp /*= false*/)
{
	if (isJudgeSp)
	{
		static char ptr2[2];
		fseek(_file, idx->offset, SEEK_SET);
		fread(ptr2, 1, 2, _file);
		if (*(ushort*)ptr2 != 0x5053)
		{
			return nullptr;
		}
	}
	auto ptr = new char[idx->size];
	fseek(_file, idx->offset, SEEK_SET);
	fread(ptr, 1, idx->size, _file);
	return ptr;
}

const char* cWdf::getData(ulong uid, int& size)
{
	if (_indexs == nullptr)
	{
		return nullptr;
	}
	auto idx = search2(uid);
	if (idx == nullptr)
	{
		return nullptr;
	}
	size = idx->size;
	return getData(idx);
	return getData(_filename, uid, size, false);
}




//////////////////////////////////////////////////////////////////////////
bool sSpFrame::isValid() const
{
	return w > 0 && h > 0;
}

//////////////////////////////////////////////////////////////////////////
sSpInfo::~sSpInfo()
{
	ccc_delete_array(frames);
}

sSpInfo::operator bool() const
{
	return frames != nullptr && directionsCount > 0 && framesCountPerDirection > 0 && framesCount > 0 && width > 0 && height > 0;
}



//////////////////////////////////////////////////////////////////////////
sSpDecode::sSpDecode()
{
}

sSpDecode::~sSpDecode()
{
	ccc_delete_array(palIdxs);
	ccc_delete_array(alphas);
}

bool sSpDecode::isValid() const
{
	return palIdxs != nullptr && alphas != nullptr && w > 0 && h > 0;
}


void sSpDecode::decode(int _w, int _h, const uchar* ptrHead, ulong offs)
{
	w = _w, h = _h;
	palIdxs = new uchar[w * h];
	alphas = new uchar[w * h];
	memset(alphas, 0, w * h);

	auto li = (ulong*)(ptrHead + offs + 16);
	auto _palIdxs = palIdxs;
	auto _alphas = alphas;
	auto palIdx = _palIdxs;
	auto alpha = _alphas;
	auto ptr = ptrHead;
	bool isgh = true, parity; //奇偶性
	for (int k = 0; k < h; ++k, ++li, _palIdxs += w, _alphas += w)
	{
		ptr = ptrHead + offs + *li;
		palIdx = _palIdxs;
		alpha = _alphas;
		parity = ((k % 2) == 1);
		for (int ix = 0; ix < w;)
		{
			static uchar s_dataCheck;
			s_dataCheck = *ptr;
			if (s_dataCheck == 0)// 像素行结束  
			{
				break;
			}
			++ptr;
			static uint s_size, s_size2;
			static uchar s_dataWait, s_alphaWait;
			switch (s_dataCheck & 0xC0)
			{
			case 0x00: //Bit7-8=00
				if (isgh && parity)
				{
					isgh = false;
				}
				if (s_dataCheck & 0x20)// 若Bit6=1
				{
					s_alphaWait = (s_dataCheck & 0x1F);// Bit1-5
					if (s_alphaWait)
					{
						*palIdx = *ptr;
						*alpha = s_alphaWait;
					}
					++ptr;
					++ix;
					++palIdx;
					++alpha;
				}
				else
				{
					s_alphaWait = *ptr;
					if (s_alphaWait)
					{
						s_size = (s_dataCheck & 0x1F);
						s_dataWait = *(ptr + 1);
						s_size2 = std::min(s_size, (uint)(w - ix));
						memset(palIdx, s_dataWait, s_size2);
						memset(alpha, s_alphaWait, s_size2);
						ix += s_size;
						palIdx += s_size;
						alpha += s_size;
					}
					ptr += 2;

				}
				break;
			case 0x40: //Bit7-8=01
				if (isgh && parity)
				{
					isgh = false;
				}
				s_size = (s_dataCheck & 0x3f);
				s_size2 = std::min(s_size, (uint)(w - ix));
				memcpy(palIdx, ptr, s_size2);
				memset(alpha, 0x20, s_size2);
				ptr += s_size;
				ix += s_size;
				palIdx += s_size;
				alpha += s_size;
				break;
			case 0x80: //Bit7-8=10
				if (isgh && parity)
				{
					isgh = false;
				}
				s_size = (s_dataCheck & 0x3F);
				s_dataWait = *ptr;
				++ptr;
				s_size2 = std::min(s_size, (uint)(w - ix));
				memset(palIdx, s_dataWait, s_size2);
				memset(alpha, 0x20, s_size2);
				ix += s_size;
				palIdx += s_size;
				alpha += s_size;
				break;
			default:
				s_size = (s_dataCheck & 0x3F);
				if (0 == s_size)
				{
					ptr += 2;
				}
				else
				{
					ix += s_size;
					palIdx += s_size;
					alpha += s_size;
				}
				break;
			}
		}
	}
	if (isgh)
	{
		palIdx = palIdxs;
		alpha = alphas;
		for (int k = 0; k < h - 1; k += 2, palIdx += w * 2, alpha += w * 2)
		{
			memcpy(palIdx + w, palIdx, w);
			memcpy(alpha + w, alpha, w);
		}
	}
}


const ulong*  sSpDecode::getBitmap(const s565* palettes, eBlend e)
{
	auto palIdx = palIdxs;
	auto alpha = alphas;
	auto palette = palettes;

	auto pA = alpha;
	auto pIdx = palIdx;

	ulong* s8s = new ulong[w * h];
	memset(s8s, 0, sizeof(ulong) * w * h);
	auto s88 = s8s;
	auto s8 = s88;
	if (e == eBlend::normal)
	{
		for (int k = 0; k < h; ++k, palIdx += w, alpha += w, s88 += w)
		{
			pA = alpha;
			pIdx = palIdx;
			s8 = s88;
			for (int i = 0; i < w; ++i, ++pIdx, ++pA, ++s8)
			{
				if (*pA == 0)
				{
					continue;
				}
				*s8 = palette[*pIdx].to8888(*pA);
			}
		}
		return s8s;
	}
	s565 pD;
	if (e == eBlend::light)
	{
		for (int k = 0; k < h; ++k, palIdx += w, alpha += w, s88 += w)
		{
			pA = alpha;
			pIdx = palIdx;
			s8 = s88;
			for (int i = 0; i < w; ++i, ++pIdx, ++pA, ++s8)
			{
				if (*pA == 0)
				{
					continue;
				}
				pD = palette[*pIdx];
				pD.toLight();
				*s8 = pD.to8888(*pA);
			}
		}
		return s8s;
	}
	for (int k = 0; k < h; ++k, palIdx += w, alpha += w, s88 += w)
	{
		pA = alpha;
		pIdx = palIdx;
		s8 = s88;
		for (int i = 0; i < w; ++i, ++pIdx, ++pA, ++s8)
		{
			if (*pA == 0)
			{
				continue;
			}
			pD = palette[*pIdx];
			pD.toBlick();
			*s8 = pD.to8888(*pA);
		}
	}
	return s8s;
}



//////////////////////////////////////////////////////////////////////////
sAlphaBmp::sAlphaBmp()
{

}

sAlphaBmp::~sAlphaBmp()
{
//	ccc_delete_array(datas);
	freeTexture(texture);
}

bool sAlphaBmp:: isValid() const
{
	return /*datas*/texture != nullptr && w > 0 && h > 0;
}


//////////////////////////////////////////////////////////////////////////
sSpDecoder::sSpDecoder()
{

}

sSpDecoder::~sSpDecoder()
{
	ccc_delete_array(decodes);
	for (auto& palette : palettes)
	{
		delete[] palette.second.palette;
	}
}

bool sSpDecoder::isValid()  const
{
	return decodes != nullptr && palette != nullptr && offsets != nullptr && info;
}



void sSpDecoder::load(const char* ptr)
{
	info.directionsCount = *(ushort*)(ptr + 4);
	info.framesCountPerDirection = *(ushort*)(ptr + 6);
	info.width = *(ushort*)(ptr + 8);
	info.height = *(ushort*)(ptr + 10);
	info.kx = *(short*)(ptr + 12);
	info.ky = *(short*)(ptr + 14);

	ushort head = *(ushort*)(ptr + 2);
	head += 4;
	ptr += head;
	palette = (s565*)ptr;

	int total = info.framesCount = info.directionsCount * info.framesCountPerDirection;
	offsets = (ulong*)(ptr + 512);
	info.frames = new sSpFrame[total];
	decodes = new sSpDecode[total];

	auto frame = info.frames;
	auto offs = offsets;
	for (int k = 0; k < total; ++k, ++frame, ++offs)
	{
		if (*offs == 0)
		{
			continue;
		}
		memcpy(frame, (ptr + *offs), 16);
	}
}


bool sSpDecoder::decode(int iframe)
{
	auto decs = decodes + iframe;
	if (decs->isValid())
	{
		return true;
	}
	const auto& frame = info.frames + iframe;
	if (!frame->isValid())
	{
		return false;
	}
	decs->decode(frame->w, frame->h, (uchar*)palette, *(offsets + iframe));
	return decs->isValid();
}


int sSpDecoder::getMatrix(const sMatrixs& matrixs)
{
	if (matrixs.empty())
	{
		return 0;
	}
	auto pal = new s565[256];
	memcpy(pal, palette, 512);
	cSp::toPalette(pal, matrixs);
	matrixid = 0;
	for (const auto& m : matrixs)
	{
		matrixid += m.value;
	}
	if (matrixid > 0)
	{
		const auto& it = palettes.find(matrixid);
		if (it == palettes.end())
		{
			sPalette palette;
			palette.palette = pal;
			palette.ref = 1;
			palettes.insert(std::make_pair(matrixid, palette));
		}
		else
		{
			++it->second.ref;
		}
	}
	return matrixid;
}

const int sSpDecoder::cMatrixFlag = 16;
bool sSpDecoder::removeMatrix(int mid)
{
	for (int k = info.framesCount - 1; k >= 0; --k)
	{
		bitmaps.erase((mid << cMatrixFlag) + k);
	}
	if (mid == 0)
	{
		return true;
	}
	const auto& it = palettes.find(mid);
	if (it == palettes.end())
	{
		return false;
	}
	if ((--it->second.ref == 0))
	{
		delete[] it->second.palette;
		palettes.erase(it);
	}
	return true;
}

const sAlphaBmp* sSpDecoder::getBitmap(int mid, int iframe, eBlend e)
{
	int index = (mid << cMatrixFlag) + iframe;
	const auto& it = bitmaps.find(index);
	std::map<eBlend, sAlphaBmp>* textures = nullptr;
	if (it != bitmaps.end())
	{
		textures = &it->second;
		const auto& it2 = textures->find(e);
		if (it2 != textures->end())
		{
			return &it2->second;
		}
	}
	else
	{
		std::map<eBlend, sAlphaBmp> bmps;
		bitmaps.insert(std::make_pair(index, bmps));
		textures = &bitmaps.at(index);
	}
	if (!decode(iframe))
	{
		textures->erase(e);
		if (textures->empty())
		{
			bitmaps.erase(index);
		}
		return nullptr;
	}
	sAlphaBmp* pBmp;
	textures->insert(std::make_pair(e, sAlphaBmp()));
	pBmp = &textures->at(e);

	const auto& dec = decodes + iframe;
	auto datas = dec->getBitmap(mid == 0 ? palette : palettes.at(mid).palette, e);
	pBmp->w = dec->w;
	pBmp->h = dec->h;
	pBmp->texture = sAlphaBmp::getTexture(pBmp->w, pBmp->h, datas);
	if (pBmp->texture == nullptr)
	{
		textures->erase(e);
		if (textures->empty())
		{
			bitmaps.erase(index);
		}
	}
	return pBmp;
}


//////////////////////////////////////////////////////////////////////////
cSp::~cSp()
{
	for (auto& r : _refs)
	{
		delete r.second.ptr;
	}
}


void cSp::toPalette(s565* palette, const sMatrixs& matrixs)
{
	if (matrixs.empty())
	{
		return;
	}
	int r, g, b;
	auto p565 = palette;
	for (int k = 0, size = matrixs.size(); k < size; ++k)
	{
		const auto& m = matrixs.at(k);
		const auto& matrix = m.matrix;
		for (int i = m.start; i < m.end; ++i, ++p565)
		{
			r = p565->r * matrix.r1 + p565->g * matrix.r2 + p565->b * matrix.r3;
			g = p565->r * matrix.g1 + p565->g * matrix.g2 + p565->b * matrix.g3;
			b = p565->r * matrix.b1 + p565->g * matrix.b2 + p565->b * matrix.b3;
			p565->r = std::min(r >> 8, 0x1F);
			p565->g = std::min(g >> 8, 0x3F);
			p565->b = std::min(b >> 8, 0x1F);
		}
	}
}


const sSpDecoder* cSp::getDecoder(ulong uid)
{
	const auto& it = _refs.find(uid);
	if (it != _refs.end())
	{
		++it->second.ref;
		return &it->second.decoder;
	}
#if ccc_wdf
	auto idx = search2(uid);
	if (idx == nullptr)
	{
		return nullptr;
	}
	auto ptr = getData(idx, true);
	if (ptr == nullptr)
	{
		return nullptr;
	}
#else 
	int size;
	auto ptr = getData(_filename, uid, size, true);
	if (ptr == nullptr)
	{
		return nullptr;
	}
#endif
	sRef r;
	r.ptr = ptr;
	r.ref = 1;
	_refs.insert(std::make_pair(uid, r));
	auto& decoder = _refs.at(uid).decoder;
	decoder.load(ptr);
	if (!decoder.isValid())
	{
		_refs.erase(uid);
		return nullptr;
	}
	// 必有效
	return &decoder;
}


bool cSp::freeDecoder(ulong uid)
{
	const auto& it = _refs.find(uid);
	if (it == _refs.end())
	{
		return false;
	}

	auto& ref = it->second;
	if ((--ref.ref) == 0)
	{
		delete[] ref.ptr;
		_refs.erase(it);
		return true;
	}
	return false;
}


//////////////////////////////////////////////////////////////////////////
cSps::~cSps()
{

}

cSps* cSps::getInstance()
{
	static cSps* s_sps = new cSps();
	return s_sps;
}

bool cSps::load(const std::string &filename)
{
	const auto& it = _spMap.find(filename);
	if (it != _spMap.end())
	{
		return false;
	}
	{
		cSp sp;
		if (!sp.load(filename, true))
		{
			return false;
		}
	}
	_spMap.insert(std::make_pair(filename, cSp()));
	auto& sp = _spMap.at(filename);
	sp.load(filename);
	_sps.push_back(&sp);
	return true;
}


const sSpDecoder* cSps::getDecoder(ulong uid)
{
	const auto& it = _uidxs.find(uid);
	if (it != _uidxs.end())
	{
		return it->second->getDecoder(uid);
	}

	for (auto& sp : _sps)
	{
		auto decoder = sp->getDecoder(uid);
		if (decoder != nullptr)
		{
			_uidxs.insert(std::make_pair(uid, sp));
			return decoder;
		}
	}
	return nullptr;
}

bool cSps::freeDecoder(ulong uid)
{
	const auto& it = _uidxs.find(uid);
	if (it == _uidxs.end())
	{
		return false;

	}
	return it->second->freeDecoder(uid);
}


#undef ccc_wdf