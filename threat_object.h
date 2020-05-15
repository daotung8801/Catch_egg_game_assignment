#ifndef THREAD_OBJECT_H
#define THREAD_OBJECT_H

#include "Base_object.h"

class EGG {
    public:
        static const int THREAD_WIDTH = 39;
        static const int THREAD_HEIGHT = 50;
        EGG();
    	void egg_move(SDL_Rect main_rect);
    	void special_egg_render();
    	void normal_egg_render();
    	void bomb_render();
    	SDL_Rect getThreadRect() {return thread_rect;}
        int getPoint() {return point;}
        int getMissEgg() {return miss_egg;}
    private:
        int x,y;
        int speed_y;
        SDL_Rect thread_rect;
        int point;
        int miss_egg;
};

#endif
