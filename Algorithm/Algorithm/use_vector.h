#pragma once

#include "001.STLContainer_AllSet.h"

#ifdef FLAG_USE_CUSTOM_LIBRARY
#include "Vector.h"
#define vector Vector
#else
#include <vector>
#define vector vector
#endif
