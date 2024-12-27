#include "Player.h"
#include "GameObject.h"
#include "constants.h"
#include <math.h>

Player::Player()
{
}

Player::~Player()
{
}

void Player::setTexture(SDL_Texture* tex)
{
	texture = tex;
}

float Player::getSpeed()
{
	return speed;
}

void Player::setSpeed(float s)
{
	speed = s;
}

float Player::getAngle()
{
	return angle;
}

void Player::setAngle(float a)
{
	angle = a;
}

void Player::draw(SDL_Renderer* rend)
{
	SDL_Rect rect = { (int)x,(int)y,(int)w,(int)h};
	SDL_RenderCopyEx(rend, texture, nullptr, &rect, angle, NULL, SDL_FLIP_NONE);
}

void Player::update()
{
	speed *= FRICTION;

	float radians = angle * M_PI / 180.0f;

	x += cos(radians) * speed;
	y += sin(radians) * speed;

	// Impedisci alla macchina di uscire dallo schermo
	if (x < 0) x = 0;
	if (x > SCREEN_WIDTH) x = SCREEN_WIDTH;
	if (y < 0) y = 0;
	if (y > SCREEN_HEIGHT) y = SCREEN_HEIGHT;
}
