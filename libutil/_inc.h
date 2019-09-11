#pragma once
#include "../libcc/_cc.h"
#include "../libcc/_cocos.h"

typedef cocos2d::Color3B sColor;
namespace cc
{
	inline sColor to3B(const s888& color)
	{
		return sColor(color.r, color.g, color.b);
	}
	static const std::string cComponentMenuItemLongPress1 = "long_press_first";
	static const std::string cComponentMenuItemLongPress = "long_press";
}