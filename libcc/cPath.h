#pragma once
#include <string>

class cPath
{
public:
	static std::string cDownload;
	static std::string cLxy;
	static std::string cI32;
	static std::string cWdf;
	static std::string cMap;
	static std::string cMusic;
	static std::string cFont;

	static const std::string& getRoot();
};