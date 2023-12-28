#pragma once

#include <SFML/Graphics.hpp>
#include "CubeClass.h"
class Window {

	sf::RenderWindow* window = nullptr;
	float posz = 0;

	sf::Vector2i mouseStart;
	sf::Vector2i mouseEnd;
	sf::Mouse mouse;
	sf::VertexArray Cube3D;
	Cube* cube;


	float calcdis(sf::Vector2i p1, sf::Vector2i p2)
	{
		float xcb = (p2.x - p1.x) * (p2.x - p1.x);
		float ycb = (p2.y - p1.y) * (p2.y - p1.y);
		return sqrt(xcb + ycb);
	}

	void updateDraw() {

		for (int i = 0; i < cube->show.size(); i++) {
			std::vector<int> faceid = cube->show[i];
			sf::Vertex* face = &Cube3D[i * 4];
			for (int j = 0; j < 4; j++)
			{

				face[j].position = sf::Vector2f(cube->C3D[faceid[j]].x, cube->C3D[faceid[j]].y);
				if (i == 0)face[j].color = sf::Color(255, 0, 0);
				if (i == 1)face[j].color = sf::Color(0, 255, 0);
				if (i == 2)face[j].color = sf::Color(0, 0, 255);


			}


		}

}

	void update()
	{
		updateDraw();



		window->clear();
		window->draw(Cube3D);
		window->display();
	}

	void close(){

		delete window;
	}

	bool ok = 0;
	void loop()
	{
		sf::Event event;
		while (window->isOpen())
		{
			while (window->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window->close();

				}

				if (event.type == sf::Event::MouseButtonPressed)
				{
					mouseStart = mouse.getPosition(*window);

				ok = 1;
				}
				if (event.type == sf::Event::MouseButtonReleased)
				{

					mouseEnd = mouse.getPosition(*window);
					float dx = mouseEnd.x - mouseStart.x;
					float dy = mouseEnd.y - mouseStart.y;
					float disP1 = cube->distanceTo(mouseStart.x, mouseStart.y, posz);

					float alfaX = atan2f(dx, disP1);
					float alfaY = atan2f(dy, disP1);

					cube->rotate(alfaY, alfaX, 0);
					cube->draw(window->getSize().x / 2, window->getSize().y / 2, posz);
					Cube3D.resize(cube->show.size() * 4);


					ok = 0;

				}
				if (ok == 1)
				{
					mouseEnd = mouse.getPosition(*window);
					float dx = mouseEnd.x - mouseStart.x;
					float dy = mouseEnd.y - mouseStart.y;
					float disP1 = cube->distanceTo(mouseStart.x, mouseStart.y,posz);

					float alfaX = atan2f(dx, disP1);
					float alfaY = atan2f(dy, disP1);

					cube->rotate(-alfaY, alfaX, 0);
					cube->draw(window->getSize().x / 2, window->getSize().y / 2, posz);
					Cube3D.resize(cube->show.size() * 4);
					mouseStart = mouseEnd;

				}

			}
			update();


		}
		close();


	}


public :


	void start(unsigned int Width, unsigned int Height, const char* Title)
	{

		window = new sf::RenderWindow(sf::VideoMode(Width, Height), Title);
		cube = new Cube(100);
		Cube3D.setPrimitiveType(sf::Quads);
		cube->move(Width / 2, Height / 2, -100);
		cube->draw(Width / 2, Height / 2, posz);

		Cube3D.resize(cube->show.size() * 4);


		loop();

	}

};
