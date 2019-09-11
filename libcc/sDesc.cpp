#include "sDesc.h"
#include "cSp.h"

sDescs::sDescs()
{
	clear();
}

sDescs::operator bool() const
{
	return !(uhead == cSp::c0 && name.empty() && descs.empty());
}



void sDescs::clear()
{
	uhead = cSp::c0;
	name.clear();
	descs.clear();
}

void sDescs::push(const sDesc& desc)
{
	descs.push_back(desc);
}

void sDescs::push(const std::string& text, const s888& color)
{
	sDesc desc;
	desc.text = text;
	desc.color = color;
	push(desc);
}


