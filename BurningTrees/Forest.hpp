#pragma once

#include "all.hpp"
#include "Screen.hpp"

class Forest {
public:
    void printForest(void) const;
    void step(void);

    Forest(size_t X, size_t Y);
    Forest(void);
    virtual ~Forest(void);

private:
    short neighbor(size_t x, size_t y);
    short neighborBoundary(void);
    short fire(void);
    short grow(void);
    short lightning(void);
    void setup(void);
    double rand(void);

    //short _n; // used to access [N]
    size_t _X; // x size
    //short _m; // used to access [M]
    size_t _Y; // y size

    double _pLight; // prob Lightning
    double _pGrow; // prob grow
    double _pFire; // prob to burn;

    std::vector<std::vector<int> > _forest;
    std::vector<std::vector<int> > _newForest;

    std::mt19937_64 _mt;
    std::uniform_real_distribution<double_t> _rand;

};

