#ifndef RANDOM_H
#define RANDOM_H

#include <random>

class Random 
{
public:
    // Returns a random float between 0.0 and 1.0
    static float getFloat01()
    {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<float> dis(0.0f, 1.0f);
        return dis(gen);
    }
    
    // Returns a random float between min and max
    static float getFloat(float min, float max)
    {
        return min + getFloat01() * (max - min);
    }
};

#endif