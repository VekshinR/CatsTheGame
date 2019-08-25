#pragma once
#include"SFML/Audio.hpp"
#include"SFML/Graphics.hpp"
#include"map.h"
#include"View.h"
#include<iostream>

using namespace sf;
using namespace std;
class Player {
protected:
	enum State { left, right, up, down, jump, stay } State ;
	bool iJumping=0;
	static bool freezeOrNot;
	bool imFreezer = 0;
	static bool gameover;
	static bool lifesChanger;
	bool imLifeChanger = 0;
	int lifes = 9;
	int TypeName=1;
	int MyNumberAtVector;
	Keyboard::Key rightDir, leftDir, upDir;
	float speed = 0, Movespeed = 0.2, JumpSpeed = 0.8, dx = 0, dy = 0, x = 850, y = 250;
	float currenframe = 0;
	char Item;
	SoundBuffer jumpBuffer;
	Sound s_jump;
	SoundBuffer Buffer;
	Sound sound_Items;
	int Chance;
	float DeathTimer = 0;
	//float time;
	bool onGround;
	bool sentenceTo, sentenceId = 0;
	int Healthy = 2;
	Image image;
	Texture texture;
	enum Sounds { jump_so = 0, gun, knife, blevota, hanging, blizzard, scream };
	Sprite sprite;
	vector<string> sounds = { "sounds/jump.ogg","sounds/gun.ogg","sounds/knife.ogg","sounds/blevota.ogg","sounds/hanging.ogg",
		"sounds/blizzard.ogg","sounds/scream.ogg" };
	class PlayerType {
	public:
		vector <string> fileName;
		int width;
		int height;
		PlayerType(string file, string fileOfDeaths, int width, int height);
		PlayerType();
	};
	vector<PlayerType> Types = { PlayerType("DeathCat.png","Cat.png",80,106),PlayerType("DeathCat2.png","Cat.png",80,106) };
	PlayerType Character;

public:
	  Player(int HeroType, int number);
	  Player();
	  static void Pause(bool a);
protected:
	void setSounds();
	int getCoordinateX() {
		return x;
	}
	int getCoordinateY() {
		return y;
	}
	bool CheckOnGround();
	virtual void bindKeys(int a);
	virtual void controlCharacter(float time);
	virtual void checkCollisionWithMap(float Dx, float Dy);//ф ция проверки столкновений с картой
	virtual void Death();
	virtual void BecomeInvalid();
	bool ChanceToDie();
	virtual void Moving(float& time);
	bool CheckUseItems(Clock& clock);
	void Gravity(int zero);

	
	void update(float& time, Clock& clock);
public:
	virtual void GameProcess(float time, Clock & clock) {
		controlCharacter(time);
		update(time, clock);	
	}
	Sprite getSprite() {
		return sprite;
	}
	int getLifes() {
		return lifes;
	}
};

