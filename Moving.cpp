#include <SFML/Graphics.hpp>

using namespace sf;

double MovingCamdx(double ang)
{
	double dx = 0;
	double d_sin = sin(ang);
	double d_cos = cos(ang);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		dx += d_sin;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		dx -= d_sin;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		dx += d_cos*3;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		dx -= d_cos*3;
	}
	return dx;

}

double MovingCamdy(double ang)
{
	double dy = 0;
	double d_sin = sin(ang);
	double d_cos = cos(ang);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		dy -= d_cos;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		dy += d_cos;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		dy += d_sin*3;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		dy -= d_sin*3;
	}
	return dy;

}

double MovingCamAng(double ang)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		ang -= 0.025;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		ang += 0.025;
	}

	return ang;
}
