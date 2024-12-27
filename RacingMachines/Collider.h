#pragma once
#include "GameObject.h"

class Collider : public GameObject
{
public:
	Collider(float x, float y, float w, float h);
	~Collider();
	virtual void draw(SDL_Renderer* rend);
	virtual void update();

	bool isColliding(GameObject* other);
};

