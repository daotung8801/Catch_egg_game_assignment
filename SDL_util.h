#ifndef SDL_UTIL_H
#define SDL_UTIL_H

#include "Base_object.h"

void logSDLError(std::ostream& os,const std::string &msg, bool fatal = false);
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer,
             int SCREEN_WIDTH,int SCREEN_HEIGHT,const string &WINDOW_TITLE);

#endif

