#include "cSp.h"
#include "_string.h"
#include "_cocos.h"

const char* cWdf::getData(const std::string& path, ulong uid, int& size, bool isJudgeSp)
{
	auto data = FileUtils::getInstance()->getDataFromFile(path + toString("%08X.was", uid));
	if (data.isNull())
	{
		return nullptr;
	}

	if (isJudgeSp)
	{
		static char ptr2[2];
		memcpy(ptr2, data.getBytes(), 2);
		if (*(ushort*)ptr2 != 0x5053)
		{
			return nullptr;
		}
	}

	size = data.getSize();
	auto ptr = (char*)data.getBytes();
	data.fastSet(nullptr, 0);
	return ptr;
}

void* sAlphaBmp::getTexture(int w, int h, const ulong* datas)
{
	Texture2D* texture = new Texture2D();
	bool isok = texture->initWithData(datas, w * h * 4, Texture2D::PixelFormat::RGBA8888, w, h, Size::ZERO);
	delete[] datas;
	if (isok)
	{
		return texture;
	}
	delete texture;
	return nullptr;
}

void sAlphaBmp::freeTexture(void* tex)
{
	Texture2D* texture = (Texture2D*)tex;
	CC_SAFE_RELEASE(texture);
}