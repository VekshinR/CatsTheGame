#pragma once
#include "Player.h"
#include <deque>
#include<queue>
#include<map>
#include<math.h>
#include<algorithm>
#include<stack>
#include<thread>

using namespace std;
using namespace sf;
struct BotPosition {
	int x, y,step;
	
	int Px, Py;//ParentsCoordinate
	BotPosition() {
		this->x = 0;
		this->y = 0;
		this->Py = 0;
		this->Px = 0;
		this->step = 0;
	}
	BotPosition(int y, int x) {
		this->x = x;
		this->y = y;
		this->Py = 0;
		this->Px = 0;
		this->step = 0;
	}
	BotPosition(int y, int x,int Py,int Px,int step) {
		this->x = x;
		this->y = y;
		this->Py = Py;
		this->Px = Px;
		this->step = step;
	}
	bool operator ==(const BotPosition& other) const;
	bool operator !=(const BotPosition& other) const;
	bool operator <(const BotPosition& other) const;
	bool operator >(const BotPosition& other) const;
	// Перегрузить операторы сравнения!
};

class Bot :public Player
{
public:
	Bot();
	~Bot();
protected:
	vector<int> CheckRoute;
	bool checkRouter = 0;
	int direction;
	BotPosition LastPosition;
	enum E_MapForBot {up_left=1,up,up_right,left,center,right,down_left,down,down_right} E_MapForBot;
	stack<int>MapForBot;
	void bindKeys(int a) override;
	void controlCharacter(float time) override;
	void Moving(float& time) override;
	void Death() override;
	void BecomeInvalid() override;
	int findAWay();
public:
	static bool NeedToFind;
	void GameProcess(float time, Clock& clock) override;
	void checkCollisionWithMap(float Dx, float Dy) override;
};


