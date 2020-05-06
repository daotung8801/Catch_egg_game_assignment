#include "thread_object.h"

EGG::EGG() {
    x=rand()%800+100,y=80;
    speed_y=rand()%5+2;
    thread_rect.h=THREAD_HEIGHT;
    thread_rect.w=THREAD_WIDTH;
    thread_rect.x=x;
}
void EGG::egg_move(SDL_Rect main_rect) {
    y+=speed_y;
    thread_rect.y=y;
    point =0;
    miss_egg=0;
    if(y>=466 || checkCollision(main_rect,thread_rect)) {
        if(y>=466) {
        miss_egg=1;
        }
        if(checkCollision(main_rect,thread_rect)) {point=1;}
        x=rand()%800+140;
        thread_rect.x=x;
        y=80;
        thread_rect.y=y;
        speed_y=rand()%3+3;
    }
}
