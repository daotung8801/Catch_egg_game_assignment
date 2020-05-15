#include "SDL_util.h"
#include "Base_object.h"
#include "main_object.h"
#include "threat_object.h"

//Screen variable
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;
const string WINDOW_TITLE = "Catch eggs - XXXxxx Copyrighted by DAO XUAN TUNG xxxXXX";
int highest_score=0;
bool mouse_quit=false;

//Text variable
SDL_Color textColor = {236,29,37};
stringstream timeText;
stringstream scoreText;
stringstream missEggText;
stringstream highestScoreText;
stringstream scoreDisplayText;
stringstream restartText;
Uint32 startTime = 0;

SDL_Window* window=NULL;
SDL_Renderer* renderer=NULL;
SDL_Event e;
TTF_Font *gFont = NULL;

//image
LTexture background;
LTexture basket;
LTexture chicken;
LTexture normal_egg;
LTexture special_egg;
LTexture bomb;
LTexture plus_point1;
LTexture plus_two_point;
LTexture explosion;
LTexture heart;
LTexture gameOver;
LTexture menuGame;
//Text
LTexture score_text;
LTexture time_text_texture;
LTexture miss_Egg_Text;
LTexture highest_score_text;
LTexture score_display_text;
LTexture restart_text;
//Music
Mix_Music *gMusic = NULL;
Mix_Chunk *explosion_sound = NULL;
Mix_Chunk *egg_sound=NULL;
Mix_Chunk *egg_cracking=NULL;
Mix_Chunk *fail_muic=NULL;

void BASKET::render() {
	basket.render(renderer,mPosX, mPosY );
}
void EGG::special_egg_render() {
    special_egg.render(renderer,x,y);
}
void EGG::normal_egg_render() {
    normal_egg.render(renderer,x,y);
}
void EGG::bomb_render() {
    bomb.render(renderer,x,y);
}
void loadMedia();
void close();
void waitUntilKeyPressed();

int main(int argc,char* argv[]) {
    srand(time(NULL));
    initSDL(window,renderer,SCREEN_WIDTH,SCREEN_HEIGHT,WINDOW_TITLE);
    loadMedia();
    bool exit_programme=false;
    //Menu game
    menuGame.render(renderer,0,0);
    SDL_RenderPresent(renderer);
    waitUntilKeyPressed();

    while(!exit_programme) {
        BASKET basket_real;
        EGG normal_egg1;
        EGG normal_egg2;
        EGG special_egg_real;
        EGG bomb_real;
        EGG bomb_real2;
        bool quit = false;
        bool stopMusic=false;
        int life_point=3;
        int score_point=0;
        int miss_egg=0;
        startTime=SDL_GetTicks();

        while(!quit) {
            //Condition to quit game
            while( SDL_PollEvent( &e ) != 0 ) {
                if( e.type == SDL_QUIT ) {
                    Mix_HaltMusic();
                    quit = true;
                    stopMusic=true;
                }
                basket_real.handleEvent( e );
            }
            if(life_point==0) {
                Mix_HaltMusic();
                quit=true;
                stopMusic=true;
            }
            if(miss_egg>=40) {
                Mix_HaltMusic();
                quit=true;
                stopMusic=true;
            }

            //Get Rect
            SDL_Rect basketRect=basket_real.getBasketRect();
            SDL_Rect normal_eggRect1=normal_egg1.getThreadRect();
            SDL_Rect normal_eggRect2=normal_egg2.getThreadRect();
            SDL_Rect special_egg_rect=special_egg_real.getThreadRect();
            SDL_Rect bomb_rect=bomb_real.getThreadRect();
            SDL_Rect bomb_rect2=bomb_real2.getThreadRect();

            //Moving
            basket_real.move();
            special_egg_real.egg_move(basketRect);
            normal_egg1.egg_move(basketRect);
            normal_egg2.egg_move(basketRect);
            bomb_real.egg_move(basketRect);
            bomb_real2.egg_move(basketRect);

            //Music handling
            while(!stopMusic) {
                if( Mix_PlayingMusic() == 0 ) {
                    Mix_PlayMusic( gMusic, -1 );
                }
                break;
            }
            if(normal_egg1.getMissEgg()==1) {
                miss_egg++;
                Mix_PlayChannel( -1, egg_cracking, 0 );
            }
            if(normal_egg2.getMissEgg()==1) {
                miss_egg++;
                Mix_PlayChannel( -1, egg_cracking, 0 );
            }
            if(special_egg_real.getMissEgg()==1 ) {
                miss_egg++;
                Mix_PlayChannel( -1, egg_cracking, 0 );
            }

            //text handling
            missEggText.str( "" );
            missEggText<<"Missed: "<<miss_egg;
            miss_Egg_Text.loadFromText(gFont,renderer,missEggText.str().c_str(),textColor);
            scoreText.str( "" );
            scoreText<<"Scores: "<<score_point;
            score_text.loadFromText(gFont,renderer,scoreText.str().c_str(),textColor);
            timeText.str( "" );
            timeText <<"Times: " <<(SDL_GetTicks() - startTime)/1000<<" s";
            time_text_texture.loadFromText(gFont,renderer,timeText.str().c_str(),textColor);

            //clear screen
            SDL_SetRenderDrawColor( renderer,255,255,255,255 );
            SDL_RenderClear(renderer);

            // Render to screen
            background.render(renderer,0,0);
            chicken.render(renderer,0,0);
            if(normal_egg1.getPoint()==1) {
                plus_point1.render(renderer,normal_eggRect1.x+45,normal_eggRect1.y-20);
                score_point++;
                Mix_PlayChannel( -1, egg_sound, 0 );
            }
            if(normal_egg2.getPoint()==1) {
                plus_point1.render(renderer,normal_eggRect2.x+45,normal_eggRect2.y-20);
                score_point++;
                Mix_PlayChannel( -1, egg_sound, 0 );
            }
            if(special_egg_real.getPoint()==1) {
                plus_two_point.render(renderer,special_egg_rect.x+45,special_egg_rect.y-20);
                score_point+=2;
                Mix_PlayChannel( -1, egg_sound, 0 );
            }
            if(bomb_real.getPoint()==1) {
                life_point--;
                explosion.render(renderer,bomb_rect.x,bomb_rect.y-30);
                Mix_PlayChannel( -1, explosion_sound, 0 );
            }
            if(bomb_real2.getPoint()==1) {
                life_point--;
                explosion.render(renderer,bomb_rect2.x,bomb_rect2.y-30);
                Mix_PlayChannel( -1, explosion_sound, 0 );
            }
            bomb_real.bomb_render();
            bomb_real2.bomb_render();
            special_egg_real.special_egg_render();
            normal_egg1.normal_egg_render();
            normal_egg2.normal_egg_render();
            basket_real.render();
            miss_Egg_Text.render(renderer,5,120);
            score_text.render(renderer,5,90);
            time_text_texture.render(renderer,450,90);
            if(life_point==3) {
                heart.render(renderer,945,90);
                heart.render(renderer,890,90);
                heart.render(renderer,835,90);
            }
            if(life_point==2) {
                heart.render(renderer,945,90);
                heart.render(renderer,890,90);
            }
            if(life_point==1) {
                heart.render(renderer,945,90);
            }
            SDL_RenderPresent(renderer);
        }
        //quit screen

        //text
        highestScoreText.str( "" );
        if(highest_score<score_point) {highest_score=score_point;}
        highestScoreText<<"Highest scores: "<<highest_score;
        highest_score_text.loadFromText(gFont,renderer,highestScoreText.str().c_str(),textColor);

        scoreDisplayText.str( "" );
        scoreDisplayText<<"Your scores: "<<score_point;
        score_display_text.loadFromText(gFont,renderer,scoreDisplayText.str().c_str(),textColor);

        restartText.str( "" );
        restartText<<"Press enter to restart";
        restart_text.loadFromText(gFont,renderer,restartText.str().c_str(),textColor);
        //render
        SDL_SetRenderDrawColor( renderer,255,255,255,255 );
        SDL_RenderClear(renderer);
        gameOver.render(renderer,0,0);
        highest_score_text.render(renderer,385,400);
        score_display_text.render(renderer,400,362);
        restart_text.render(renderer,362,530);
        //Music
        SDL_RenderPresent(renderer);
        SDL_Delay(900);
        Mix_PlayChannel( -1, fail_muic, 0 );
        //restart
        waitUntilKeyPressed();
        if(mouse_quit) {exit_programme=true;}
    }
	close();
	return 0;
}

void loadMedia() {
    //Loading picture
    basket.loadFromFile(renderer,"Picture/basket.jpg");
    background.loadFromFile(renderer,"Picture/background.jpg");
    chicken.loadFromFile(renderer,"Picture/chicken.jpg");
    special_egg.loadFromFile(renderer,"Picture/special_egg.jpg");
    normal_egg.loadFromFile(renderer,"Picture/normal_egg.jpg");
    bomb.loadFromFile(renderer,"Picture/bomb.jpg");
    plus_point1.loadFromFile(renderer,"Picture/one.jpg");
    plus_two_point.loadFromFile(renderer,"Picture/two.jpg");
    explosion.loadFromFile(renderer,"Picture/explosion.jpg");
    heart.loadFromFile(renderer,"Picture/heart.jpg");
    gameOver.loadFromFile(renderer,"Picture/gameOver.jpg");
    menuGame.loadFromFile(renderer,"Picture/menuGame.jpg");
    //Loading text font
    gFont = TTF_OpenFont( "font.ttf", 24 );
    //Loading music
    gMusic = Mix_LoadMUS( "Music/farm.wav" );
    explosion_sound=Mix_LoadWAV( "Music/explosion.wav" );
    egg_sound=Mix_LoadWAV( "Music/egg_sound.wav" );
    egg_cracking=Mix_LoadWAV( "Music/egg_cracking.wav" );
    fail_muic=Mix_LoadWAV( "Music/fail.wav" );
}
void close() {
	//Free loaded images
	basket.free();
    background.free();
    chicken.free();
    normal_egg.free();
    special_egg.free();
    bomb.free();
    plus_point1.free();
    plus_two_point.free();
    explosion.free();
    heart.free();
    gameOver.free();
    menuGame.free();
    //Text
    score_text.free();
    time_text_texture.free();
    miss_Egg_Text.free();
    highest_score_text.free();
    score_display_text.free();
    restart_text.free();
    //Free global font
    TTF_CloseFont( gFont );
    gFont = NULL;
    //Free music
    Mix_FreeMusic( gMusic );
    Mix_FreeChunk( explosion_sound );
    Mix_FreeChunk( egg_sound );
    Mix_FreeChunk( egg_cracking );
    Mix_FreeChunk( fail_muic );
    gMusic = NULL;
    explosion_sound=NULL;
    egg_sound=NULL;
    egg_cracking=NULL;
    fail_muic=NULL;
	//Destroy window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;
	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
void waitUntilKeyPressed() {
    while (true) {
        if(SDL_PollEvent( &e ) != 0 && e.type == SDL_QUIT) {
            mouse_quit=true;
            return;
        }
        if ( SDL_PollEvent( &e ) != 0 && e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN ) {return;}
    }
}
