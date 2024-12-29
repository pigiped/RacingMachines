#include <stdio.h>
#include "Font.h"
#include <string>

Font::Font(const char fontName[])
{
	font = TTF_OpenFont(fontName, 24);
	if (font == NULL)
	{
		printf("TTF_OpenFont: %s\n", TTF_GetError());
	}
}

Font::~Font()
{
	SDL_DestroyTexture(texture);
	TTF_CloseFont(font);
	printf("Font closed and texture erased\n");
}

void Font::draw(SDL_Renderer* rend)
{
	SDL_Rect rect = { (int)x,(int)y,(int)w,(int)h };
	SDL_RenderCopy(rend, texture, nullptr, &rect);
}

void Font::update()
{
}

void Font::setText(const char text[], SDL_Color color, SDL_Renderer* renderer)
{
	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
	}
	SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
	if (surface == NULL)
	{
		printf("TTF_RenderText_Solid: %s\n", TTF_GetError());
	}
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == NULL)
	{
		printf("SDL_CreateTextureFromSurface: %s\n", SDL_GetError());
	}
	SDL_FreeSurface(surface);
}
