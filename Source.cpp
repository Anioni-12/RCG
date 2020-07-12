#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include <vector>

#include "Moving.h"
#include "Intersect.h"



// кол-во отрезков
int sh=0;

//координаты точек отрезков

int sh11[2555] = {};
int sh12[2555] = {};
int sh21[2555] = {};
int sh22[2555] = {};

//рёбра
int r = 0;

//координаты точек рёбер
int rx[2555] = {};
int ry[2555] = {};


using namespace sf;


// функция добавления отрезков прямоугольника
int AddRect(int x, int y, int x1, int y1)
{
	r += 4;
	rx[r - 3] = x; ry[r - 3] = y;
	rx[r - 2] = x1; ry[r - 2] = y;
	rx[r - 1] = x; ry[r - 1] = y1;
	rx[r] = x1; ry[r] = y1;

	sh += 4;
	sh11[sh - 3] = x; sh12[sh - 3] = y;	sh21[sh - 3] = x1; sh22[sh - 3] = y;
	sh11[sh - 2] = x; sh12[sh - 2] = y;	sh21[sh - 2] = x; sh22[sh - 2] = y1;
	sh11[sh - 1] = x1; sh12[sh - 1] = y; sh21[sh - 1] = x1; sh22[sh - 1] = y1;
	sh11[sh] = x; sh12[sh] = y1; sh21[sh] = x1;sh22[sh] = y1;
	return 0;
}

// функция добавления отрезков треугольника
int AddTrian(int x, int y, int x1, int y1, int x2, int y2)
{
	r += 3;
	rx[r - 2] = x; ry[r - 2] = y;
	rx[r - 1] = x1; ry[r - 1] = y1;
	rx[r] = x2; ry[r] = y2;

	sh += 3;
	sh11[sh - 2] = x; sh12[sh - 2] = y;	sh21[sh - 2] = x1; sh22[sh - 2] = y1;
	sh11[sh - 1] = x1; sh12[sh - 1] = y1;	sh21[sh - 1] = x2; sh22[sh - 1] = y2;
	sh11[sh] = x2; sh12[sh] = y2; sh21[sh] = x; sh22[sh] = y;
	return 0;
}


int main()

{

	std::vector<Sprite> text(600);

	sf::Texture wall;

	if (!wall.loadFromFile("wall.png"))
	{
		std::cout << "Resourse error: texture was not found.\nError x0001f";
		return 0;
	}

	double x = 20, y = 20, ang = 90;
	int radius = 200, quanlin=0;
	const double hor = 300;
	double corang = 90;

	sf::VertexArray lin(sf::Lines, 1200);
	sf::VertexArray view(sf::LineStrip, 601);

	RenderWindow window(VideoMode(600, 600), "RCG");

	RectangleShape rect1(Vector2f(5.f, 150.f));
	rect1.setPosition(0.f, 0.f);
	AddRect(0, 0, 5, 150);
	rect1.setFillColor(Color::Magenta);

	RectangleShape rect2(Vector2f(140.f, 5.f));
	rect2.setPosition(5.f, 0.f);
	AddRect(5, 0, 145, 5);
	rect2.setFillColor(Color::Magenta);

	RectangleShape rect3(Vector2f(5.f, 150.f));
	rect3.setPosition(145.f, 0.f);
	AddRect(145, 0, 150, 150);
	rect3.setFillColor(Color::Magenta);

	RectangleShape rect4(Vector2f(140.f, 5.f));
	rect4.setPosition(5.f, 145.f);
	AddRect(5, 145, 145, 150);
	rect4.setFillColor(Color::Magenta);

	RectangleShape rect5(Vector2f(20.f, 20.f));
	rect5.setPosition(45.f, 45.f);
	AddRect(45, 45, 65, 65);
	rect5.setFillColor(Color::Magenta);
	rect5.setOutlineThickness(3.f);
	rect5.setOutlineColor(sf::Color(250, 150, 100));

	CircleShape pl(5.f);
	pl.setFillColor(sf::Color(100, 250, 50));
	pl.setPosition(x, y);

	ConvexShape tr1;
	tr1.setPointCount(3);
	tr1.setPoint(0, sf::Vector2f(80.f, 100.f));
	tr1.setPoint(1, sf::Vector2f(110.f, 100.f));
	tr1.setPoint(2, sf::Vector2f(105.f, 80.f));
	AddTrian(80, 100, 110, 100, 105, 80);
	tr1.setFillColor(Color::Magenta);
	tr1.setOutlineThickness(3.f);
	tr1.setOutlineColor(sf::Color(250, 150, 100));

	double yc, xc;

	int fi, e=-1, dl=-1;

	while (window.isOpen())

	{
		sf::Vector2f position = pl.getPosition();
		double dx = 0;
		double dy = 0;
		double d_sin = sin(ang);
		double d_cos = cos(ang);

		Event event;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		dx = MovingCamdx(ang);
		dy = MovingCamdy(ang);
		pl.move(dx/10, dy/10);
		ang = MovingCamAng(ang);

		double vx=(sin(-ang+corang) * radius + position.x), vy= (cos(-ang+ corang) * radius + position.y);
		view[0].position = sf::Vector2f(position.x+5, position.y+5);
		double an = ang;
		double px = 0, py = 0;
		quanlin = 0;
		fi = 1;

		for (int i = 1; i < 600; i++)
		{
			double minl = 999999;
			bool wrlin = false;
			
			for (int l = 0; l <= sh; l++)
			{
				pt lef, r;
				pt a, b, c, d;
				a.x = position.x + 5;
				a.y = position.y + 5;
				b.x = vx;
				b.y = vy;
				c.x = sh11[l];
				c.y = sh12[l];
				d.x = sh21[l];
				d.y = sh22[l];
				if (intersect(a, b, c, d, lef, r))
				{
					yc = (lef.y + r.y) / 2;
					xc = (lef.x + r.x) / 2;
					if (minl >= (double)(sqrt((xc - position.x)*(xc - position.x) + (yc - position.y)*(yc - position.y))))
					{
						minl = (double)(sqrt((xc - position.x)*(xc - position.x) + (yc - position.y)*(yc - position.y)));
						vx = lef.x; vy = lef.y;
						wrlin = true;
					}
				}

			}

			if (wrlin)
			{
				double length = (50 / (minl + 50)) * 500;
				double color = 255-((minl/200) * 255);

				lin[quanlin].position = sf::Vector2f(i, hor - (length / 2));
				lin[quanlin + 1].position = sf::Vector2f(i, hor + (length / 2));

				lin[quanlin].color = sf::Color(color, color, color);
				lin[quanlin+1].color = sf::Color(color, color, color);

				quanlin += 2;
			}

			else
			{
				lin[quanlin].position = sf::Vector2f(0, 0);
				lin[quanlin + 1].position = sf::Vector2f(0, 0);
				quanlin += 2;
			}

			view[i].position = sf::Vector2f(vx, vy);
			an = an + 0.002;
			vx = (sin(-an + corang) * radius + position.x); vy = (cos(-an + corang) * radius + position.y);
		}

		view[600].position = sf::Vector2f(position.x + 5, position.y + 5);

		window.clear();
		window.draw(lin);
		window.draw(rect1);
		window.draw(rect2);
		window.draw(rect3);
		window.draw(rect4);
		window.draw(rect5);
		window.draw(tr1);
		window.draw(pl);
		window.draw(view);
		window.display();
	}

	return 0;

}