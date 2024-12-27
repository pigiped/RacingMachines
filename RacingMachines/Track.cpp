#include "Track.h"
#include "GameObject.h"
#include "constants.h"

Track::Track()
{
}

Track::~Track()
{
}

void Track::setTexture(SDL_Texture* tex)
{
	texture = tex;
}

void Track::draw(SDL_Renderer* rend)
{
	SDL_Rect rect = { (int)x,(int)y,(int)w,(int)h};
	SDL_RenderCopy(rend, texture, nullptr, &rect);
}

void Track::update()
{
}
