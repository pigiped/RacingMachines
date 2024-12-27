#include "GameObject.h"

GameObject::GameObject()
{
}

void GameObject::setPos(float x, float y)
{
	this->x = x;
	this->y = y;
}

float GameObject::getX()
{
	return x;
}

float GameObject::getY()
{
	return y;
}

void GameObject::setW(float w)
{
	this->w = w;
}

void GameObject::setH(float h)
{
	this->h = h;
}

void GameObject::setDim(float w, float h)
{
	this->w = w;
	this->h = h;
}

float GameObject::getW()
{
	return w;
}

float GameObject::getH()
{
	return h;
}
