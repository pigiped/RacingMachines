#pragma once
#include "GameObject.h"
class Track : public GameObject
{
public:
	Track();
	~Track();

	void setTexture(SDL_Texture* tex);

	virtual void draw(SDL_Renderer* rend);
	virtual void update();

private:
	SDL_Texture* texture = nullptr;
};

