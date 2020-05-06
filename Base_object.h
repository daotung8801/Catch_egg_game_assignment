#ifndef BASE_OBJECT_H
#define BASE_OBJECT_H

#include<iostream>
#include<cstdlib>
#include<string>
#include<ctime>
#include<sstream>

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
using namespace std;

class LTexture{
	public:
		LTexture();
		~LTexture();
		void loadFromFile(SDL_Renderer* des,string path);
		void loadFromText(TTF_Font *Font,SDL_Renderer* des,string textureText, SDL_Color textColor );
		void free();
		void render(SDL_Renderer* des,int x, int y);
		int getWidth();
		int getHeight();

	private:
		SDL_Texture* mTexture;
		int mWidth;
		int mHeight;
};

bool checkCollision( SDL_Rect a, SDL_Rect b );
#endif
