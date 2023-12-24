#ifndef AUXILIARY_H
#define AUXILIARY_H

#include <cstdlib>
#include <cmath>

inline double RandomFloat(){return rand() / (RAND_MAX + 1.f);}

inline int RandomIntegerInRange(int lowerBound, int upperBound){
	return (int)round(lowerBound + (RandomFloat() * (upperBound - lowerBound)));
}

#endif