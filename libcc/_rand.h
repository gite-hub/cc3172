#pragma once
#include "base/ccRandom.h"

namespace cc
{
	template<typename T> // ¿ªÇø¼ä
	inline T random(T min, T max) { return cocos2d::random(min, max); }
	inline float random() { return cocos2d::random(0.0f, 0.999999f); }
	float gaussStandard();
	float gauss(float mu, float sigma);
	float gauss(float exp_1_5);
	float gauss();
}