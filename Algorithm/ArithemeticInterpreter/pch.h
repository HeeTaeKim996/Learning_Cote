#pragma once
#include <stdio.h>
#include <string>

using namespace std;



#define AIM_64
//#define AIM_32

#ifdef AIM_64
#define INT long long
#define FLOAT double
#elif defined AIM_32
#define INT long
#define FLOAT float
#endif

#include "MemoryTracker.h"



#define DEBUG_SPEAK