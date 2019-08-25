#pragma once
#include"SFML/Graphics.hpp"
#include<vector>
#include<string>
#include<ctime>



using namespace std;

 const extern int Height ;
	const extern int Width ;
	extern vector<char> ItemsInWindow;
	 extern vector<char> Items;
	 extern string Map_Text ;



extern sf::String TileMap[];



void SpawnItems(int timer);