#pragma once
#include "_inc.h"

struct sMapInfo { int mw, mh, bw, bh; };

struct sMapDecode : public sSpFrame
{
	uchar* decodes = nullptr;

	~sMapDecode();
	const bool isValid() const;
	bool decode(uchar* ptr);
};


struct sMapAlpha : public sSpFrame
{
	int maskIdx, bx, by;
	Texture2D* texture = nullptr;

	~sMapAlpha();
	const bool isValid() const;
	Texture2D* getAlpha(const uchar* image, const sMapDecode& m);
};

struct sMapBlock
{
	Image* image = nullptr;
	Texture2D* texture = nullptr;
	std::vector<sMapAlpha> alphas;

	~sMapBlock();
	bool isValid() const;
};

struct sMap
{
	const char* ptr;
	sMapInfo info;
	int blocksCount, masksCount;
	uint* blockOffs = nullptr;
	uint* maskOffs = nullptr;
	sMapDecode* masks = nullptr;
	uchar* obstacles = nullptr;
	cAstar* astar = nullptr;

	std::map<int, sMapBlock> blocks;

	~sMap();
	bool load(const char* ptr);
	bool loadMask();
	bool loadObstacles();
	bool isObstacle(int x20, int y20);
	Texture2D* getBitmap(int blockIdx);
	bool isLoaded();
	void clear();

	bool search(int x, int y, int tx, int ty, std::vector<cAstar::sXY>& paths);
};


struct sMapCache
{
	int mapid = 0;
	std::string filename;
	sMap* pMap = nullptr;
	const bool isValid() const;
};

class cMapReader
{
public:
	cMapReader();
	~cMapReader();
	static cMapReader* getInstance();

	static bool isMap(const char* ptr);

	static const char* getData(const std::string& filename);

	const std::string& getFileName(int mapid);

	sMapCache getCache(int mapid);

	bool freeCache(const sMapCache& cache);

private:
	struct sRef
	{
		sMap* pMap = nullptr;
		int ref;
	};
	std::map<std::string, sRef> _caches;
	std::map<int, std::string> _searchs;
public:
	static const int c320, c240, c16, c12, c20;
};

