#pragma once

#define _GXX_EXPERIMENTAL_CXX0X__ 1

#include <cstdlib>
#include <random>
#include <vector>

#if OMP > 0
#include <omp.h>
#endif

#if DEBUG > 0
#include <iostream>
#endif
