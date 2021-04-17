#pragma once
#ifndef USEFUL_MACROS_H
#define USEFUL_MACROS_H

#include <cstdlib>
#include <cmath>
#include <float.h>
#include <time.h>

#define SEED srand ((unsigned int)time(NULL))
// Generates a random value from 0 to 1
#define RANDOM ((rand() % 1001) / 1000.0f)
// Generates a random real values from -1 to 1
#define REAL_RANDOM_NEG (((rand() % 2001) - 1000) / 1000.0f)
// Generates a random integer from low to high inclusive
#define RANGED_RANDOM_INT(low, high) ((rand() % ((high) - (low) + 1)) + (low))
// Generates a random float from low to high inclusive
#define RANGED_RANDOM(low, high) ((RANDOM * ((high)-(low))) + (low))
// Simulates a coin flip based on a given probability
#define FLIP(probability) (((probability) >= 1.0)?true:(RANDOM<=(probability)))

#endif