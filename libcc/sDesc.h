#pragma once
#include "s888.h"

struct sDesc
{
	std::string text;
	s888 color;
};


struct sDescs
{
	ulong uhead;
	std::string name;
	std::vector<sDesc> descs;

	sDescs();
	operator bool() const;
	void clear();
	void push(const sDesc& desc);
	void push(const std::string& text, const s888& color);
};


