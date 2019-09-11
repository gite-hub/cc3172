#include "cSave.h"

cSave* cSave::getSave()
{
	static cSave* s_save = new cSave();
	return s_save;
}

cSave* cSave::getSaveEncode()
{
	static cSave* s_saveEncode = new cSave();
	return s_saveEncode;
}

cSave* cSave::getLoad()
{
	static cSave* s_load = new cSave();
	return s_load;
}

cSave* cSave::getLoadEncode()
{
	static cSave* s_loadEncode = new cSave();
	return s_loadEncode;
}

void cSave::clear()
{
	_str.clear();
}

bool cSave::save(const std::string& filename, bool encode)
{
	if (_file.is_open())
	{
		_file.close();
	}
	_file.open(filename, std::ios::out);
	if (!_file.is_open())
	{
		return false;
	}
	std::string str = _str.str();
	if (encode)
	{
		for (int i = str.size() - 1; i >= 0; --i)
		{
			unsigned char& x = (unsigned char&)str[i];
			x = (x & 0xF) << 4 | ((x & 0xF0) >> 4);
			x = ((x & 0xC0) >> 6) | (((x & 0x30) >> 4) << 2) | (((x & 0xC) >> 2) << 4) | ((x & 0x3) << 6);
		}
	}
	_file.write(str.data(), str.size());
	_file.close();
	return true;
}



//////////////////////////////////////////////////////////////////////////


bool cSave::load(const std::string& filename, bool encode)
{
	if (_file.is_open())
	{
		_file.close();
	}
	_file.open(filename, std::ios::in);
	if (!_file.is_open())
	{
		return false;
	}
	_file.seekg(0, std::ios_base::end);
	int size = (int)_file.tellg();
	char *data = new char[size];
	_file.seekg(0, std::ios_base::beg);
	_file.read(data, size);
	_file.close();
	if (encode)
	{
		for (int i = size - 1; i >= 0; --i)
		{
			unsigned char& x = (unsigned char&)data[i];
			x = ((x & 0xC0) >> 6) | (((x & 0x30) >> 4) << 2) | (((x & 0xC) >> 2) << 4) | ((x & 0x3) << 6);
			x = (x & 0xF) << 4 | ((x & 0xF0) >> 4);
		}
	}
	_str.str(std::string(data, size));
//	_str.seekg(0, std::ios_base::beg);
	delete[] data;
	return true;
}

cSave::operator sStream&()
{
	return _str;
}
