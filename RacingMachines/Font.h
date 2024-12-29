#pragma once
#include "GameObject.h"
#include "SDL_ttf.h"
#include <string>

class Font : public GameObject
{
public:
	Font(const char[]);
	~Font();

	virtual void draw(SDL_Renderer* rend);
	virtual void update();

	void setText(const char text[], SDL_Color color, SDL_Renderer* renderer);
private:
	SDL_Texture* texture = nullptr;
	TTF_Font* font = nullptr;
};

