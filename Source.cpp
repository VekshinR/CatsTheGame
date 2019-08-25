#include<iostream>
#include<vector>
#include<SFML/Graphics.hpp>
#include"map.h"
#include"View.h"
#include"ctime"
#include<thread>
#include<fstream>
#include<numeric>
#include<SFML/Audio.hpp>
#include<mutex>
#include"Player.h"
#include"Bot.h"
using namespace std;
using namespace sf;
bool checkCoordinateForWindow(int i, int j) {
	if ((TileMap[i][j] == 'w') || (TileMap[i][j] == 'G') || (TileMap[i][j] == 'T')
		|| (TileMap[i][j] == 'P') || (TileMap[i][j] == 'K') || (TileMap[i][j] == 'R') || (TileMap[i][j] == 'C') || (TileMap[i][j] == 'A') || (TileMap[i][j] == 'I') || (TileMap[i][j] == 'L')
		|| (TileMap[i][j] == 'J')) {
		return 1;
	}
	else { return 0; }
}
int main() {
	fstream s;
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(980, 720), "SuicideCats",Style::Fullscreen);
	sf::Event event;
	Clock clock1;
	bool Menu = 1;
	Font font;//шрифт 
	font.loadFromFile("CyrilicOld.ttf");//передаем нашему шрифту файл шрифта
	Text text("", font, 30);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пикселях);//сам объект текст (не строка)
	text.setFillColor(Color::Red);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);//
	Texture map_texture;
	Sprite s_map;
	Texture map_background;
	map_background.loadFromFile("images/sky.png");
	Sprite b_map;
	b_map.setTexture(map_background);
	View view;
	view.setCenter(810, 790);
	view.setSize(1620, 1590);
	Image map_image;
	map_image.loadFromFile(Map_Text);
	map_image.createMaskFromColor(Color::White);
	map_texture.loadFromImage(map_image);
	s_map.setTexture(map_texture);
	Clock clock12;
	Clock Clockfor2pl;
	Clock clock123;
	Clock clock1232;
	Clock clockfor1pl;
	Clock Clockforbot1;
	Clock Clockforbot1_1;
	int SpawnTimer = 0;
	Player FC(0, 0);
	Player FC1(1, 1);
	Bot Bot1;
	bool Clocker=1;
	vector <string> MainMusic = { "sounds/main_classic.ogg","sounds/main_nirvana.ogg",
		"sounds/main_naruto.ogg","sounds/main_sound_of_silence.ogg" };
	Music music;//создаем объект музыки
	int song = rand() % MainMusic.size();
	music.openFromFile(MainMusic[song]);//загружаем файл
	if (song == 1) { music.setVolume(50); }
	else { music.setVolume(80); }
	music.play();
	float	time;
	float time1pl;
	float time1bot;
	deque<float>AverageTimeDQ(10,0);
	float AverageTime;
	float AverageTimeInDQ=10;
	while (window.isOpen()) {
		if (Menu == 0) {
			time = clock1.getElapsedTime().asMicroseconds();
			time1pl = clockfor1pl.getElapsedTime().asMicroseconds();
			time1bot = Clockforbot1.getElapsedTime().asMicroseconds();
			clock1.restart();
			clockfor1pl.restart();
			Clockforbot1.restart();
			AverageTime = (time + time1pl + time1bot) / 3;
			if (AverageTimeDQ.size() == 10) {
				AverageTimeDQ.pop_back();
			}
			AverageTimeDQ.push_front(AverageTime);
			time = AverageTimeInDQ;
			time1pl = AverageTimeInDQ;
			time1bot = AverageTimeInDQ;
			SpawnTimer = clock12.getElapsedTime().asSeconds();
			if (clock12.getElapsedTime().asSeconds() < 2&&Clocker) {
				Player::Pause(1);
			}
			if(clock12.getElapsedTime().asSeconds()>=2&&Clocker==1){
				Player::Pause(0);
				Clocker = 0;
				cout << "JJJJJJJIIIIIIIIIIIMMYYY" << endl;
			}
			//clock12.restart();
			time1pl = time1pl / 1000;
			time = time / 1000;
			time1bot = time1bot / 1000;
		}
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		thread t2([&]() {SpawnItems(SpawnTimer); });
		b_map.setPosition(0, 0);
		b_map.setTextureRect(IntRect(0, 0, 1024, 1007));
		window.draw(b_map);
		b_map.setPosition(1024, 0);
		b_map.setTextureRect(IntRect(1024, 0, -635, 1007));
		window.draw(b_map);
		b_map.setPosition(0, 1007);
		b_map.setTextureRect(IntRect(0, 1024, 596, -583));
		window.draw(b_map);
		b_map.setPosition(1024, 1007);
		b_map.setTextureRect(IntRect(1024, 1024, -635, -583));
		window.draw(b_map);
		t2.join();
		if (Menu==0) {
			for (int i = 0; i < Height; i++)
				for (int j = 0; j < Width; j++)
				{
					if (TileMap[i][j] == 's') { s_map.setTextureRect(IntRect(132, 0, 36, 53)); }//stone
					if ((TileMap[i][j] == '0')) { s_map.setTextureRect(IntRect(42, 0, 36, 53)); }//green
					if (checkCoordinateForWindow(i, j)) { s_map.setTextureRect(IntRect(0, 0, 36, 53)); }//window
					s_map.setPosition(j * 36, i * 53);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат
					if ((TileMap[i][j] != ' ') && (TileMap[i][j] != 't') && (TileMap[i][j] != 'g') && (TileMap[i][j] != 'p')
						&& (TileMap[i][j] != 'h') && (TileMap[i][j] != 'k') && (TileMap[i][j] != 'r') && (TileMap[i][j] != 'i') && (TileMap[i][j] != 'l') && (TileMap[i][j] != 'j')) {
						window.draw(s_map);
					}
				}
			int FindTimerBot = clock12.getElapsedTime().asSeconds();
			if (FindTimerBot % 7==0) {
				Bot::NeedToFind = 1;
			}
			thread tb1([&]() {Bot1.GameProcess(time1bot, Clockforbot1_1); });
			thread t1([&]() {FC.GameProcess(time1pl, clock123); });
			thread t4([&]() {FC1.GameProcess(time, clock1232); });
			for (int i = 0; i < Height; i++)
				for (int j = 0; j < Width; j++)
				{
					if ((TileMap[i][j] == 'p')) { s_map.setTextureRect(IntRect(87, 106, 50, 100)); }//poison
					if ((TileMap[i][j] == 'P')) { s_map.setTextureRect(IntRect(87, 106, 50, 100)); }//poisom in window
					if ((TileMap[i][j] == 'g')) { s_map.setTextureRect(IntRect(0, 107, 30, 100)); }//Gun
					if ((TileMap[i][j] == 'G')) { s_map.setTextureRect(IntRect(0, 107, 30, 100)); }//Gun in window
					if ((TileMap[i][j] == 't')) { s_map.setTextureRect(IntRect(34, 107, 50, 100)); }//tabs
					if ((TileMap[i][j] == 'T')) { s_map.setTextureRect(IntRect(34, 107, 50, 100)); }//tabs in window
					if ((TileMap[i][j] == 'h')) { s_map.setTextureRect(IntRect(135, 107, 46, 100)); }//nahgman
					if ((TileMap[i][j] == 'k')) { s_map.setTextureRect(IntRect(185, 106, 105, 100)); }//knife
					if ((TileMap[i][j] == 'K')) { s_map.setTextureRect(IntRect(185, 106, 105, 100)); }//knife in window
					if ((TileMap[i][j] == 'r')) { s_map.setTextureRect(IntRect(293, 106, 100, 100)); }//Radiation 
					if ((TileMap[i][j] == 'R')) { s_map.setTextureRect(IntRect(293, 106, 100, 100)); }//Radiation in 
					if ((TileMap[i][j] == 'C')) { s_map.setTextureRect(IntRect(10, 212, 468, 375)); }
					if ((TileMap[i][j] == 'i')) { s_map.setTextureRect(IntRect(403, 106, 100, 100)); }//ice 
					if ((TileMap[i][j] == 'I')) { s_map.setTextureRect(IntRect(403, 106, 100, 100)); }//Ice in window
					if ((TileMap[i][j] == 'l')) { s_map.setTextureRect(IntRect(503, 106, 100, 100)); }//life 
					if ((TileMap[i][j] == 'L')) { s_map.setTextureRect(IntRect(503, 106, 100, 100)); }//Lifein window
					//cout << "x= " << j * 36 << "y= " << i * 53 << endl;
					s_map.setPosition(j * 36, i * 53);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат
					if ((TileMap[i][j] != ' ') && (TileMap[i][j] != 's') && (TileMap[i][j] != 'w') && (TileMap[i][j] != '0')
						&& (TileMap[i][j] != 'J') && (TileMap[i][j] != 'j')) {
						window.draw(s_map);
					}
				}
			t1.join();
			t4.join();
			tb1.join();
			window.draw(FC.getSprite());
			window.draw(FC1.getSprite());
			window.draw(Bot1.getSprite());
			//this_thread::sleep_for(100s);
			thread t3([&]() {
				if ((FC.getLifes() > 0) && (FC1.getLifes() > 0)&&(Bot1.getLifes()>0)) {
					text.setString("Осталось жизней:\n1 Player: " + to_string(FC.getLifes()) + 
						"\n2 Player : " + to_string(FC1.getLifes())+"\n1 Bot :"+ to_string(Bot1.getLifes()));//задает строку тексту
					text.setPosition(30, 30);//задаем позицию текста, центр камеры
				}});
			if (FC.getLifes() == 0 || FC1.getLifes() == 0||Bot1.getLifes()==0) {
				text.setScale(4, 4);
				text.setString("Победа! ");//задает строку тексту
				text.setPosition(550, 550);//задаем позицию текста, центр камеры
			}
			t3.join();
			window.draw(text);
		}
		window.setView(view);
		changeView();
		if (Menu == 0) {
			cout << time1bot << "MyTime";
		}
		if (AverageTimeDQ.size() > 0) {
		AverageTimeInDQ = accumulate(AverageTimeDQ.begin(), AverageTimeDQ.end(), 0) / AverageTimeDQ.size();
		cout <<"============++++" <<AverageTimeInDQ << endl;
		}
		window.display();
		if (Menu) {
		if(clock12.getElapsedTime().asSeconds() > 2){ Menu = 0; }
			clock1.restart();
			clockfor1pl.restart();
			Clockforbot1.restart();
		}
		cout << "End  " << endl;
	}
	return 0;
}

