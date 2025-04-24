#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <queue>
using namespace std;
int a[] = { 0,1,0,-1 };
int b[] = { -1,0,1,0 };
int width = 360, hight = 175,cellsize = 5;
set<pair<int, int>>s;
class mrav {
private:
	int pozx,pozy;
	int kret;
	sf::RectangleShape cl;
public:
	mrav(int Pozx, int Pozy, int Kret)
	{
		pozx = Pozx;pozy = Pozy;kret = Kret;
		cl.setSize(sf::Vector2f(5, 5));
	}
	void krete()
	{
		if (s.find({pozx,pozy}) == s.end())
		{
			s.insert({ pozx,pozy });
			kret++;
		}
		else {
			s.erase({ pozx,pozy });
			kret--;
		}
		if (kret < 0) kret = 3;
		if (kret > 3) kret = 0;
		pozx += a[kret];
		pozy += b[kret];
		if (pozx >= width || pozx < 0 || pozy >= hight || pozy < 0)
		{
			kret += 2;
			if (pozx >= width) pozx = width - 1;
			if (pozy >= hight) pozy = hight - 1;
			if (pozx < 0) pozx = 0;
			if (pozy < 0) pozy = 0;
		}
	}
};

int main()
{
	sf::RenderWindow window(sf::VideoMode(width*5, hight*5), "NESTO", sf::Style::Default);
	sf::Event ev;
	vector<mrav> mravi;
	sf::RectangleShape cd(sf::Vector2f(5, 5));cd.setFillColor(sf::Color::Black);
	int numOfAnts = 2000;
	for (int i = 0;i < numOfAnts;i++)
	{
		mravi.push_back({ rand() % width,rand() % hight,rand() % 4 });
	}
	while (window.isOpen())
	{
		while (window.pollEvent(ev))
		{
			if (ev.type == sf::Event::Closed)
				window.close();
			else if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
				window.close();
		}
		for (int i = 0;i < numOfAnts;i++)
		{
			mravi[i].krete();
		}
		window.clear(sf::Color::White);
		for (auto i : s)
		{
			cd.setPosition(i.first*5, i.second*5);
			window.draw(cd);
		}
		window.display();
	}
}