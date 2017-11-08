#include "Forest.hpp"

void Forest::printForest(void) const {

    const Screen* screen = Screen::instance();
#if 0
    static char empty_image[] = "images/empty.bmp";
    static char tree_image[] = "images/tree.bmp";
    static char fire_image[] = "images/fire.bmp";
#else
    static char empty_image[] = "images/empty3.bmp";
    static char tree_image[] = "images/tree3.bmp";
    static char fire_image[] = "images/fire3.bmp";
#endif

    size_t x, y;

    for (x = 0; x < _X; ++x) {
        for (y = 0; y < _Y; ++y) {
            switch (_forest[x][y]) {

            case -1:
                screen->draw(empty_image, x, y);
                break;

            case 0:
                screen->draw(tree_image, x, y);
                break;

            case 1:
                screen->draw(fire_image, x, y);
                break;
            }
        }
    }

    screen->update();
}

void Forest::step(void) {

    for (size_t x = 0; x < _X; ++x) {
        #pragma omp parallel num_threads(8)
        {
            #pragma omp for
            for (size_t y = 0; y < _Y; ++y) {

                switch (_forest[x][y]) {

                case -1: // empty
                    _newForest[x][y] = grow();
                    break;

                case 0: // tree
                    _newForest[x][y] = neighbor(x, y);
                    if (_newForest[x][y] == 0) {
                        _newForest[x][y] = lightning();
                    }
                    break;

                case 1: // burning
                    _newForest[x][y] = -1;
                    break;
                }
            }
        }
    }

    _forest = _newForest;
}

Forest::Forest(size_t X, size_t Y) :
    _X(X), _Y(Y), _pLight(0.0000001), _pGrow(0.001), _pFire(0.855) {
    _mt.seed(time(0));
    setup();
}

Forest::Forest(void) {
    exit(1);
}

Forest::~Forest(void) {
}

// ##################
// #	PRIVATE		#
// ##################

short Forest::neighbor(size_t x, size_t y) {
    int left, right, top, bottom;

    left = x - 1;
    if (left < 0) {
        left = _X - 1;
    }
    if (_forest[left][y] == 1) {
        return (fire());
    }

    right = x + 1;
    if (right >= _X) {
        right = 0;
    }
    if (_forest[right][y] == 1) {
        return (fire());
    }

    top = y + 1;
    if (top >= _Y) {
        top = 0;
    }
    if (_forest[x][top] == 1) {
        return (fire());
    }

    bottom = y - 1;
    if (bottom <= 0) {
        bottom = _Y - 1;
    }
    if (_forest[x][bottom] == 1) {
        return (fire());
    }

    return (0);
}

short Forest::fire(void) {
    if (rand() <= _pFire) {
        return (1);
    } else {
        return (0);
    }
}

short Forest::grow(void) {
    if (rand() <= _pGrow) {
        return (0);
    } else {
        return (-1);
    }
}

short Forest::lightning(void) {
    if (rand() <= _pLight) {
        return (1);
    } else {
        return (0);
    }
}

double Forest::rand(void) {
    return (_rand(_mt));
}

void Forest::setup(void) {
    size_t x, y;

    // Resize
    _forest.resize(_X);
    _newForest.resize(_X);
    for (x = 0; x < _X; ++x) {
        _forest[x].resize(_Y);
        _newForest[x].resize(_Y);
    }

    // Fill randomly with trees. Approx 80%
    for (x = 0; x < _X; ++x) {
        for (y = 0; y < _Y; ++y) {
            if (rand() < 0.75) {
                _forest[x][y] = 0;
            } else {
                _forest[x][y] = -1;
            }
        }
    }

    // Set a tree on fire
    _forest[_X / 2][_Y / 2] = 1;

}
