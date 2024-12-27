#include <stdio.h>
#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"
#include "constants.h"
#include "Track.h"
#include "Collider.h"

using namespace std;

static TextureManager* textureManager = nullptr;
static SDL_Texture* playerTexture = nullptr;
static SDL_Texture* trackTexture = nullptr;
list<GameObject*> gameObjects;

int processEvents(SDL_Window* window)
{
	SDL_Event event;
	int done = 0;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_WINDOWEVENT_CLOSE:
		{
			if (window)
			{
				SDL_DestroyWindow(window);
				window = NULL;
				done = 1;
			}
		}
		break;
		case SDL_KEYDOWN:
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				done = 1;
				break;
			}
		}
		break;
		case SDL_QUIT:
			done = 1;
			break;
		}
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);
	Player* player = nullptr;

	for (auto gameObject : gameObjects)
	{
		if (dynamic_cast<Player*>(gameObject))
		{
			player = dynamic_cast<Player*>(gameObject);
			break;
		}
	}
	if (player) 
	{
		if (state[SDL_SCANCODE_LEFT])
		{
			player->setAngle(player->getAngle() - TURN_SPEED * (player->getSpeed() != 0 ? player->getSpeed() / MAX_SPEED : 1));
		}
		if (state[SDL_SCANCODE_RIGHT])
		{
			player->setAngle(player->getAngle() + TURN_SPEED * (player->getSpeed() != 0 ? player->getSpeed() / MAX_SPEED : 1));
		}
		if (state[SDL_SCANCODE_UP])
		{
			player->setSpeed(player->getSpeed() + ACCELERATION);
			if (player->getSpeed() > MAX_SPEED)
			{
				player->setSpeed(MAX_SPEED);
			}
		}
		if (state[SDL_SCANCODE_DOWN])
		{
			player->setSpeed(player->getSpeed() - ACCELERATION);
			if (player->getSpeed() < -MAX_SPEED)
			{
				player->setSpeed(-MAX_SPEED);
			}
		}
	}
	
	return done;
}

void doRender(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 240, 240, 255, 255);

	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	for (auto gameObject : gameObjects)
	{
		gameObject->draw(renderer);
	}

	SDL_RenderPresent(renderer);
}

int doUpdates()
{
	for (auto gameObject : gameObjects)
	{
		gameObject->update();
	}
	return 0;
}

void InitColliders()
{
	Collider* collider = new Collider(896,16,16,384);
	gameObjects.push_back(collider);
	Collider* collider2 = new Collider(1072, 192, 16, 368);
	gameObjects.push_back(collider2);
	Collider* collider3 = new Collider(256, 128, 16, 432);
	gameObjects.push_back(collider3);
	Collider* collider4 = new Collider(448, 224, 16, 176);
	gameObjects.push_back(collider4);
	Collider* collider5 = new Collider(272, 128, 305, 16);
	gameObjects.push_back(collider5);
	Collider* collider6 = new Collider(464, 224, 432, 16);
	gameObjects.push_back(collider6);
	Collider* collider7 = new Collider(464, 384, 432, 16);
	gameObjects.push_back(collider7);
	Collider* collider8 = new Collider(272, 544, 800, 16);
	gameObjects.push_back(collider8);
	Collider* collider9 = new Collider(0, 0, SCREEN_WIDTH, 16);
	gameObjects.push_back(collider9);
	Collider* collider10 = new Collider(SCREEN_WIDTH-16, 0, 16, SCREEN_HEIGHT);
	gameObjects.push_back(collider10);
	Collider* collider11 = new Collider(0, 16, 16, SCREEN_HEIGHT-16);
	gameObjects.push_back(collider11);
	Collider* collider12 = new Collider(16, SCREEN_HEIGHT - 16, SCREEN_WIDTH - 16, 16);
	gameObjects.push_back(collider12);
}

SDL_Texture* loadFont(SDL_Renderer* renderer, const std::string& name)
{
	TTF_Font* font = TTF_OpenFont(name.c_str(), 24);
	if (font == NULL)
	{
		printf("TTF_OpenFont: %s\n", TTF_GetError());
	}
	SDL_Color color = { 255, 255, 255 };
	SDL_Surface* surface = TTF_RenderText_Solid(font, "Hello World", color);
	if (surface == NULL)
	{
		printf("TTF_RenderText_Solid: %s\n", TTF_GetError());
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == NULL)
	{
		printf("SDL_CreateTextureFromSurface: %s\n", SDL_GetError());
	}

	SDL_FreeSurface(surface);
	TTF_CloseFont(font);

	return texture;
}

int main(int argc, char* argv[])
{
	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	window = SDL_CreateWindow(
		"Game Window",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		1280,
		720,
		0
	);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	textureManager = new TextureManager();
	TextureManager::setRenderer(renderer);

	trackTexture = textureManager->getTexture("track.png");
	playerTexture = textureManager->getTexture("ferreri.png");

	Track* track = new Track();
	track->setTexture(trackTexture);
	track->setPos(0, 0);
	track->setDim(SCREEN_WIDTH, SCREEN_HEIGHT);

	Player* player = new Player();
	player->setTexture(playerTexture);
	player->setPos(640, 630);
	player->setDim(32*2, 13*2);

	gameObjects.push_back(track);
	gameObjects.push_back(player);

	InitColliders();

	SDL_Texture* fontTexture = loadFont(renderer, "crazy-pixel.ttf");
	if (fontTexture == nullptr)
	{
		printf("Failed to load font texture.\n");
		return -1;
	}

	int done = 0;

	while (!done)
	{
		done = processEvents(window);
		doUpdates();
		for (auto gameObject : gameObjects)
		{
			if (auto collider = dynamic_cast<Collider*>(gameObject))
			{
				if (collider->isColliding(player))
				{
					player->setSpeed(-player->getSpeed());
				}
			}
		}
		/*
		SDL_Rect rect = { 100,100,100,100 };
		SDL_RenderCopy(renderer, fontTexture, nullptr, &rect);
		*/
		doRender(renderer);

	}

	for (auto& go : gameObjects)
	{
		delete go;
	}
	gameObjects.clear();


	SDL_DestroyTexture(playerTexture);
	SDL_DestroyTexture(trackTexture);

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	delete textureManager;

	SDL_Quit();
	TTF_Quit();
	return 0;
}