#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mouse.h>
#include <string.h>
#include <unistd.h>
#include <ctime>
#include <time.h>       /* time */
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

//LTexture, Window, and Initialize stuff
#include "init.h"

//Globally used font
TTF_Font *gFont12 = NULL;
TTF_Font *gFont21 = NULL;

//LTexture
LTexture gText;


bool loadMedia() {
	bool success = true;
	gFont12 = TTF_OpenFont("resource/fonts/Viga-Regular.ttf", 12);
	gFont21 = TTF_OpenFont("resource/fonts/Viga-Regular.ttf", 21);

	return success;
}

void close() {
	TTF_CloseFont(gFont12);
	TTF_CloseFont(gFont21);
	gFont12 = NULL;
	gFont21 = NULL;
	gText.free();

	SDL_DestroyRenderer(gRenderer);
	gWindow.free();

	//Quit SDL subsystems
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}


int main(int argc, char **argv) {

	init();
	loadMedia();

	bool quit = false;

	// Level size
	int mapX = 0;
	int mapY = 0;
	int mapW = 2096;
	int mapH = 1080;

	// House
	int houseX = 800;
	int houseY = 200;
	int houseW = 500;
	int houseH = 350;

	//Mouse
	int mx, my;

	// Player1
	float x = 0+1280/2 - 32/2 - 200;
	float y = 0+720/2 - 32/2;
	int w = 24;
	int h = 24;
	bool moving = false;
	bool moveL = false;
	bool moveR = false;
	bool moveU = false;
	bool moveD = false;
    float velX = 0.0, velY = 0.0;

	//Player 2
	float x2 = 1500;
	float y2 = 245;
	int w2 = 24;
	int h2 = 24;
	bool movePlayer2ToStart = false;
	bool moveL2 = false;
	bool moveR2 = false;
	bool moveU2 = false;
	bool moveD2 = false;

	int mouseWheelY = 0;

	float camx = 0, camy = 0;

	while (!quit) {

		// Camera target distance
		float bmx, bmy;
		bmx  = x+w/2-gWindow.getWidth()/2;
		bmy  = y+h/2-gWindow.getHeight()/2;
		float distance = sqrt((bmx - camx) * (bmx - camx)+
							  (bmy - camy) * (bmy - camy));

		// Camera target
		float vX, vY;
		if (distance > 0.5){
			vX 	= 2 * (10*distance/600) * (bmx - camx) / distance;
			vY 	= 2 * (10*distance/600) * (bmy - camy) / distance;
		}
		camx += vX;
		camy += vY;

		// Camera bounds
		if( camx < 0 ){
			camx = 0;
		}
		if( camy < 0 ){
			camy = 0;
		}
		if( camx+gWindow.getWidth() > mapW ){
			camx = mapW-gWindow.getWidth() ;
		}
		if( camy+gWindow.getHeight()  > mapH ){
			camy = mapH-gWindow.getHeight() ;
		}

		//Get mouse x, y positions
		SDL_GetMouseState(&mx, &my);


		SDL_Event e;
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
			}

			//Handle window events
			gWindow.handleEvent(e);

			//If Key Pressed
			if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
				switch (e.key.keysym.sym) {
				case SDLK_w:
					moveU = true;
					break;
				case SDLK_s:
					moveD = true;
					break;
				case SDLK_a:
					moveL = true;
					break;
				case SDLK_d:
					moveR = true;
					break;
				}
			}
			//If Key Released
			else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
				switch (e.key.keysym.sym) {
				case SDLK_w:
					moveU = false;
					break;
				case SDLK_s:
					moveD = false;
					break;
				case SDLK_a:
					moveL = false;
					break;
				case SDLK_d:
					moveR = false;
					break;
				}
			}
			if (e.type == SDL_MOUSEWHEEL) {
					mouseWheelY = e.wheel.y;
			}
			if (e.type == SDL_MOUSEBUTTONDOWN) {
				if (e.button.button == SDL_BUTTON_LEFT) {
					//
				}
				if (e.button.button == SDL_BUTTON_RIGHT) {
					//
				}
			}
			if (e.type == SDL_MOUSEBUTTONUP) {
				if (e.button.button == SDL_BUTTON_LEFT) {
					//
				}
			}
		} // end controls

		// Update Player controls
		if (moveU){
			velY -= 1;
			moving = true;
		}else if (moveD){
			velY += 1;
			moving = true;
		}
		if (moveL){
			velX -= 1;
			moving = true;
		}else if (moveR){
			velX += 1;
			moving = true;
		}

		// Max velocity
		if (velX > 6){
			velX = 6;
		}
		if (velX < -6){
			velX = -6;
		}
		if (velY > 6){
			velY = 6;
		}
		if (velY < -6){
			velY = -6;
		}

		// Player velocity
		x += velX;
		y += velY;

		// Drag coefficient
		if (!moveU && !moveD){
			velY = velY - velY * 0.5;
		}
		if (!moveL && !moveR){
			velX = velX - velX * 0.5;
		}

		// Player stopped moving, start Idle animation
		if (!moveU && !moveD && !moveL && !moveR){
			moving = false;
		}

		// Player bounds
		if( x < 0 ){
			x = 0;
		}
		if( y < 0 ){
			y = 0;
		}
		if( x+w > mapW ){
			x = mapW-w ;
		}
		if( y+h  > mapH ){
			y = mapH-h ;
		}

		// Event, Check if Player1 entered House (Arena)
		if (checkCollision(x, y, w, h, houseX, houseY, houseW, houseH))
		{
			movePlayer2ToStart = true;
		}

		// Event, move Player2 inside House
		if (movePlayer2ToStart){
			float bmx, bmy;
			bmx  = houseX+houseW-w2-35;
			bmy  = houseY+h2+125;
			float distance = sqrt((bmx - x2-w2/2) * (bmx - x2-w2/2)+
								  (bmy - y2-h2/2) * (bmy - y2-h2/2));

			// Player2
			float vX, vY;
			if (distance > 0.5){
				vX 	= 2 * (10*distance/600) * (bmx - x2-w2/2) / distance;
				vY 	= 2 * (10*distance/600) * (bmy - y2-h2/2) / distance;
			}
			x2 += vX;
			y2 += vY;
		}

		//Clear render screen
		SDL_SetRenderDrawColor(gRenderer, 0, 50, 50, 255);
		SDL_RenderClear(gRenderer);

			// Render game Title
			std::stringstream tempss;
			tempss.str(std::string());
			tempss << "Two ____ Walk into a...: ";
			gText.loadFromRenderedText(tempss.str().c_str(), white, gFont12);
			gText.render(0, 0, gText.getWidth(), gText.getHeight());


			// Render House name
			tempss.str(std::string());
			tempss << "HOUSE OF LIARS";
			gText.loadFromRenderedText(tempss.str().c_str(), red, gFont21);
			gText.render(houseX+houseW/2-gText.getWidth()/2-camx, houseY+10-camy, gText.getWidth(), gText.getHeight());

			// Render Player1
			SDL_Rect tempR = { x-camx, y-camy, w, h };
			SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
			SDL_RenderFillRect(gRenderer, &tempR);

			// Render Player2
			SDL_Rect tempR2 = { x2-camx, y2-camy, w2, h2 };
			SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
			SDL_RenderFillRect(gRenderer, &tempR2);

			// Render House
			SDL_Rect tempHouse = { houseX-camx, houseY-camy, houseW, houseH };
			SDL_SetRenderDrawColor(gRenderer, 200, 0, 0, 255);
			SDL_RenderDrawRect(gRenderer, &tempHouse);

			// Render Map
			SDL_Rect tempMap = { mapX-camx, mapY-camy, mapW, mapH };
			SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 255);
			SDL_RenderDrawRect(gRenderer, &tempMap);


		SDL_RenderPresent(gRenderer);
	}
	close();			//Free resources and close SDL
	return 0;
}
