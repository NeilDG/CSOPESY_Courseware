#include "MathUtils.h"
#include <stdlib.h>
#include <cmath>

float MathUtils::randomFloat(float a, float b)
{
    float random = ((float)rand()) / (float)RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

int MathUtils::randomInt(int a, int b)
{
    int range = a - b + 1;
    int num = rand() % range + a;

    return num;
}

float MathUtils::normalize(float x, float xMin, float xMax, float normMin, float normMax)
{
    float normRange = (normMax - normMin);
    float xNorm = (x - xMin) / (xMax - xMin);
    float result = (normRange * xNorm) + normMin;

    return result;
}

/**
 * \brief Returns true if random number hits threshold (rand_num >= threshold)
 * \param min Min value. Default = 0
 * \param max max value. Default = 100
 * \param threshold Threshold to met
 * \return 
 */
bool MathUtils::chanceHit(int threshold, int min, int max)
{
    int randNum = randomInt(min, max);
    return (randNum >= threshold);
}
