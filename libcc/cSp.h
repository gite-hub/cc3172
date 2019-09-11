#pragma  once
#include "s565.h"

class cWdf
{
public:
	static cWdf* getColor();
	static cWdf* getMp3();
	static cWdf* getWav();
	~cWdf();
	static bool isLoadable(const std::string &filename);
	bool load(const std::string &filename, bool onlyCheck = false);

	struct sIndex { ulong uid, offset, size; };

	const sIndex* search2(ulong uid);

	const sIndex* getIndexs() const { return _indexs; }

	int getIndexsCount() const { return _indexsCount; }

	static const char* getData(const std::string& path, ulong uid, int& size, bool isJudgeSp);

	const char* getData(const sIndex* idx, bool isJudgeSp = false);

	const char* getData(ulong uid, int& size);

protected:
	std::string _filename;
	FILE* _file = nullptr;
	sIndex* _indexs = nullptr;
	int _indexsCount = 0;
};



struct sSpFrame
{
	int x = 0, y = 0, w = 0, h = 0;
	bool isValid() const;
};
struct sSpInfo
{
	int directionsCount;
	int framesCountPerDirection;
	int framesCount;
	int width, height, kx, ky;
	sSpFrame* frames = nullptr;

	~sSpInfo();
	operator bool() const;
};

enum class eBlend { normal, light, blink };
struct sSpDecode
{
	int w, h;
	uchar* palIdxs = nullptr;
	uchar* alphas = nullptr;

	sSpDecode();
	~sSpDecode();
	bool isValid() const;
	void decode(int w, int h, const uchar* ptrHead, ulong offs);
	const ulong* getBitmap(const s565* palettes, eBlend e);
};

struct sAlphaBmp
{
	int w, h;
	void* texture = nullptr;

	sAlphaBmp();
	virtual ~sAlphaBmp();
	virtual bool isValid() const;
	static void* getTexture(int w, int h, const ulong* datas);
	static void freeTexture(void* texture);
};


struct sMatrix9 { ushort r1, r2, r3, g1, g2, g3, b1, b2, b3; };
struct sMatrix { sMatrix9 matrix;  ushort start, end; ulong value; };
typedef std::vector<sMatrix> sMatrixs;
struct sPalette { const s565* palette; int ref; };
struct sSpDecoder
{
	sSpInfo info;
	const s565* palette = nullptr;
	const ulong* offsets = nullptr;
	sSpDecode* decodes = nullptr;

	ulong matrixid = 0;
	// 2<<16Ö¡ ×ã¹»ÁË°É
	static const int cMatrixFlag;
	std::map<u64, sPalette> palettes;
	std::map<u64, std::map<eBlend, sAlphaBmp>> bitmaps;

	sSpDecoder();
	~sSpDecoder();
	bool isValid() const;

	void load(const char* ptr);
	bool decode(int frame);
	int getMatrix(const sMatrixs& matrixs);
	bool removeMatrix(int mid);
	const sAlphaBmp* getBitmap(int mid, int iframe, eBlend e);
};



class cSp : public cWdf
{
public:
	static const ulong c0 = 0;

	~cSp();

	static void toPalette(s565* palette, const sMatrixs& matrixs);

	const sSpDecoder* getDecoder(ulong uid);

	bool freeDecoder(ulong uid);

private:
	struct sRef 
	{ 
		const char* ptr;
		sSpDecoder decoder;
		int ref; 
	};
	std::map<ulong, sRef> _refs;
};


struct sSp
{
	ulong uid = cSp::c0;
	sMatrixs matrixs;
};
typedef std::vector<sSp> sSps;
namespace ccu
{
	static const ulong uShadow = 0xDCE4B562;
}

class cSps
{
public:
	~cSps();
	static cSps* getInstance();

	bool load(const std::string &filename);

	const sSpDecoder* getDecoder(ulong uid);
	bool freeDecoder(ulong uid);
private:
	std::map<std::string, cSp> _spMap;
	std::vector<cSp*> _sps;
	std::map<ulong, cSp*> _uidxs;
};
