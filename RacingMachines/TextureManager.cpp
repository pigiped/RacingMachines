#include "TextureManager.h"
#include "SDL_image.h"

SDL_Renderer* TextureManager::renderer = NULL;

TextureManager::~TextureManager()
{
	for (auto& t : textures)
	{
		SDL_DestroyTexture(t.second);
	}
	textures.clear();
}

void TextureManager::setRenderer(SDL_Renderer* r)
{
	renderer = r;
}

void TextureManager::setTexture(const std::string& name, SDL_Texture* tex)
{
	textures[name] = tex;
}

SDL_Texture* TextureManager::getTexture(const std::string& name)
{
	auto it = textures.find(name);
	if (it == textures.end())
	{
		SDL_Texture* tex = NULL;
		auto surface = IMG_Load(name.c_str());
		if (surface)
		{
			tex = SDL_CreateTextureFromSurface(renderer, surface);
			setTexture(name, tex);
		}
		else
		{
			printf("IMG_Load: %s\n", IMG_GetError());
			return NULL;
		}
		SDL_FreeSurface(surface);

		return tex;
	}

	return it->second;
}

void TextureManager::dropTexture(const std::string& name)
{
	auto it = textures.find(name);
	if (it != textures.end())
	{
		SDL_DestroyTexture(it->second);
		textures.erase(it);
	}
}
