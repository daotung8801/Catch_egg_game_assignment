#include "main_object.h"

BASKET::BASKET(){
    //Initialize the offsets
    mPosX = 0;
    mPosY = 466;
    main_object_rect.h=BASKET_HEIGHT;
    main_object_rect.w=BASKET_WIDTH;
    main_object_rect.y=mPosY;
    mVelX = 0;
}
void BASKET::handleEvent( SDL_Event& e ){
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ) {
        //Adjust the velocity
        switch( e.key.keysym.sym ) {
            case SDLK_LEFT: mVelX -= BASKET_VEL; break;
            case SDLK_RIGHT: mVelX += BASKET_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 ) {
        //Adjust the velocity
        switch( e.key.keysym.sym ) {
            case SDLK_LEFT: mVelX += BASKET_VEL; break;
            case SDLK_RIGHT: mVelX -= BASKET_VEL; break;
        }
    }
}
void BASKET::move() {
    mPosX += mVelX;
    main_object_rect.x=mPosX;
    if( ( mPosX < 0 ) || ( mPosX + BASKET_WIDTH > 1000 ) ) {
        //Move back
        mPosX -= mVelX;
        main_object_rect.x=mPosX;
    }
}
