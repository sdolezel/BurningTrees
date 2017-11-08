//============================================================================
// Name        : BurningTrees.cpp
// Author      : Stefan Dolezel
// Version     :
// Copyright   : Your copyright notice
// Description : Burning tree simulation
// Forest of size N x M (+ periodic)
// Field values:
// 		-1	:	empty
//		 0	:	Tree
//		 1	:	Burning tree
//
// Start: All fields 0 = trees
//
// If a tree burns the field value is changed to -1 for the next step
// If one of the four neighbor trees is burning > tree also starts burning
// If not it may be hit by a lightning. Starts burning with probability pLight
// If the field is empty a new tree may grow with a probability pGrow
//
//============================================================================

#include "all.hpp"

#include "Screen.hpp"
#include "Forest.hpp"

int main(void) {
#if OMP > 0
    omp_set_num_threads(8);
#endif

    // Variables
    const short STEPS = 10;
    const short PIXELSIZE = 3;
    short step = 0;
    short X = 1000 / PIXELSIZE;
    short Y = 1000 / PIXELSIZE;

    Screen::create(X * PIXELSIZE, Y * PIXELSIZE);
//	Screen* screen = Screen::instance();

    Forest forest(X, Y);
    forest.printForest();

    // Main loop
    while (STEPS - step) {
        ++step;
#if DEBUG > 0
        std::cout << "Step " << step << std::endl;
#endif

        forest.step();
        forest.printForest();
    }

    return EXIT_SUCCESS;
}
