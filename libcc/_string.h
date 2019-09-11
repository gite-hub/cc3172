#pragma once
#include <string>
#include <sstream>
#include <stdarg.h>
#include <vector>
#include <assert.h>


namespace cc
{
	// 转 字符串
	template <typename T>
	inline std::string toString(T arg)
	{
		std::stringstream string_stream;
		string_stream << arg;
		return string_stream.str();
	}
}


// 字符串 格式化
inline std::string toString(const char* format, ...)
{
	va_list args;
	std::string buffer(256, '\0');

	va_start(args, format);
	int nret = vsnprintf(&buffer.front(), buffer.length() + 1, format, args);
	va_end(args);

	if (nret >= 0) {
		if ((unsigned int)nret < buffer.length()) {
			buffer.resize(nret);
		}
		else if ((unsigned int)nret > buffer.length()) { // VS2015/2017 or later Visual Studio Version
			buffer.resize(nret);

			va_start(args, format);
			nret = vsnprintf(&buffer.front(), buffer.length() + 1, format, args);
			va_end(args);

			assert(nret == buffer.length());
}
		// else equals, do nothing.
	}
	else { // less or equal VS2013 and Unix System glibc implement.
		do {
			buffer.resize(buffer.length() * 3 / 2);

			va_start(args, format);
			nret = vsnprintf(&buffer.front(), buffer.length() + 1, format, args);
			va_end(args);

		} while (nret < 0);

		buffer.resize(nret);
	}

	return buffer;
}


namespace cc
{
	// 字符串 分割
	inline void split(const std::string &str, const std::string &delim, std::vector<std::string>& ret)
	{
		ret.clear();
		size_t last = 0;
		size_t index = str.find_first_of(delim, last);

		if (index == std::string::npos)
		{
			ret.push_back(str);
			return;
		}

		while (index != std::string::npos)
		{
			ret.push_back(str.substr(last, index - last));
			last = index + 1;
			index = str.find_first_of(delim, last);
		}

		if (index - last > 0)
		{
			ret.push_back(str.substr(last, index - last));
		}
	}


	// 字符串 替换
	inline std::string replace(std::string str, const std::string &to_replace, const std::string &replace)
	{
		std::string::size_type pos = 0;
		std::string::size_type srcLen = to_replace.size();
		std::string::size_type desLen = replace.size();
		pos = str.find(to_replace, pos);
		while ((pos != std::string::npos))
		{
			str.replace(pos, srcLen, replace);
			pos = str.find(to_replace, (pos + desLen));
		}
		return str;
	}
}
