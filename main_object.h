#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H

#include "Base_object.h"

class BASKET{
    public:
        static const int BASKET_WIDTH = 80;
		static const int BASKET_HEIGHT = 50;
		static const int BASKET_VEL = 10;
		BASKET();
		void handleEvent( SDL_Event& e );
		void move();
		void render();
		SDL_Rect getBasketRect() {return main_object_rect;}
    private:
		int mPosX, mPosY;
		int mVelX;
		SDL_Rect main_object_rect;
		int point;
};

#endif
