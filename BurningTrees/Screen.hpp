#pragma once

#include "all.hpp"

#include "SDL/SDL.h"

class Screen {
public:
    virtual ~Screen();

    void draw(char* file, int x, int y) const;
    void update() const;

    static void create(int x, int y);
    static Screen* instance(void) ;

protected:
    static Screen* _instance;

private:
    SDL_Surface* _screen;

    Screen(void);
    Screen(int x, int y);

};

