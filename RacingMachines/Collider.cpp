#include "Collider.h"
#include "stdio.h"

Collider::Collider(float x, float y, float w, float h)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

Collider::~Collider()
{
}

void Collider::draw(SDL_Renderer* rend)
{
	//draw a magenta rectangle
	/*
	SDL_SetRenderDrawColor(rend, 255, 0, 255, 255);
	SDL_Rect rect = { (int)x,(int)y,(int)w,(int)h };
	SDL_RenderFillRect(rend, &rect);
	*/
}

void Collider::update()
{
}

bool Collider::isColliding(GameObject* other)
{
	{
		if (x < other->getX() + other->getW() &&
			x + w > other->getX() &&
			y < other->getY() + other->getH() &&
			y + h > other->getY())
		{
			printf("Collision detected!\n");
			return true;
		}
		return false;
	}
}