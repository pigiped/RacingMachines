#pragma once
#include "GameObject.h"
#include "SDL.h"
#include "SDL_image.h"

class Player : public GameObject
{
public:
	Player();
	~Player();

	void setTexture(SDL_Texture* tex);

	float getSpeed();
	void setSpeed(float s);

	float getAngle();
	void setAngle(float a);

	virtual void draw(SDL_Renderer* rend);
	virtual void update();

private:
	SDL_Texture* texture = nullptr;
	float speed = 0;
	float angle = 0;
};

