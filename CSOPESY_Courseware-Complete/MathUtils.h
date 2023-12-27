#pragma once

class MathUtils
{
public:
	static float randomFloat(float a, float b);
	static int randomInt(int a, int b);
	static float normalize(float x, float xMin, float xMax, float normMin, float normMax);
	static bool chanceHit(int threshold, int min = 0, int max = 100);
};

