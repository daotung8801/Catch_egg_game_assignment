#include "Base_object.h"

LTexture::LTexture() {
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture() {
	free();
}

void LTexture::loadFromFile(SDL_Renderer* des,string path ) {
	free();
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	newTexture = SDL_CreateTextureFromSurface( des, loadedSurface );

    mWidth = loadedSurface->w;
    mHeight = loadedSurface->h;

    SDL_FreeSurface( loadedSurface );
	mTexture = newTexture;
}
void LTexture::loadFromText(TTF_Font *Font,SDL_Renderer* des,string textureText, SDL_Color textColor ) {
    free();
    SDL_Surface* textSurface = TTF_RenderText_Solid(Font, textureText.c_str(), textColor );
    mTexture = SDL_CreateTextureFromSurface(des,textSurface);
    mWidth = textSurface->w;
    mHeight = textSurface->h;
    SDL_FreeSurface( textSurface );
}
void LTexture::free() {
	if( mTexture != NULL ) {
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}
void LTexture::render(SDL_Renderer* des,int x, int y) {
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	SDL_RenderCopy(des, mTexture,NULL,&renderQuad);
}
int LTexture::getWidth() {
	return mWidth;
}

int LTexture::getHeight() {
	return mHeight;
}

bool checkCollision( SDL_Rect a, SDL_Rect b ) {
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if(bottomB>=500){
        return false;
    }

    if( topA >= bottomB ){
        return false;
    }

    if( rightA <= leftB ) {
        return false;
    }

    if( leftA >= rightB ) {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}
