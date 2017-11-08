#include "Screen.hpp"

Screen* Screen::_instance = 0;

void Screen::draw(char* file, int x, int y) const {
    static SDL_Surface* image;
    static SDL_Rect dest;
    image = SDL_LoadBMP(file);
    if (image == NULL) {
        printf("Can't load image\n");
    }
    dest.w = image->w;
    dest.h = image->h;
    dest.x = image->w * x;
    dest.y = image->h * y;

    SDL_BlitSurface(image, NULL, _screen, &dest); // kopiere das Bild-Surface auf das _screen-surface
    //SDL_UpdateRects(_screen, 1, &dest);
    SDL_FreeSurface(image); // Das Bitmap-Surface löschen
}

void Screen::update() const {
    SDL_Flip(_screen);
}

Screen::~Screen() {
    SDL_Delay(1000);
    SDL_Quit();
    delete _instance;
    _instance = 0;
}

Screen* Screen::instance(void) {
    return (_instance);
}

void Screen::create(int x, int y) {
    if (!_instance) {
        _instance = new Screen(x, y);
    }
}

Screen::Screen(void) {
}

Screen::Screen(int x, int y) {
    if (SDL_Init(SDL_INIT_VIDEO) == -1) {
        printf("Can't init SDL:  %s\n", SDL_GetError());
        exit(1);
    }
    atexit (SDL_Quit);

    _screen = SDL_SetVideoMode(x, y, 24, SDL_HWSURFACE);
    if (_screen == NULL) {
        printf("Can't set video mode: %s\n", SDL_GetError());
        exit(1);
    }
}
