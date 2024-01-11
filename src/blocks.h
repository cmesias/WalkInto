struct Blockc {
public:
	int x;
	int y;
	int w;
	int h;
	bool alive;
	bool collision;
	bool collide;
	bool MouseOnBlockc;
	string s;
	string type;
};
void initBlockc(Blockc blockc[]) {
	for (int i = 0; i < 6000; i++) {
		blockc[i].x = 0;
		blockc[i].y = 0;
		blockc[i].w = 0;
		blockc[i].h = 0;
		blockc[i].alive = false;
		blockc[i].collision = false;
		blockc[i].collide = false;
		blockc[i].MouseOnBlockc = false;
		blockc[i].s = "";
	}
}
void placeBlockc(Blockc blockc[], int x, int y, int w, int h, bool collision, string type) {
	for (int i = 0; i < 6000; i++) {
		if (!blockc[i].alive) {
			blockc[i].type = type;
			blockc[i].x = x;
			blockc[i].y = y;
			blockc[i].w = w;
			blockc[i].h = h;
			blockc[i].collision = collision;

			blockc[i].alive = true;
			collisionBlocks++;
			break;

		}
	}
}

void placeBlockcAllTypes(Blockc blockc[]){
	//PLACE BLOCK DEPENDING ON WHICH ONE YOU CHOSE (index number)
	if (inventoryIndexBlockc == 1) {
		for (int i = 0; i < HOWMANYBLOCKSW; i++) {
			for (int h = 0; h < HOWMANYBLOCKSH; h++) {
				placeBlockc(blockc,BLOCKX + i * BLOCKW,
								   BLOCKY + h * BLOCKW,
								   BLOCKW, BLOCKH,
								   false, "OnlyPlayer");
			}
		}
	} else if (inventoryIndexBlockc == 2) {
		for (int i = 0; i < HOWMANYBLOCKSW; i++) {
			for (int h = 0; h < HOWMANYBLOCKSH; h++) {
				placeBlockc(blockc,BLOCKX + i * BLOCKW,
								   BLOCKY + h * BLOCKW,
								   BLOCKW, BLOCKH,
								   false, "OnlyGhost");
			}
		}
	}
}




void removeBlockOnMousec(Blockc blockc[]) {
	//REMOVE THE BLOCK(s) YOU ARE CURRENTLY OVER
	for (int i = 0; i < 6000; i++) {
		if (blockc[i].alive) {
			if (inventoryIndexBlockc == 1){
				if (blockc[i].type == "OnlyPlayer") {
					if (blockc[i].MouseOnBlockc) {
						blockc[i].alive = false;
						collisionBlocks--;
					}
				}
			}
			if (inventoryIndexBlockc == 2){
				if (blockc[i].type == "OnlyGhost") {
					if (blockc[i].MouseOnBlockc) {
						blockc[i].alive = false;
						collisionBlocks--;
					}
				}
			}
		}
	}
}

void copyBlockcOnMouse(Blockc blockc[]) {
	//COPY THE WIDTH/HEIGHT OF THE BLOCK YOU ARE CURRENTLY OVER
	for (int i = 0; i < 6000; i++) {
		if (blockc[i].alive) {
			if (blockc[i].MouseOnBlockc){
				BLOCKX = blockc[i].x;
				BLOCKY = blockc[i].y;
				BLOCKW = blockc[i].w;
				BLOCKH = blockc[i].h;
				if (blockc[i].type == "OnlyPlayer") {
					inventoryIndexBlockc = 1;
				}
				if (blockc[i].type == "OnlyGhost") {
					inventoryIndexBlockc = 2;
				}
			}
		}
	}
}
void updateBlockc(Blockc blockc[],int camx,int camy, int mx, int my) {
	for (int i = 0; i < 6000; i++) {
		//if the the bullet is alive for x miliseconds it dissapears
		if (blockc[i].alive) {
			//If the mouse is on the block
			if (mx-camx > blockc[i].x-camx && mx-camx < blockc[i].x + blockc[i].w-camx &&
				my-camy > blockc[i].y-camy && my-camy < blockc[i].y + blockc[i].h-camy) {
				blockc[i].MouseOnBlockc = true;
			} else {
				blockc[i].MouseOnBlockc = false;
			}
		}
	}
}



void renderBlockc(Blockc blockc[], int camx, int camy) {
	for (int i = 0; i < 6000; i++) {
		if (blockc[i].alive) {
			if (debug){
				if (blockc[i].MouseOnBlockc){
					SDL_Rect blockcb = { blockc[i].x+5 - camx, blockc[i].y+5 - camy,blockc[i].w-10, blockc[i].h-10 };
					SDL_SetRenderDrawColor(gRenderer, 244, 124, 0, 255);
					SDL_RenderDrawRect(gRenderer, &blockcb);
				}
				if (blockc[i].type == "OnlyPlayer") {
					SDL_Rect blockcb = { blockc[i].x - camx, blockc[i].y - camy,blockc[i].w, blockc[i].h };
					SDL_SetRenderDrawColor(gRenderer, 0,0,244, 255);
					SDL_RenderDrawRect(gRenderer, &blockcb);
				}
				if (blockc[i].type == "OnlyGhost") {
					SDL_Rect blockcb = { blockc[i].x - camx, blockc[i].y - camy,blockc[i].w, blockc[i].h };
					SDL_SetRenderDrawColor(gRenderer, 244,144,0, 255);
					SDL_RenderDrawRect(gRenderer, &blockcb);
				}
			}
		}
	}
}
void renderBlockcGhost(Blockc blockc[], int camx, int camy) {
	if (inventoryIndexBlockc==1){
		SDL_Rect blockcb = { BLOCKX-camx, BLOCKY-camy, BLOCKW, BLOCKH };
		SDL_SetRenderDrawColor(gRenderer, 0,0,244, 255);
		SDL_RenderDrawRect(gRenderer, &blockcb);
	}
	if (inventoryIndexBlockc==2){
		SDL_Rect blockcb = { BLOCKX-camx, BLOCKY-camy, BLOCKW, BLOCKH };
		SDL_SetRenderDrawColor(gRenderer, 244,144,0, 255);
		SDL_RenderDrawRect(gRenderer, &blockcb);
	}
}





/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////// Blocks /////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Block {
public:
	int x;
	int y;
	int w;
	int h;
	int time;
	float a;
	bool alive;
	bool collide;
	bool inVision;
	bool onScreen;
	string collision;
	bool tcollision;
	string blockType;
	string s;
	double speed;
	float vX;
	float vY;
	float distance;
	float mDistanceXLeft;
	float mDistanceXRight;
	float mDistanceYTop;
	float mDistanceYBot;
	int Bmx;
	int Bmy;
	int alpha;
	bool MouseOnPlacement;
	int onmouse;
	SDL_Rect clips = { x, y, w, h };
	bool calculateDistance;
};
void initBlock(Block block[]) {
	for (int i = 0; i < 6000; i++) {
		block[i].tcollision = true;
		block[i].calculateDistance = true;
		block[i].onmouse = 0;
		block[i].onScreen = false;
		block[i].MouseOnPlacement = false;
		block[i].collide = false;
		block[i].alive = false;
		block[i].s = "right";
	}
}
void placeBlockI(Block block[], int x, int y, int w, int h, int startx,
		int starty, int endW, int endH, float a, string blockType,
		string collision) {
	for (int i = 0; i < 6000; i++) {
		if (!block[i].alive) {
			block[i].alpha = 255;
			block[i].x = x;
			block[i].y = y;

			block[i].clips.x = startx;
			block[i].clips.y = starty;
			block[i].clips.w = endW;
			block[i].clips.h = endH;

			block[i].w = w;
			block[i].h = h;
			block[i].a = a;
			block[i].blockType = blockType;
			block[i].collision = collision;

			block[i].alive = true;
			Blocks++;
			break;

		}
	}
}



void placeBlockAllTypes(Block block[]){
	//PLACE BLOCK DEPENDING ON WHICH ONE YOU CHOSE (index number)
	if (inventoryIndex == 1) {
		for (int i = 0; i < HOWMANYBLOCKSW; i++) {
			for (int h = 0; h < HOWMANYBLOCKSH; h++) {
				placeBlockI(block, BLOCKX + i * BLOCKW, BLOCKY + h * BLOCKH,
						BLOCKW, BLOCKH, BLOCK.x, BLOCK.y,
						BLOCK.w, BLOCK.h, 0.0,
						"grass", "off");
			}
		}
	} else if (inventoryIndex == 2) {
		for (int i = 0; i < HOWMANYBLOCKSW; i++) {
			for (int h = 0; h < HOWMANYBLOCKSH; h++) {
				placeBlockI(block, BLOCKX + i * BLOCKW, BLOCKY + h * BLOCKH,
						BLOCKW, BLOCKH, BLOCK.x, BLOCK.y,
						BLOCK.w, BLOCK.h, 0.0,
						"grass-light", "off");
			}
		}
	} else if (inventoryIndex == 3) {
		for (int i = 0; i < HOWMANYBLOCKSW; i++) {
			for (int h = 0; h < HOWMANYBLOCKSH; h++) {
				placeBlockI(block,
						BLOCKX + i * BLOCKW, BLOCKY + h * BLOCKH,
						BLOCKW, BLOCKH, BLOCK.x, BLOCK.y,
						BLOCK.w, BLOCK.h, 0.0,
						"grass-dark", "off");
			}
		}

	} else if (inventoryIndex == 4) {
		for (int i = 0; i < HOWMANYBLOCKSW; i++) {
			for (int h = 0; h < HOWMANYBLOCKSH; h++) {
				placeBlockI(block, BLOCKX + i * BLOCKW, BLOCKY + h * BLOCKH,
					BLOCKW, BLOCKH, BLOCK.x, BLOCK.y,
					BLOCK.w, BLOCK.h, 0.0,"water","on");
			}
		}
	} else if (inventoryIndex == 5) {
		for (int i = 0; i < HOWMANYBLOCKSW; i++) {
			for (int h = 0; h < HOWMANYBLOCKSH; h++) {
			placeBlockI(block, BLOCKX + i * BLOCKW, BLOCKY + h * BLOCKH,
					BLOCKW, BLOCKH, BLOCK.x, BLOCK.y,
					BLOCK.w, BLOCK.h, 0.0,
					"hill-small", "on");
			}
		}
	} else if (inventoryIndex == 6) {
		for (int i = 0; i < HOWMANYBLOCKSW; i++) {
			for (int h = 0; h < HOWMANYBLOCKSH; h++) {
			placeBlockI(block, BLOCKX + i * BLOCKW, BLOCKY + h * BLOCKH,
					BLOCKW, BLOCKH, BLOCK.x, BLOCK.y,
					BLOCK.w, BLOCK.h, 0.0,
					"hill-medium", "on");
			}
		}
	} else if (inventoryIndex == 7) {
		for (int i = 0; i < HOWMANYBLOCKSW; i++) {
			for (int h = 0; h < HOWMANYBLOCKSH; h++) {
			placeBlockI(block, BLOCKX + i * BLOCKW, BLOCKY + h * BLOCKH,
					BLOCKW, BLOCKH, BLOCK.x, BLOCK.y,
					BLOCK.w, BLOCK.h, 0.0,
					"hill-large", "on");
			}
		}
	} else if (inventoryIndex == 8) {
		for (int i = 0; i < HOWMANYBLOCKSW; i++) {
			for (int h = 0; h < HOWMANYBLOCKSH; h++) {
			placeBlockI(block, BLOCKX + i * BLOCKW, BLOCKY + h * BLOCKH,
					BLOCKW, BLOCKH, BLOCK.x, BLOCK.y,
					BLOCK.w, BLOCK.h, 0.0,
					"spawn-point", "off");
			}
		}
	} else if (inventoryIndex == 9) {
		for (int i = 0; i < HOWMANYBLOCKSW; i++) {
			for (int h = 0; h < HOWMANYBLOCKSH; h++) {
			placeBlockI(block, BLOCKX + i * BLOCKW, BLOCKY + h * BLOCKH,
					BLOCKW, BLOCKH, BLOCK.x, BLOCK.y,
					BLOCK.w, BLOCK.h, 0.0,
					"stone", "on");
			}
		}
	} else if (inventoryIndex == 10) {
		for (int i = 0; i < HOWMANYBLOCKSW; i++) {
			for (int h = 0; h < HOWMANYBLOCKSH; h++) {
			placeBlockI(block, BLOCKX + i * BLOCKW, BLOCKY + h * BLOCKH,
					BLOCKW, BLOCKH, BLOCK.x, BLOCK.y,
					BLOCK.w, BLOCK.h, 0.0,
					"stone-n", "off");
			}
		}
	} else if (inventoryIndex == 11) {
		for (int i = 0; i < HOWMANYBLOCKSW; i++) {
			for (int h = 0; h < HOWMANYBLOCKSH; h++) {
			placeBlockI(block, BLOCKX + i * BLOCKW, BLOCKY + h * BLOCKH,
					BLOCKW, BLOCKH, BLOCK.x, BLOCK.y,
					BLOCK.w, BLOCK.h, 0.0,
					"stone-s", "off");
			}
		}
	} else if (inventoryIndex == 12) {
		for (int i = 0; i < HOWMANYBLOCKSW; i++) {
			for (int h = 0; h < HOWMANYBLOCKSH; h++) {
			placeBlockI(block, BLOCKX + i * BLOCKW, BLOCKY + h * BLOCKH,
					BLOCKW, BLOCKH, BLOCK.x, BLOCK.y,
					BLOCK.w, BLOCK.h, 0.0,
					"stone-w", "off");
			}
		}
	} else if (inventoryIndex == 13) {
		for (int i = 0; i < HOWMANYBLOCKSW; i++) {
			for (int h = 0; h < HOWMANYBLOCKSH; h++) {
			placeBlockI(block, BLOCKX + i * BLOCKW, BLOCKY + h * BLOCKH,
					BLOCKW, BLOCKH, BLOCK.x, BLOCK.y,
					BLOCK.w, BLOCK.h, 0.0,
					"stone-e", "off");
			}
		}
	}  else if (inventoryIndex == 14) {
		for (int i = 0; i < HOWMANYBLOCKSW; i++) {
			for (int h = 0; h < HOWMANYBLOCKSH; h++) {
			placeBlockI(block, BLOCKX + i * BLOCKW, BLOCKY + h * BLOCKH,
					BLOCKW, BLOCKH, BLOCK.x, BLOCK.y,
					BLOCK.w, BLOCK.h, 0.0,
					"stone-nw", "off");
			}
		}
	}  else if (inventoryIndex == 15) {
		for (int i = 0; i < HOWMANYBLOCKSW; i++) {
			for (int h = 0; h < HOWMANYBLOCKSH; h++) {
			placeBlockI(block, BLOCKX + i * BLOCKW, BLOCKY + h * BLOCKH,
					BLOCKW, BLOCKH, BLOCK.x, BLOCK.y,
					BLOCK.w, BLOCK.h, 0.0,
					"stone-ne", "off");
			}
		}
	}  else if (inventoryIndex == 16) {
		for (int i = 0; i < HOWMANYBLOCKSW; i++) {
			for (int h = 0; h < HOWMANYBLOCKSH; h++) {
			placeBlockI(block, BLOCKX + i * BLOCKW, BLOCKY + h * BLOCKH,
					BLOCKW, BLOCKH, BLOCK.x, BLOCK.y,
					BLOCK.w, BLOCK.h, 0.0,
					"stone-sw", "off");
			}
		}
	}  else if (inventoryIndex == 17) {
		for (int i = 0; i < HOWMANYBLOCKSW; i++) {
			for (int h = 0; h < HOWMANYBLOCKSH; h++) {
			placeBlockI(block, BLOCKX + i * BLOCKW, BLOCKY + h * BLOCKH,
					BLOCKW, BLOCKH, BLOCK.x, BLOCK.y,
					BLOCK.w, BLOCK.h, 0.0,
					"stone-se", "off");
			}
		}
	}  else if (inventoryIndex == 18) {
		for (int i = 0; i < HOWMANYBLOCKSW; i++) {
			for (int h = 0; h < HOWMANYBLOCKSH; h++) {
			placeBlockI(block, BLOCKX + i * BLOCKW, BLOCKY + h * BLOCKH,
					BLOCKW, BLOCKH, BLOCK.x, BLOCK.y,
					BLOCK.w, BLOCK.h, 0.0,
					"stone-blank", "off");
			}
		}
	}  else if (inventoryIndex == 19) {
		for (int i = 0; i < HOWMANYBLOCKSW; i++) {
			for (int h = 0; h < HOWMANYBLOCKSH; h++) {
			placeBlockI(block, BLOCKX + i * BLOCKW, BLOCKY + h * BLOCKH,
					BLOCKW, BLOCKH, BLOCK.x, BLOCK.y,
					BLOCK.w, BLOCK.h, 0.0,
					"block", "off");
			}
		}
	}  else if (inventoryIndex == 20) {
		for (int i = 0; i < HOWMANYBLOCKSW; i++) {
			for (int h = 0; h < HOWMANYBLOCKSH; h++) {
			placeBlockI(block, BLOCKX + i * BLOCKW, BLOCKY + h * BLOCKH,
					BLOCKW, BLOCKH, BLOCK.x, BLOCK.y,
					BLOCK.w, BLOCK.h, 0.0,
					"door", "off");
			}
		}
	}







	else {
		//If Mouse distance is greater than playerRadiusShootShoot, Player may shoot
		//gunShootIni = true; //Shoot shit
	}
}





void removeBlockOnMouse(Block block[]) {
	//REMOVE THE BLOCK(s) YOU ARE CURRENTLY OVER
	for (int i = 0; i < 6000; i++) {
		if (block[i].alive) {
			if (block[i].MouseOnPlacement) {
				block[i].alive = false;
				Blocks--;
			}
		}
	}
}


void EnableDisableCollision(Block block[]) {
	for (int i = 0; i < 6000; i++) {
		if (block[i].alive) {
			if (block[i].MouseOnPlacement) {
				block[i].collision == "on";
			}
		}
	}
}
void copyBlockOnMouse(Block block[]) {
	//COPY THE WIDTH/HEIGHT OF THE BLOCK YOU ARE CURRENTLY OVER
	for (int i = 0; i < 6000; i++) {
		if (block[i].alive) {
			if (block[i].MouseOnPlacement){
				BLOCKX = block[i].x;
				BLOCKY = block[i].y;
				BLOCKW = block[i].w;
				BLOCKH = block[i].h;
				BLOCK.x = block[i].clips.x;
				BLOCK.y = block[i].clips.y;
				BLOCK.w = block[i].clips.w;
				BLOCK.h = block[i].clips.h;

				if (block[i].blockType == "grass") {
					inventoryIndex = 1;
				}
				if (block[i].blockType == "grass-light") {
					inventoryIndex = 2;
				}
				if (block[i].blockType == "grass-dark") {
					inventoryIndex = 3;
				}
				if (block[i].blockType == "water") {
					inventoryIndex = 4;
				}
				if (block[i].blockType == "hill-small") {
					inventoryIndex = 5;
				}
				if (block[i].blockType == "hill-medium") {
					inventoryIndex = 6;
				}
				if (block[i].blockType == "hill-large") {
					inventoryIndex = 7;
				}
				if (block[i].blockType == "spawn-point") {
					inventoryIndex = 8;
				}
				if (block[i].blockType == "stone") {
					inventoryIndex = 9;
				}
				if (block[i].blockType == "stone-n") {
					inventoryIndex = 10;
				}
				if (block[i].blockType == "stone-s") {
					inventoryIndex = 11;
				}
				if (block[i].blockType == "stone-w") {
					inventoryIndex = 12;
				}
				if (block[i].blockType == "stone-e") {
					inventoryIndex = 13;
				}
				if (block[i].blockType == "stone-nw") {
					inventoryIndex = 14;
				}
				if (block[i].blockType == "stone-ne") {
					inventoryIndex = 15;
				}
				if (block[i].blockType == "stone-sw") {
					inventoryIndex = 16;
				}
				if (block[i].blockType == "stone-se") {
					inventoryIndex = 17;
				}
				if (block[i].blockType == "stone-blank") {
					inventoryIndex = 18;
				}
				if (block[i].blockType == "block") {
					inventoryIndex = 19;
				}
				if (block[i].blockType == "door") {
					inventoryIndex = 20;
				}
			}
		}
	}
}

void updateBlock(Block block[], int targetX, int targetY, int targetRadius, int camx, int camy, int mx, int my) {
//void updateBlock(Block block[], int camx,int camy, int mx, int my) {
	for (int i = 0; i < 6000; i++) {
		//if the the bullet is alive for x miliseconds it dissapears
		if (block[i].alive) {

			//MAGNET PLACEMENT EFFECT
			//Calculate distance of mouse and LEFT side of a block
			block[i].mDistanceXLeft = sqrt((BLOCKX - block[i].x)* (BLOCKX - block[i].x));
			if (block[i].mDistanceXLeft <= 5) {
				BLOCKX = block[i].x;
			}
			//Calculate distance of mouse and RIGHT side of a block
			block[i].mDistanceXRight = sqrt((BLOCKX - block[i].x-block[i].w)* (BLOCKX - block[i].x-block[i].w));
			if (block[i].mDistanceXRight <= 5) {
				BLOCKX = block[i].x+block[i].w;
			}
			//Calculate distance of mouse and TOP side of a block
			block[i].mDistanceYTop = sqrt((BLOCKY - block[i].y)* (BLOCKY - block[i].y));
			if (block[i].mDistanceYTop <= 5) {
				BLOCKY = block[i].y;
			}
			//Calculate distance of mouse and BOT side of a block
			block[i].mDistanceYBot = sqrt((BLOCKY - block[i].y-block[i].h)* (BLOCKY - block[i].y-block[i].h));
			if (block[i].mDistanceYBot <= 5) {
				BLOCKY = block[i].y+block[i].h;
			}


			block[i].Bmx = targetX;
			block[i].Bmy = targetY;
			block[i].distance = sqrt(
					(block[i].Bmx - block[i].x - block[i].w / 2)
							* (block[i].Bmx - block[i].x - block[i].w / 2)
							+ (block[i].Bmy - block[i].y - block[i].h / 2)
									* (block[i].Bmy - block[i].y
											- block[i].h / 2));
			float angleZ = atan2(block[i].Bmy - block[i].y,
					block[i].Bmx - block[i].x);
			block[i].a = angleZ * (180 / 3.1416);

			if (block[i].distance < targetRadius + block[i].w / 2) {
				block[i].inVision = true;
			} else {
				block[i].inVision = false;
			}

			//If the block is in the screen
			if (block[i].x + block[i].w >= camx-64
					&& block[i].x <= camx-64 + gWindow.getWidth()+128
					&& block[i].y + block[i].h >= camy-64
					&& block[i].y <= camy-64 + gWindow.getHeight()+128) {
				block[i].onScreen = true;
			} else {
				block[i].onScreen = false;
			}

			//If the mouse is on the block
			if (mx-camx > block[i].x-camx && mx-camx < block[i].x + block[i].w-camx &&
				my-camy > block[i].y-camy && my-camy < block[i].y + block[i].h-camy) {
				block[i].MouseOnPlacement = true;
				block[i].onmouse = 1;
			} else {
				block[i].MouseOnPlacement = false;
				block[i].onmouse = 0;
			}
		}
	}
}

void renderBlock(Block block[], int camX, int camY) {
	for (int i = 0; i < 6000; i++) {
		if (block[i].alive) {
			//block[i].alpha = 255;
			if (block[i].onScreen) {
				//if (block[i].inVision) {
					/*change NULL with &block[i].clips */
					if (block[i].blockType == "grass") {
						gTile01.setAlpha(block[i].alpha);
						gTile01.render(block[i].x - camX, block[i].y - camY,
								block[i].w, block[i].h, &block[i].clips, 0);
					}
					if (block[i].blockType == "grass-light") {
						gGrassLight.setAlpha(block[i].alpha);
						gGrassLight.render(block[i].x - camX, block[i].y - camY,
								block[i].w, block[i].h, &block[i].clips, 0);
					}
					if (block[i].blockType == "grass-dark") {
						gGrassDark.setAlpha(block[i].alpha);
						gGrassDark.render(block[i].x - camX, block[i].y - camY,
								block[i].w, block[i].h, &block[i].clips, 0);
					}
					if (block[i].blockType == "spawn-point") {
						if (debug){
							gSpawnPoint.setAlpha(block[i].alpha);
							gSpawnPoint.render(block[i].x - camX, block[i].y - camY,
									block[i].w, block[i].h, &block[i].clips, 0);
						}
					}
					if (block[i].blockType == "water") {
						gWater.setAlpha(block[i].alpha);
						gWater.render(block[i].x - camX, block[i].y - camY,
								block[i].w, block[i].h, &block[i].clips, 0);
					}
					if (block[i].blockType == "hill-small") {
						gHillSmall.setAlpha(block[i].alpha);
						gHillSmall.render(block[i].x - camX, block[i].y - camY,
								block[i].w, block[i].h,
								&block[i].clips, 0);
					}
					if (block[i].blockType == "hill-medium") {
						gHillMedium.setAlpha(block[i].alpha);
						gHillMedium.render(block[i].x - camX, block[i].y - camY,
								block[i].w, block[i].h,
								&block[i].clips, 0);
					}
					if (block[i].blockType == "hill-large") {
						gHillLarge.setAlpha(block[i].alpha);
						gHillLarge.render(block[i].x - camX, block[i].y - camY,
								block[i].w, block[i].h,
								&block[i].clips, 0);
					}
					if (block[i].blockType == "stone") {
						gStone.setAlpha(block[i].alpha);
						SDL_Rect stonen = { 128, 128, 128, 128 };
						gStone.render(block[i].x - camX, block[i].y - camY,
								block[i].w, block[i].h,
								&stonen, 0);
					}
					if (block[i].blockType == "stone-n") {
						gStone.setAlpha(block[i].alpha);
						SDL_Rect stonen = { 128, 0, 128, 128 };
						gStone.render(block[i].x - camX, block[i].y - camY,
								block[i].w, block[i].h,
								&stonen, 0);
					}
					if (block[i].blockType == "stone-s") {
						gStone.setAlpha(block[i].alpha);
						SDL_Rect stones = { 128, 256, 128, 128 };
						gStone.render(block[i].x - camX, block[i].y - camY,
								block[i].w, block[i].h,
								&stones, 0);
					}
					if (block[i].blockType == "stone-w") {
						gStone.setAlpha(block[i].alpha);
						SDL_Rect stonew = { 0, 128, 128, 128 };
						gStone.render(block[i].x - camX, block[i].y - camY,
								block[i].w, block[i].h,
								&stonew, 0);
					}
					if (block[i].blockType == "stone-e") {
						gStone.setAlpha(block[i].alpha);
						SDL_Rect stonee = { 256, 128, 128, 128 };
						gStone.render(block[i].x - camX, block[i].y - camY,
								block[i].w, block[i].h,
								&stonee, 0);
					}

					if (block[i].blockType == "stone-nw") {
						gStone.setAlpha(block[i].alpha);
						SDL_Rect stonenw = { 0, 0, 128, 128 };
						gStone.render(block[i].x - camX, block[i].y - camY,
								block[i].w, block[i].h,
								&stonenw, 0);
					}
					if (block[i].blockType == "stone-ne") {
						gStone.setAlpha(block[i].alpha);
						SDL_Rect stonese = { 256, 0, 128, 128 };
						gStone.render(block[i].x - camX, block[i].y - camY,
								block[i].w, block[i].h,
								&stonese, 0);
					}
					if (block[i].blockType == "stone-sw") {
						gStone.setAlpha(block[i].alpha);
						SDL_Rect stonesw = { 0, 256, 128, 128 };
						gStone.render(block[i].x - camX, block[i].y - camY,
								block[i].w, block[i].h,
								&stonesw, 0);
					}
					if (block[i].blockType == "stone-se") {
						gStone.setAlpha(block[i].alpha);
						SDL_Rect stonese = { 256, 256, 128, 128 };
						gStone.render(block[i].x - camX, block[i].y - camY,
								block[i].w, block[i].h,
								&stonese, 0);
					}
					if (block[i].blockType == "stone-blank") {
						gStoneBlank.setAlpha(block[i].alpha);
						gStoneBlank.render(block[i].x - camX, block[i].y - camY,
								block[i].w, block[i].h,
								&block[i].clips, 0);
					}
					if (block[i].blockType == "block") {
						//if player is inside of the block, make it transparent so we can see player
						if (block[i].collide) {
							if (block[i].alpha > 110){
								block[i].alpha -= 10;
							}
						}else{
							if (block[i].alpha < 240){
								block[i].alpha += 10;
							}
						}
						gBlock.setAlpha(block[i].alpha);
						gBlock.render(block[i].x - camX, block[i].y - camY,
								block[i].w, block[i].h,
								&block[i].clips, 0);
					}

				//}
			}
			//If Mouse is over block, draw an indicator border
			if (block[i].MouseOnPlacement){
				SDL_Rect mouseOnBlockRect = { block[i].x - camX, block[i].y - camY,block[i].w, block[i].h };
				SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
				SDL_RenderDrawRect(gRenderer, &mouseOnBlockRect);
			}

			//Show distance of Mouse and the 4 sides of a Block - Used for 'Magnet' placement effect
			if (debug){
				/*if (block[i].mDistanceXLeft < 100) {
					std::stringstream blocksw;
					blocksw << block[i].mDistanceXLeft;
					gText.loadFromRenderedText(blocksw.str().c_str(), { 255, 255, 255,255 }, gFont10);
					gText.render(block[i].x-camX, block[i].y+block[i].h/2-gText.getHeight()/2-camY, gText.getWidth(), gText.getHeight());
				}
				if (block[i].mDistanceXRight < 100) {
					std::stringstream blocksw;
					blocksw << block[i].mDistanceXRight;
					gText.loadFromRenderedText(blocksw.str().c_str(), { 255, 255, 255,255 }, gFont10);
					gText.render(block[i].x+block[i].w-gText.getWidth()-camX, block[i].y+block[i].h/2-gText.getHeight()/2-camY, gText.getWidth(), gText.getHeight());
				}
				if (block[i].mDistanceYTop < 100) {
					std::stringstream blocksw;
					blocksw << block[i].mDistanceYTop;
					gText.loadFromRenderedText(blocksw.str().c_str(), { 255, 255, 255,255 }, gFont10);
					gText.render(block[i].x+block[i].w/2-gText.getWidth()/2-camX, block[i].y-camY, gText.getWidth(), gText.getHeight());
				}
				if (block[i].mDistanceYBot < 100) {
					std::stringstream blocksw;
					blocksw << block[i].mDistanceYBot;
					gText.loadFromRenderedText(blocksw.str().c_str(), { 255, 255, 255,255 }, gFont10);
					gText.render(block[i].x+block[i].w/2-gText.getHeight()/2-camX, block[i].y+block[i].h-gText.getHeight()-camY, gText.getWidth(), gText.getHeight());
				}
				if (mx+camX == block[i].x){
					SDL_Rect tempLineX = { mx,my-500, 2, 1000 };
					SDL_SetRenderDrawColor(gRenderer, 0, 255, 255, 255);
					SDL_RenderDrawRect(gRenderer, &tempLineX);

					SDL_Rect tempLineX2 = { block[i].x-camX, block[i].y-camY, 5, block[i].h };
					SDL_SetRenderDrawColor(gRenderer, 0, 255, 255, 255);
					SDL_RenderFillRect(gRenderer, &tempLineX2);
				}
				//If the mouse is right of the block
				if (mx+camX == block[i].x+block[i].w){
					SDL_Rect tempLineX = { mx,my-500, 2, 1000 };
					SDL_SetRenderDrawColor(gRenderer, 0, 200, 0, 255);
					SDL_RenderDrawRect(gRenderer, &tempLineX);

					SDL_Rect tempLineX2 = { block[i].x+block[i].w-5-camX, block[i].y-camY, 5, block[i].h };
					SDL_SetRenderDrawColor(gRenderer, 0, 200, 0, 255);
					SDL_RenderFillRect(gRenderer, &tempLineX2);
				}

				if (my+camY == block[i].y){
					SDL_Rect tempLineX = { mx-500,my, 1000, 2 };
					SDL_SetRenderDrawColor(gRenderer, 255, 0, 255, 255);
					SDL_RenderDrawRect(gRenderer, &tempLineX);
				}
				if (my+camY == block[i].y+block[i].h){
					SDL_Rect tempLineX = { mx-500,my, 1000, 2 };
					SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 255);
					SDL_RenderDrawRect(gRenderer, &tempLineX);
				}*/
			}
		}
	}
}
//SDL_Rect BLOCK = { x, y, w, h };
void renderBlockGhost(Block block[], int inventoryIndex, int camx, int camy) {
	for (int i = 0; i < HOWMANYBLOCKSW; i++) {
		for (int h = 0; h < HOWMANYBLOCKSH; h++) {
			if (inventoryIndex == 1) {
				gTile01.setAlpha(110);
				gTile01.render(BLOCKX + i * BLOCKW-camx, BLOCKY + h * BLOCKH-camy,
						BLOCKW, BLOCKH, &BLOCK, 0);
			}
			if (inventoryIndex == 2) {
				gGrassLight.setAlpha(110);
				gGrassLight.render(BLOCKX + i * BLOCKW-camx, BLOCKY + h * BLOCKH-camy,
						BLOCKW, BLOCKH, &BLOCK, 0);
			}
			if (inventoryIndex == 3) {
				gGrassDark.setAlpha(110);
				gGrassDark.render(BLOCKX + i * BLOCKW-camx, BLOCKY + h * BLOCKH-camy,
						BLOCKW, BLOCKH, &BLOCK, 0);
			}
			if (inventoryIndex == 4) {
				gWater.setAlpha(110);
				gWater.render(BLOCKX  + i * BLOCKW-camx, BLOCKY  + h * BLOCKH-camy,
						BLOCKW, BLOCKH, &BLOCK, 0);
			}
			if (inventoryIndex == 5) {
				gHillSmall.setAlpha(110);
				gHillSmall.render(BLOCKX  + i * BLOCKW-camx, BLOCKY  + h * BLOCKH-camy,
						BLOCKW, BLOCKH, &BLOCK, 0);
			}
			if (inventoryIndex == 6) {
				gHillMedium.setAlpha(110);
				gHillMedium.render(BLOCKX  + i * BLOCKW-camx, BLOCKY  + h * BLOCKH-camy,
						BLOCKW, BLOCKH, &BLOCK, 0);
			}
			if (inventoryIndex == 7) {
				gHillLarge.setAlpha(110);
				gHillLarge.render(BLOCKX  + i * BLOCKW-camx, BLOCKY  + h * BLOCKH-camy,
						BLOCKW, BLOCKH, &BLOCK, 0);
			}
			if (inventoryIndex == 8) {
				gSpawnPoint.setAlpha(110);
				gSpawnPoint.render(BLOCKX  + i * BLOCKW-camx, BLOCKY  + h * BLOCKH-camy,
						BLOCKW, BLOCKH, &BLOCK, 0);
			}
			if (inventoryIndex == 9) {
				gStone.setAlpha(110);
				SDL_Rect stonee = { 128, 128, 128, 128 };
				gStone.render(BLOCKX  + i * BLOCKW-camx, BLOCKY  + h * BLOCKH-camy,
						BLOCKW, BLOCKH, &stonee, 0);
			}
			if (inventoryIndex == 10) {
				gStone.setAlpha(110);
				SDL_Rect stonen = { 128, 0, 128, 128 };
				gStone.render(BLOCKX  + i * BLOCKW-camx, BLOCKY  + h * BLOCKH-camy,
						BLOCKW, BLOCKH, &stonen, 0);
			}
			if (inventoryIndex == 11) {
				gStone.setAlpha(110);
				SDL_Rect stones = { 128, 256, 128, 128 };
				gStone.render(BLOCKX  + i * BLOCKW-camx, BLOCKY  + h * BLOCKH-camy,
						BLOCKW, BLOCKH, &stones, 0);
			}
			if (inventoryIndex == 12) {
				gStone.setAlpha(110);
				SDL_Rect stonew = { 0, 128, 128, 128 };
				gStone.render(BLOCKX  + i * BLOCKW-camx, BLOCKY  + h * BLOCKH-camy,
						BLOCKW, BLOCKH, &stonew, 0);
			}
			if (inventoryIndex == 13) {
				gStone.setAlpha(110);
				SDL_Rect stonee = { 256, 128, 128, 128 };
				gStone.render(BLOCKX  + i * BLOCKW-camx, BLOCKY  + h * BLOCKH-camy,
						BLOCKW, BLOCKH, &stonee, 0);
			}

			if (inventoryIndex == 14) {
				gStone.setAlpha(110);
				SDL_Rect stonenw = { 0, 0, 128, 128 };
				gStone.render(BLOCKX  + i * BLOCKW-camx, BLOCKY  + h * BLOCKH-camy,
						BLOCKW, BLOCKH, &stonenw, 0);
			}
			if (inventoryIndex == 15) {
				gStone.setAlpha(110);
				SDL_Rect stonene = { 256, 0, 128, 128 };
				gStone.render(BLOCKX  + i * BLOCKW-camx, BLOCKY  + h * BLOCKH-camy,
						BLOCKW, BLOCKH, &stonene, 0);
			}
			if (inventoryIndex == 16) {
				gStone.setAlpha(110);
				SDL_Rect stonesw = { 0, 256, 128, 128 };
				gStone.render(BLOCKX  + i * BLOCKW-camx, BLOCKY  + h * BLOCKH-camy,
						BLOCKW, BLOCKH, &stonesw, 0);
			}
			if (inventoryIndex == 17) {
				gStone.setAlpha(110);
				SDL_Rect stonese = { 256, 256, 128, 128 };
				gStone.render(BLOCKX  + i * BLOCKW-camx, BLOCKY  + h * BLOCKH-camy,
						BLOCKW, BLOCKH, &stonese, 0);
			}
			if (inventoryIndex == 18) {
				gStoneBlank.render(BLOCKX  + i * BLOCKW-camx, BLOCKY  + h * BLOCKH-camy,
						BLOCKW, BLOCKH, &BLOCK, 0);
			}
			if (inventoryIndex == 19) {
				gBlock.setAlpha(110);
				gBlock.render(BLOCKX  + i * BLOCKW-camx, BLOCKY  + h * BLOCKH-camy,
						BLOCKW, BLOCKH, &BLOCK, 0);
			}
		}
	}
}

//Disable placing blocks if we are hovering over changing buttons
void disablePlaceBlock( int mx, int my, SDL_Rect WIDTH_DECREASE, SDL_Rect WIDTH_INCREASE, SDL_Rect HEIGHT_DECREASE, SDL_Rect HEIGHT_INCREASE) {
	if (mx > WIDTH_DECREASE.x && mx < WIDTH_DECREASE.x+WIDTH_DECREASE.w && my > WIDTH_DECREASE.y && my < WIDTH_DECREASE.y+WIDTH_DECREASE.h) {
		PLACING_TYPE = 0;
	}
	if (mx > WIDTH_INCREASE.x && mx < WIDTH_INCREASE.x+WIDTH_INCREASE.w && my > WIDTH_INCREASE.y && my < WIDTH_INCREASE.y+WIDTH_INCREASE.h) {
		PLACING_TYPE = 0;
	}
	if (mx > HEIGHT_DECREASE.x && mx < HEIGHT_DECREASE.x+HEIGHT_DECREASE.w && my > HEIGHT_DECREASE.y && my < HEIGHT_DECREASE.y+HEIGHT_DECREASE.h) {
		PLACING_TYPE = 0;
	}
	if (mx > HEIGHT_INCREASE.x && mx < HEIGHT_INCREASE.x+HEIGHT_INCREASE.w && my > HEIGHT_INCREASE.y && my < HEIGHT_INCREASE.y+HEIGHT_INCREASE.h) {
		PLACING_TYPE = 0;
	}
}
void disablePlaceBlocksp( int mx, int my, SDL_Rect WIDTH_DECREASE, SDL_Rect WIDTH_INCREASE) {
	if (mx > WIDTH_DECREASE.x && mx < WIDTH_DECREASE.x+WIDTH_DECREASE.w && my > WIDTH_DECREASE.y && my < WIDTH_DECREASE.y+WIDTH_DECREASE.h) {
		PLACING_TYPE = 0;
	}
	if (mx > WIDTH_INCREASE.x && mx < WIDTH_INCREASE.x+WIDTH_INCREASE.w && my > WIDTH_INCREASE.y && my < WIDTH_INCREASE.y+WIDTH_INCREASE.h) {
		PLACING_TYPE = 0;
	}
}

//Draw WIDTH_DECREASE
void drawIncreaseDecreaseBox( SDL_Rect WIDTH_DECREASE, SDL_Rect WIDTH_INCREASE, SDL_Rect HEIGHT_DECREASE, SDL_Rect HEIGHT_INCREASE) {
	//Draw WIDTH_DECREASE
	SDL_Rect dec_wid = { WIDTH_DECREASE.x, WIDTH_DECREASE.y, WIDTH_DECREASE.w, WIDTH_DECREASE.h };
	SDL_SetRenderDrawColor(gRenderer, 160, 0, 0, 255);
	SDL_RenderFillRect(gRenderer, &dec_wid);
	SDL_Rect dec_widb = { WIDTH_DECREASE.x, WIDTH_DECREASE.y, WIDTH_DECREASE.w, WIDTH_DECREASE.h };
	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(gRenderer, &dec_widb);

	//Draw WIDTH_INCREASE
	SDL_Rect inc_wid = { WIDTH_INCREASE.x, WIDTH_INCREASE.y, WIDTH_INCREASE.w, WIDTH_INCREASE.h };
	SDL_SetRenderDrawColor(gRenderer, 0, 144, 0, 255);
	SDL_RenderFillRect(gRenderer, &inc_wid);
	SDL_Rect inc_widb = { WIDTH_INCREASE.x, WIDTH_INCREASE.y, WIDTH_INCREASE.w, WIDTH_INCREASE.h };
	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(gRenderer, &inc_widb);

	//Draw HEIGHT_DECREASE
	SDL_Rect dec_hei = { HEIGHT_DECREASE.x, HEIGHT_DECREASE.y, HEIGHT_DECREASE.w, HEIGHT_DECREASE.h };
	SDL_SetRenderDrawColor(gRenderer, 160, 0, 0, 255);
	SDL_RenderFillRect(gRenderer, &dec_hei);
	SDL_Rect dec_heib = { HEIGHT_DECREASE.x, HEIGHT_DECREASE.y, HEIGHT_DECREASE.w, HEIGHT_DECREASE.h };
	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(gRenderer, &dec_heib);

	//Draw HEIGHT_INCREASE
	SDL_Rect inc_hei = { HEIGHT_INCREASE.x, HEIGHT_INCREASE.y, HEIGHT_INCREASE.w, HEIGHT_INCREASE.h };
	SDL_SetRenderDrawColor(gRenderer, 0, 144, 0, 255);
	SDL_RenderFillRect(gRenderer, &inc_hei);
	SDL_Rect inc_heib = { HEIGHT_INCREASE.x, HEIGHT_INCREASE.y, HEIGHT_INCREASE.w, HEIGHT_INCREASE.h };
	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(gRenderer, &inc_heib);
}

void drawSpeedChangeBox(SDL_Rect SPEED_DECREASE, SDL_Rect SPEED_INCREASE) {
	//Draw dec
	SDL_Rect inc_hei = { SPEED_DECREASE.x, SPEED_DECREASE.y, SPEED_DECREASE.w, SPEED_DECREASE.h };
	SDL_SetRenderDrawColor(gRenderer, 160, 0, 0, 255);
	SDL_RenderFillRect(gRenderer, &inc_hei);
	SDL_Rect inc_heib = { SPEED_DECREASE.x, SPEED_DECREASE.y, SPEED_DECREASE.w, SPEED_DECREASE.h };
	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(gRenderer, &inc_heib);

	//Draw inc
	SDL_Rect inc_hei2 = { SPEED_INCREASE.x, SPEED_INCREASE.y, SPEED_INCREASE.w, SPEED_INCREASE.h };
	SDL_SetRenderDrawColor(gRenderer, 0, 144, 0, 255);
	SDL_RenderFillRect(gRenderer, &inc_hei2);
	SDL_Rect inc_heib2 = { SPEED_INCREASE.x, SPEED_INCREASE.y, SPEED_INCREASE.w, SPEED_INCREASE.h };
	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(gRenderer, &inc_heib2);
}


//Draw WIDTH_DECREASE
void changeBlockWidthHeight( int mx, int my, SDL_Rect WIDTH_DECREASE, SDL_Rect WIDTH_INCREASE, SDL_Rect HEIGHT_DECREASE, SDL_Rect HEIGHT_INCREASE) {
	if (mx > WIDTH_DECREASE.x && mx < WIDTH_DECREASE.x+WIDTH_DECREASE.w && my > WIDTH_DECREASE.y && my < WIDTH_DECREASE.y+WIDTH_DECREASE.h) {
		BLOCKW -= 8;
	}
	if (mx > WIDTH_INCREASE.x && mx < WIDTH_INCREASE.x+WIDTH_INCREASE.w && my > WIDTH_INCREASE.y && my < WIDTH_INCREASE.y+WIDTH_INCREASE.h) {
		BLOCKW += 8;
	}
	if (mx > HEIGHT_DECREASE.x && mx < HEIGHT_DECREASE.x+HEIGHT_DECREASE.w && my > HEIGHT_DECREASE.y && my < HEIGHT_DECREASE.y+HEIGHT_DECREASE.h) {
		BLOCKH-= 8;
	}
	if (mx > HEIGHT_INCREASE.x && mx < HEIGHT_INCREASE.x+HEIGHT_INCREASE.w && my > HEIGHT_INCREASE.y && my < HEIGHT_INCREASE.y+HEIGHT_INCREASE.h) {
		BLOCKH += 8;
	}
}
void changeBlockWidthHeightStartXY( int mx, int my, SDL_Rect WIDTH_DECREASE, SDL_Rect WIDTH_INCREASE, SDL_Rect HEIGHT_DECREASE, SDL_Rect HEIGHT_INCREASE) {
	if (mx > WIDTH_DECREASE.x && mx < WIDTH_DECREASE.x+WIDTH_DECREASE.w && my > WIDTH_DECREASE.y && my < WIDTH_DECREASE.y+WIDTH_DECREASE.h) {
		BLOCK.x -= 8;
	}
	if (mx > WIDTH_INCREASE.x && mx < WIDTH_INCREASE.x+WIDTH_INCREASE.w && my > WIDTH_INCREASE.y && my < WIDTH_INCREASE.y+WIDTH_INCREASE.h) {
		BLOCK.x += 8;
	}
	if (mx > HEIGHT_DECREASE.x && mx < HEIGHT_DECREASE.x+HEIGHT_DECREASE.w && my > HEIGHT_DECREASE.y && my < HEIGHT_DECREASE.y+HEIGHT_DECREASE.h) {
		BLOCK.y-= 8;
	}
	if (mx > HEIGHT_INCREASE.x && mx < HEIGHT_INCREASE.x+HEIGHT_INCREASE.w && my > HEIGHT_INCREASE.y && my < HEIGHT_INCREASE.y+HEIGHT_INCREASE.h) {
		BLOCK.y += 8;
	}
}
void changeBlockWidthHeightEndXY( int mx, int my, SDL_Rect WIDTH_DECREASE, SDL_Rect WIDTH_INCREASE, SDL_Rect HEIGHT_DECREASE, SDL_Rect HEIGHT_INCREASE) {
	if (mx > WIDTH_DECREASE.x && mx < WIDTH_DECREASE.x+WIDTH_DECREASE.w && my > WIDTH_DECREASE.y && my < WIDTH_DECREASE.y+WIDTH_DECREASE.h) {
		BLOCK.w -= 8;
	}
	if (mx > WIDTH_INCREASE.x && mx < WIDTH_INCREASE.x+WIDTH_INCREASE.w && my > WIDTH_INCREASE.y && my < WIDTH_INCREASE.y+WIDTH_INCREASE.h) {
		BLOCK.w += 8;
	}
	if (mx > HEIGHT_DECREASE.x && mx < HEIGHT_DECREASE.x+HEIGHT_DECREASE.w && my > HEIGHT_DECREASE.y && my < HEIGHT_DECREASE.y+HEIGHT_DECREASE.h) {
		BLOCK.h-= 8;
	}
	if (mx > HEIGHT_INCREASE.x && mx < HEIGHT_INCREASE.x+HEIGHT_INCREASE.w && my > HEIGHT_INCREASE.y && my < HEIGHT_INCREASE.y+HEIGHT_INCREASE.h) {
		BLOCK.h += 8;
	}
}

void changeBlockWidthHeightBoth( int mx, int my, SDL_Rect WIDTH_DECREASE, SDL_Rect WIDTH_INCREASE, SDL_Rect HEIGHT_DECREASE, SDL_Rect HEIGHT_INCREASE) {
	if (mx > WIDTH_DECREASE.x && mx < WIDTH_DECREASE.x+WIDTH_DECREASE.w && my > WIDTH_DECREASE.y && my < WIDTH_DECREASE.y+WIDTH_DECREASE.h) {
		BLOCK.w -= 8;
		BLOCKW -= 8;
	}
	if (mx > WIDTH_INCREASE.x && mx < WIDTH_INCREASE.x+WIDTH_INCREASE.w && my > WIDTH_INCREASE.y && my < WIDTH_INCREASE.y+WIDTH_INCREASE.h) {
		BLOCK.w += 8;
		BLOCKW += 8;
	}
	if (mx > HEIGHT_DECREASE.x && mx < HEIGHT_DECREASE.x+HEIGHT_DECREASE.w && my > HEIGHT_DECREASE.y && my < HEIGHT_DECREASE.y+HEIGHT_DECREASE.h) {
		BLOCK.h-= 8;
		BLOCKH-= 8;
	}
	if (mx > HEIGHT_INCREASE.x && mx < HEIGHT_INCREASE.x+HEIGHT_INCREASE.w && my > HEIGHT_INCREASE.y && my < HEIGHT_INCREASE.y+HEIGHT_INCREASE.h) {
		BLOCK.h += 8;
		BLOCKH += 8;
	}
}
void changePlayerSpeed( int mx, int my, SDL_Rect SPEED_DECREASE, SDL_Rect SPEED_INCREASE) {
	if (mx > SPEED_DECREASE.x && mx < SPEED_DECREASE.x+SPEED_DECREASE.w && my > SPEED_DECREASE.y && my < SPEED_DECREASE.y+SPEED_DECREASE.h) {
		//player.speedmax -= 2;
	}
	if (mx > SPEED_INCREASE.x && mx < SPEED_INCREASE.x+SPEED_INCREASE.w && my > SPEED_INCREASE.y && my < SPEED_INCREASE.y+SPEED_INCREASE.h) {
		//player.speedmax += 2;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////// ADD or MINUS PLACEMENT BASED ON WHAT BLOCK YOU ARE ON /////////////////////////////////////////
//-----------------------------------------------------------------------------------------------------------------------------//
void addWidth(Block block[], Blockc blockc[]) {
	//ADD THE WIDTH/HEIGHT OF THE BLOCK YOU ARE CURRENTLY OVER
	if (PLACING_TYPE == 1){
		for (int i = 0; i < 6000; i++) {
			if (block[i].alive) {
				if (block[i].MouseOnPlacement){
					BLOCKW += block[i].w;
				}
			}
		}
	}
	if (PLACING_TYPE == 3){
		for (int i = 0; i < 6000; i++) {
			if (blockc[i].alive) {
				if (blockc[i].MouseOnBlockc){
					BLOCKW += blockc[i].w;
				}
			}
		}
	}
}
void minusWidth(Block block[], Blockc blockc[]) {
	//ADD THE WIDTH/HEIGHT OF THE BLOCK YOU ARE CURRENTLY OVER
	if (PLACING_TYPE == 1){
		for (int i = 0; i < 6000; i++) {
			if (block[i].alive) {
				if (block[i].MouseOnPlacement){
					BLOCKW -= block[i].w;
				}
			}
		}
	}
	if (PLACING_TYPE == 3){
		for (int i = 0; i < 6000; i++) {
			if (blockc[i].alive) {
				if (blockc[i].MouseOnBlockc){
					BLOCKW -= blockc[i].w;
				}
			}
		}
	}
}
void addHeight(Block block[], Blockc blockc[]) {
	//ADD THE WIDTH/HEIGHT OF THE BLOCK YOU ARE CURRENTLY OVER
	if (PLACING_TYPE == 1){
		for (int i = 0; i < 6000; i++) {
			if (block[i].alive) {
				if (block[i].MouseOnPlacement){
					BLOCKH += block[i].h;
				}
			}
		}
	}
	if (PLACING_TYPE == 3){
		for (int i = 0; i < 6000; i++) {
			if (blockc[i].alive) {
				if (blockc[i].MouseOnBlockc){
					BLOCKH += blockc[i].h;
				}
			}
		}
	}
}
void minusHeight(Block block[], Blockc blockc[]) {
	//ADD THE WIDTH/HEIGHT OF THE BLOCK YOU ARE CURRENTLY OVER
	if (PLACING_TYPE == 1){
		for (int i = 0; i < 6000; i++) {
			if (block[i].alive) {
				if (block[i].MouseOnPlacement){
					BLOCKH -= block[i].h;
				}
			}
		}
	}
	if (PLACING_TYPE == 3){
		for (int i = 0; i < 6000; i++) {
			if (blockc[i].alive) {
				if (blockc[i].MouseOnBlockc){
					BLOCKH -= blockc[i].h;
				}
			}
		}
	}
}
//-----------------------------------------------------------------------------------------------------------------------------//
///////////////////////////////// ADD or MINUS PLACEMENT BASED ON WHAT BLOCK YOU ARE ON /////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




SDL_Color white = { 255, 255, 255, 255 };
void drawDebug(int camX, int camY,
		SDL_Rect WIDTH_DECREASE, SDL_Rect WIDTH_INCREASE, SDL_Rect HEIGHT_DECREASE, SDL_Rect HEIGHT_INCREASE,
		SDL_Rect sWIDTH_DECREASE, SDL_Rect sWIDTH_INCREASE, SDL_Rect sHEIGHT_DECREASE, SDL_Rect sHEIGHT_INCREASE,
		SDL_Rect eWIDTH_DECREASE, SDL_Rect eWIDTH_INCREASE, SDL_Rect eHEIGHT_DECREASE, SDL_Rect eHEIGHT_INCREASE,
		SDL_Rect bWIDTH_DECREASE, SDL_Rect bWIDTH_INCREASE, SDL_Rect bHEIGHT_DECREASE, SDL_Rect bHEIGHT_INCREASE){
	//placement box
	if (PLACING_TYPE == 0){			//Deleting
		SDL_Rect placeblockborder = { BLOCKX-camX, BLOCKY-camY, BLOCKW * HOWMANYBLOCKSW, BLOCKH* HOWMANYBLOCKSH };
		SDL_SetRenderDrawColor(gRenderer, 144, 0, 0, 255);
		SDL_RenderDrawRect(gRenderer, &placeblockborder);
	}
	if (PLACING_TYPE == 1){			//Placing Blocks
		SDL_Rect placeblockborder = { BLOCKX-camX, BLOCKY-camY, BLOCKW * HOWMANYBLOCKSW, BLOCKH* HOWMANYBLOCKSH };
		SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 255);
		SDL_RenderDrawRect(gRenderer, &placeblockborder);
	}
	if (PLACING_TYPE == 2){			//Placing Objects
		SDL_Rect placeblockborder2 = { BLOCKX-camX, BLOCKY-camY, BLOCKW * HOWMANYBLOCKSW, BLOCKH* HOWMANYBLOCKSH };
		SDL_SetRenderDrawColor(gRenderer, 102, 51, 0, 255);
		SDL_RenderDrawRect(gRenderer, &placeblockborder2);
	}
	//if (PLACING_TYPE == 3){			//Enable-Disable collision
	//	SDL_Rect placeblockborder2 = { BLOCKX-camX, BLOCKY-camY, BLOCKW * HOWMANYBLOCKSW, BLOCKH* HOWMANYBLOCKSH };
	//	SDL_SetRenderDrawColor(gRenderer, 0, 128, 255, 255);
	//	SDL_RenderDrawRect(gRenderer, &placeblockborder2);
	//}
	if (PLACING_TYPE == 4){			//Placing Monsters
		SDL_Rect monsterz = { BLOCKX-camX, BLOCKY-camY, BLOCKW * HOWMANYBLOCKSW, BLOCKH* HOWMANYBLOCKSH };
		SDL_SetRenderDrawColor(gRenderer, 244, 0, 0, 255);
		SDL_RenderDrawRect(gRenderer, &monsterz);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////// INDICATOR FOR INC/DEC BLOCKS /////////////////////////////////////
	//------------------------------------------------------------------------------------------------//
	drawIncreaseDecreaseBox(WIDTH_DECREASE, WIDTH_INCREASE, HEIGHT_DECREASE, HEIGHT_INCREASE);
	drawIncreaseDecreaseBox(sWIDTH_DECREASE, sWIDTH_INCREASE, sHEIGHT_DECREASE, sHEIGHT_INCREASE);
	drawIncreaseDecreaseBox(eWIDTH_DECREASE, eWIDTH_INCREASE, eHEIGHT_DECREASE, eHEIGHT_INCREASE);
	drawIncreaseDecreaseBox(bWIDTH_DECREASE, bWIDTH_INCREASE, bHEIGHT_DECREASE, bHEIGHT_INCREASE);
	//------------------------------------------------------------------------------------------------//
	///////////////////////////////// INDICATOR FOR INC/DEC BLOCKS /////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////x

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////// INCREASE WIDTH/HEIGHT OF BLOCK(W/H) //////////////////////////////////////////////////
	//----------------------------------------------------------------------------------------------------------------------------//
	//Width- (w)
	std::stringstream wdec;
	wdec << "W-";
	gText.loadFromRenderedText(wdec.str().c_str(),white, gFont12);
	gText.render(WIDTH_DECREASE.x+gText.getWidth()/2, WIDTH_DECREASE.y+gText.getHeight()/2-8,gText.getWidth(),gText.getHeight());
	//std::stringstream wdec2;
	//wdec2 << BLOCKW;
	//gText.loadFromRenderedText(wdec2.str().c_str(),white, gFont12);
	//gText.render(WIDTH_DECREASE.x-gText.getWidth(), WIDTH_DECREASE.y+gText.getHeight()/2,gText.getWidth(),gText.getHeight());

	//Width+ (w)
	std::stringstream winc;
	winc << "W+";
	gText.loadFromRenderedText(winc.str().c_str(),white, gFont12);
	gText.render(WIDTH_INCREASE.x+gText.getWidth()/2, WIDTH_INCREASE.y+gText.getHeight()/2-8,gText.getWidth(),gText.getHeight());
	std::stringstream wdec2;
	wdec2 << BLOCKW;
	gText.loadFromRenderedText(wdec2.str().c_str(),white, gFont12);
	gText.render(WIDTH_INCREASE.x-gText.getWidth(), WIDTH_INCREASE.y+gText.getHeight()/2-8,gText.getWidth(),gText.getHeight());

	//Height- (hw)
	std::stringstream hdec;
	hdec << "H-";
	gText.loadFromRenderedText(hdec.str().c_str(),white, gFont12);
	gText.render(HEIGHT_DECREASE.x+gText.getWidth()/2, HEIGHT_DECREASE.y+gText.getHeight()/2-8,gText.getWidth(),gText.getHeight());

	//Height+ (h)
	std::stringstream hinc;
	hinc << "H+";
	gText.loadFromRenderedText(hinc.str().c_str(),white, gFont12);
	gText.render(HEIGHT_INCREASE.x+gText.getWidth()/2, HEIGHT_INCREASE.y+gText.getHeight()/2-8,gText.getWidth(),gText.getHeight());
	std::stringstream hdec2;
	hdec2 << BLOCKH;
	gText.loadFromRenderedText(hdec2.str().c_str(),white, gFont12);
	gText.render(HEIGHT_INCREASE.x-gText.getWidth(), HEIGHT_INCREASE.y+gText.getHeight()/2-8,gText.getWidth(),gText.getHeight());
	//----------------------------------------------------------------------------------------------------------------------------//
	//startX- (sx)
	std::stringstream swdec;
	swdec << "SX-";
	gText.loadFromRenderedText(swdec.str().c_str(),white, gFont12);
	gText.render(sWIDTH_DECREASE.x+gText.getWidth()/2, sWIDTH_DECREASE.y+gText.getHeight()/2-8,gText.getWidth(),gText.getHeight());

	//startX+ (shy)
	std::stringstream swinc;
	swinc << "SX+";
	gText.loadFromRenderedText(swinc.str().c_str(),white, gFont12);
	gText.render(sWIDTH_INCREASE.x+gText.getWidth()/2, sWIDTH_INCREASE.y+gText.getHeight()/2-8,gText.getWidth(),gText.getHeight());
	std::stringstream swdec2;
	swdec2 << BLOCK.x;
	gText.loadFromRenderedText(swdec2.str().c_str(),white, gFont12);
	gText.render(sWIDTH_INCREASE.x-gText.getWidth(), sWIDTH_INCREASE.y+gText.getHeight()/2-8,gText.getWidth(),gText.getHeight());

	//startY- (sy)
	std::stringstream shdec;
	shdec << "SY-";
	gText.loadFromRenderedText(shdec.str().c_str(),white, gFont12);
	gText.render(sHEIGHT_DECREASE.x+gText.getWidth()/2, sHEIGHT_DECREASE.y+gText.getHeight()/2-8,gText.getWidth(),gText.getHeight());

	//startY+ (sy)
	std::stringstream shinc;
	shinc << "SY+";
	gText.loadFromRenderedText(shinc.str().c_str(),white, gFont12);
	gText.render(sHEIGHT_INCREASE.x+gText.getWidth()/2, sHEIGHT_INCREASE.y+gText.getHeight()/2-8,gText.getWidth(),gText.getHeight());
	std::stringstream shdec2;
	shdec2 << BLOCK.y;
	gText.loadFromRenderedText(shdec2.str().c_str(),white, gFont12);
	gText.render(sHEIGHT_INCREASE.x-gText.getWidth(), sHEIGHT_INCREASE.y+gText.getHeight()/2-8,gText.getWidth(),gText.getHeight());

	//----------------------------------------------------------------------------------------------------------------------------//
	//endw- (ew)
	std::stringstream ewdec;
	ewdec << "EW-";
	gText.loadFromRenderedText(ewdec.str().c_str(),white, gFont12);
	gText.render(eWIDTH_DECREASE.x+gText.getWidth()/2, eWIDTH_DECREASE.y+gText.getHeight()/2-8,gText.getWidth(),gText.getHeight());

	//endw+ (ew)
	std::stringstream ewinc;
	ewinc << "EW+";
	gText.loadFromRenderedText(ewinc.str().c_str(),white, gFont12);
	gText.render(eWIDTH_INCREASE.x+gText.getWidth()/2, eWIDTH_INCREASE.y+gText.getHeight()/2-8,gText.getWidth(),gText.getHeight());
	std::stringstream ewdec2;
	ewdec2 << BLOCK.w;
	gText.loadFromRenderedText(ewdec2.str().c_str(),white, gFont12);
	gText.render(eWIDTH_INCREASE.x-gText.getWidth(), eWIDTH_INCREASE.y+gText.getHeight()/2-8,gText.getWidth(),gText.getHeight());

	//endw- (ew)
	std::stringstream ehdec;
	ehdec << "EH-";
	gText.loadFromRenderedText(ehdec.str().c_str(),white, gFont12);
	gText.render(eHEIGHT_DECREASE.x+gText.getWidth()/2, eHEIGHT_DECREASE.y+gText.getHeight()/2-8,gText.getWidth(),gText.getHeight());

	//endh+ (eh)
	std::stringstream ehinc;
	ehinc << "EH+";
	gText.loadFromRenderedText(ehinc.str().c_str(),white, gFont12);
	gText.render(eHEIGHT_INCREASE.x+gText.getWidth()/2, eHEIGHT_INCREASE.y+gText.getHeight()/2-8,gText.getWidth(),gText.getHeight());
	std::stringstream ehdec2;
	ehdec2 << BLOCK.h;
	gText.loadFromRenderedText(ehdec2.str().c_str(),white, gFont12);
	gText.render(eHEIGHT_INCREASE.x-gText.getWidth(), eHEIGHT_INCREASE.y+gText.getHeight()/2-8,gText.getWidth(),gText.getHeight());
	//----------------------------------------------------------------------------------------------------------------------------//
	//Width- (w)
	std::stringstream bwdec;
	bwdec << "BW-";
	gText.loadFromRenderedText(bwdec.str().c_str(),white, gFont12);
	gText.render(bWIDTH_DECREASE.x+gText.getWidth()/2, bWIDTH_DECREASE.y+gText.getHeight()/2-8,gText.getWidth(),gText.getHeight());

	//Width+ (w)
	std::stringstream bwinc;
	bwinc << "BW+";
	gText.loadFromRenderedText(bwinc.str().c_str(),white, gFont12);
	gText.render(bWIDTH_INCREASE.x+gText.getWidth()/2, bWIDTH_INCREASE.y+gText.getHeight()/2-8,gText.getWidth(),gText.getHeight());

	//Height- hw)
	std::stringstream bhdec;
	bhdec << "BH-";
	gText.loadFromRenderedText(bhdec.str().c_str(),white, gFont12);
	gText.render(bHEIGHT_DECREASE.x+gText.getWidth()/2, bHEIGHT_DECREASE.y+gText.getHeight()/2-8,gText.getWidth(),gText.getHeight());

	//Height+ (h)
	std::stringstream bhinc;
	bhinc << "BH+";
	gText.loadFromRenderedText(bhinc.str().c_str(),white, gFont12);
	gText.render(bHEIGHT_INCREASE.x+gText.getWidth()/2, bHEIGHT_INCREASE.y+gText.getHeight()/2-8,gText.getWidth(),gText.getHeight());
	//----------------------------------------------------------------------------------------------------------------------------//
	///////////////////////////////////////// INCREASE WIDTH/HEIGHT OF BLOCK(W/H) //////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
