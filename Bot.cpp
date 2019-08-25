#include "Bot.h"



Bot::Bot()
{
	Character = Types[1];
	image.loadFromFile("images/" + Character.fileName[0]);
	image.createMaskFromColor(Color::White);
	setSounds();
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	x = 700; y = 450;
	sprite.setTextureRect(IntRect(430, 300, Character.width, Character.height));
	sprite.setPosition(x + Character.width / 2, y + Character.height / 2);
	sprite.setOrigin(Character.width/2, Character.height / 2);
	onGround = 0;
	
		

}


Bot::~Bot()
{
}

void Bot::bindKeys(int a)
{
}

void Bot::controlCharacter(float time)
{
}

void Bot::Moving(float& time)
{
	if (Healthy != 1) {
		if ((freezeOrNot == 0) || ((freezeOrNot == 1) && (imFreezer == 1))) {
			int direct = center;
			if (!(MapForBot.empty())) {
				direct = MapForBot.top();
				cout << direct << "---direct" << endl;
				if ((LastPosition.y != getCoordinateY() / 53) || (LastPosition.x != getCoordinateX() / 36)) {
					
					MapForBot.pop();
					if (!(MapForBot.empty())) {
						direct = MapForBot.top();
					}
					else { direct = center; NeedToFind = 1; }
					
					LastPosition.x = getCoordinateX() / 36;
					LastPosition.y == getCoordinateY() / 53;
				}
				else {
					
				}

				
			}
			else {
				
			}

			
			if ((direct == left) && (x > 4)) {
				//this_thread::sleep_for(0.035s);
				E_MapForBot = left; speed = Movespeed;
				currenframe += 0.05 * time;
				if (Healthy == 2) {
					sprite.setTextureRect(IntRect(515, 300, Character.width, Character.height));
				}
				if (Healthy == 0) { sprite.setTextureRect(IntRect(685, 300, Character.width, Character.height)); }
				getPlayerCoordinate(getCoordinateX(), getCoordinateY());
			}
			if ((direct == up_left)  && (x > 4)) {
				if ((CheckOnGround())) {
					

						E_MapForBot = up_left; speed = Movespeed;

						currenframe += 0.05 * time;
						if (Healthy == 2) {
							sprite.setTextureRect(IntRect(515, 300, Character.width, Character.height));
						}
						if (Healthy == 0) { sprite.setTextureRect(IntRect(685, 300, Character.width, Character.height)); }
					
					
				}
				else {
					E_MapForBot = left; speed = Movespeed;
					currenframe += 0.05 * time;
					if (Healthy == 2) {
						sprite.setTextureRect(IntRect(515, 300, Character.width, Character.height));
					}
					if (Healthy == 0) { sprite.setTextureRect(IntRect(685, 300, Character.width, Character.height)); }

				}
				getPlayerCoordinate(getCoordinateX(), getCoordinateY());
			}
			if ((direct == up_right)  && (x > 4)) {
				if ((CheckOnGround())) {
					
						E_MapForBot = up_right; speed = Movespeed;
						currenframe += 0.05 * time;
						if (Healthy == 2) {
							sprite.setTextureRect(IntRect(515, 300, Character.width, Character.height));
						}
						if (Healthy == 0) { sprite.setTextureRect(IntRect(685, 300, Character.width, Character.height)); }
					
					
				}
				else {
					E_MapForBot = right; speed = Movespeed;
					currenframe += 0.05 * time;
					if (Healthy == 2) {
						sprite.setTextureRect(IntRect(430, 300, Character.width, Character.height));
					}
					if (Healthy == 0) { sprite.setTextureRect(IntRect(600, 300, Character.width, Character.height)); }

				}

				getPlayerCoordinate(getCoordinateX(), getCoordinateY());
			}
			if ((direct == right) && (x < 1540)) {
				cout << "rightHEre" << endl;
				E_MapForBot = right; speed = Movespeed;
				currenframe += 0.05 * time;
				if (Healthy == 2) {
					sprite.setTextureRect(IntRect(430, 300, Character.width, Character.height));
				}
				if (Healthy == 0) { sprite.setTextureRect(IntRect(600, 300, Character.width, Character.height)); }
				getPlayerCoordinate(getCoordinateX(), getCoordinateY());
			}
			if ((direct == down_left) && (x > 4)) {
				//this_thread::sleep_for(0.035s);
				E_MapForBot = down_left; speed = Movespeed;
				currenframe += 0.05 * time;
				if (Healthy == 2) {
					sprite.setTextureRect(IntRect(515, 300, Character.width, Character.height));
				}
				if (Healthy == 0) { sprite.setTextureRect(IntRect(685, 300, Character.width, Character.height)); }
				getPlayerCoordinate(getCoordinateX(), getCoordinateY());
			}
			if ((direct == down) && (x > 4)) {
				//this_thread::sleep_for(0.035s);
				E_MapForBot = down; speed = Movespeed;
				currenframe += 0.05 * time;
				if (Healthy == 2) {
					sprite.setTextureRect(IntRect(515, 300, Character.width, Character.height));
				}
				if (Healthy == 0) { sprite.setTextureRect(IntRect(685, 300, Character.width, Character.height)); }
				getPlayerCoordinate(getCoordinateX(), getCoordinateY());
			}
			if ((direct == down_right) && (x > 4)) {
				//this_thread::sleep_for(0.035s);

				E_MapForBot = down_right; speed = Movespeed;
				currenframe += 0.05 * time;
				if (Healthy == 2) {
					sprite.setTextureRect(IntRect(515, 300, Character.width, Character.height));
				}
				if (Healthy == 0) { sprite.setTextureRect(IntRect(685, 300, Character.width, Character.height)); }
				getPlayerCoordinate(getCoordinateX(), getCoordinateY());
			}
			if (((direct == up)) && (getCoordinateY() > 90)) {
				if ((CheckOnGround())) {

					E_MapForBot = up; speed = JumpSpeed;
					currenframe += 0.05 * time;
					onGround = 0;
					s_jump.setVolume(30);
					s_jump.play();
				}
				else {
						E_MapForBot = down_right; speed = Movespeed;
						currenframe += 0.05 * time;
					}

					//sprite.setTextureRect(IntRect(0, 0, Character.width, Character.height));
					
				
				
				getPlayerCoordinate(getCoordinateX(), getCoordinateY());
			}

		}
		cout << "heyhey" << endl;// Проблема где то от начала циклаи и до этого места
		if (Healthy != 1) {


			switch (E_MapForBot)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
			{
				cout << "Map for bot" << endl;
			case left: dx = -speed;   break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
			case right: dx = speed;    break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
			case up:if (CheckOnGround()) { dy = -speed; } break;//по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз
			case down:   break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
			case up_left:if (CheckOnGround()) { dx = -speed; speed = JumpSpeed; dy = -speed; } break;
			case up_right:if (CheckOnGround()) { dx = speed; speed = JumpSpeed; dy = -speed; } break;
			case down_left:dx = -speed; break;
			case down_right:dx = speed; break;
			}


			//cout << "direction" << direction << endl;
			//if (direction == left) { dx = -speed; cout << "left!!!" << endl; }//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
			//if (direction == right) { dx = speed; cout << "right!!!" << endl;}//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
			//if (direction == up) { dy = -speed; cout << "up!!!" << endl;}// иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз
			//if (direction == down) {}//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
			//if (direction == up_left) { dx = -speed; speed = JumpSpeed; dy = -speed; cout << "up_left!!!" << endl;}
			//if(direction==up_right){dx = speed; speed = JumpSpeed; dy = -speed; cout << "up_right!!!" << endl;}
			//if (direction == down_left) { dx = -speed; cout << "down_left!!!" << endl;}
			//if (direction==down_right){dx = speed; cout << "down_right!!!" << endl;}
			cout << "x= " << x << endl;
			x += dx * time;
			cout << time << " = time" << endl;//то движение из прошлого урока. наше ускорение на время получаем смещение координат и как следствие движение
			cout << "x= " << x << endl;
			cout <<"real X= "<< int(x / 36) << endl;
			checkCollisionWithMap(dx, 0);
			y += dy * time;//аналогично по игреку
			checkCollisionWithMap(0, dy);
			speed = 0;//зануляем скорость, чтобы персонаж остановился.
			//interactionWithMap();
		}
	}
}

void Bot::Death()
{
	if (TypeName == 0) {
		sprite.setTextureRect(IntRect(430, 310, Character.width, Character.height));
	}
	else { sprite.setTextureRect(IntRect(418, 310, Character.width, Character.height)); }
	lifes--;
	x = 850; y = 450;
	sprite.setPosition(x / 2, y / 2);
	while (!MapForBot.empty()) {
		MapForBot.pop();
	}
	Movespeed = 0.2;
	JumpSpeed = 0.8;
	Healthy = 2;
	imFreezer = 0;
	imLifeChanger = 0;
	lifesChanger = 0;
}

void Bot::BecomeInvalid()
{
	sprite.setTextureRect(IntRect(520, 310, Character.width, Character.height));
	x = 850; y = 450;
	sprite.setPosition(x / 2, y / 2);
	Movespeed = 0.08;
	JumpSpeed = 0.2;
	Healthy = 0;
	imLifeChanger = 0;
	while (!MapForBot.empty()) {
		MapForBot.pop();
	}
}

void Bot::GameProcess(float time, Clock& clock)
{
	Bot::y = Bot::getCoordinateY();
	Bot::x = Bot::getCoordinateX();
	if (NeedToFind && Healthy != 1) {
		cout << "findAway find" << endl;
		CheckRoute.clear();
		while (!MapForBot.empty()) {
			MapForBot.pop();
		}
		findAWay();
	}
	update(time, clock);
	getCoordinateX();
	
	//измерить время выполнения функции файнд
	
}

void Bot::checkCollisionWithMap(float Dx, float Dy)
{
	cout << "CheckCollisionWithMap! " << endl;
	
	for (int i = (int)(this->y / 53); i < (this->y + Character.height) / 53; i++) {//проходимся по элементам карты
		for (int j = int(this->x / 36); j < (this->x + Character.width) / 36; j++)
		{
			if (TileMap[i][j] == 's')//если элемент наш тайлик земли? то
			{
				if (Dy > 0) { this->y = i * 53 - Character.height; onGround = true; }//по Y вниз=>идем в пол(стоим на месте) или падаем. В этот момент надо вытолкнуть персонажа и поставить его на землю, при этом говорим что мы на земле тем самым снова можем прыгать
				if (Dy < 0) { this->y = i * 53 + 53; }//столкновение с верхними краями карты(может и не пригодиться)
				if (Dx > 0) { this->x = j * 36 - Character.width; }//с правым краем карты
				if (Dx < 0) { this->x = j * 36 + 36; }// с левым краем карты
			}
			if (lifes != 9) {
				if ((Dy > 0) && (TileMap[i][j] != 's')) {
					onGround = 0;
				}
			}
		}
	}
}

int Bot::findAWay()
{
	queue<BotPosition> BotMapQ;
	vector<BotPosition> BotMap;
	cout<<"X="<< Bot::getCoordinateX() <<"        y="<< Bot::getCoordinateY()<<endl;
	int J = Bot::getCoordinateY()/53;
	int I = Bot::getCoordinateX()/36;
	cout << I << "=x    " << J << "=y    " << endl;
	BotMapQ.push(BotPosition(J, I));
	map<BotPosition, int>wayBot;
	int TurnCode;
	LastPosition.x = I;
	LastPosition.y = J;
	int step = 0;
	wayBot[BotPosition(J, I)] = step;
	if (Healthy == 2) {
		while (!BotMapQ.empty() && NeedToFind) {
			int Y = BotMapQ.front().y;
			int X = BotMapQ.front().x;
			BotMapQ.pop();
			if (abs(Y - J) > abs(X - I)) {// проверить правильно ли реализован модуль чисел!!!!!
				step = (abs(Y - J) + 1) * 10;
			}
			else { step = (abs(X - I) + 1) * 10; }
			for (int jY = Y - 1; jY < Y + 2; jY++) {
				for (int iX = X - 1; iX < X + 2; iX++) {
					if (jY > 0 && jY < Height && iX>0 && iX < Width) {
						if ((Y != jY || X != iX) && wayBot.count(BotPosition(jY, iX)) == 0) {
							if (jY < Y && iX < X) {
								if (TileMap[Y - 1][X] == 's' || TileMap[Y - 2][X] == 's'
									|| TileMap[Y - 2][X + 1] == 's' || TileMap[Y - 2][X - 1] == 's' || TileMap[Y - 1][X + 1] == 's' || TileMap[Y - 1][X - 1] == 's') {
									//wayBot[BotPosition(jY, iX)] = (step + up_left);
								}
								else {
									BotMap.push_back(BotPosition(jY, iX, Y, X, step + up_left));
									TurnCode = up_left;
									wayBot[BotPosition(jY, iX)] = (step + up_left);
								}
							}
							if (jY < Y && iX == X) {
								if (TileMap[Y - 1][X] == 's' || TileMap[Y - 2][X] == 's'
									|| TileMap[Y - 2][X + 1] == 's' || TileMap[Y - 2][X - 1] == 's' || TileMap[Y - 1][X + 1] == 's' || TileMap[Y - 1][X - 1] == 's') {
									//wayBot[BotPosition(jY, iX)] = (step + up);
								}
								else {
									BotMap.push_back(BotPosition(jY, iX, Y, X, step + up));
									TurnCode = up;
									wayBot[BotPosition(jY, iX)] = (step + up);
								}
							}
							if (jY < Y && iX > X) {
								if (TileMap[Y - 1][X] == 's' || TileMap[Y - 2][X] == 's'
									|| TileMap[Y - 2][X + 1] == 's' || TileMap[Y - 2][X - 1] == 's' || TileMap[Y - 1][X + 1] == 's' || TileMap[Y - 1][X - 1] == 's') {
									//wayBot[BotPosition(jY, iX)] = (step + up_right);
								}
								else {
									BotMap.push_back(BotPosition(jY, iX, Y, X, step + up_right));
									TurnCode = up_right;
									wayBot[BotPosition(jY, iX)] = (step + up_right);
								}
							}
							if (jY == Y && iX < X) {
								BotMap.push_back(BotPosition(jY, iX, Y, X, step + left));
								TurnCode = left;
								wayBot[BotPosition(jY, iX)] = (step + left);
							}
							if (jY == Y && iX > X) {
								BotMap.push_back(BotPosition(jY, iX, Y, X, step + right));
								TurnCode = right;
								wayBot[BotPosition(jY, iX)] = (step + right);
							}
							if (jY > Y && iX < X) {
								BotMap.push_back(BotPosition(jY, iX, Y, X, step + down_left));
								TurnCode = down_left;
								wayBot[BotPosition(jY, iX)] = (step + down_left);
							}
							if (jY > Y && iX == X) {
								BotMap.push_back(BotPosition(jY, iX, Y, X, step + down));
								TurnCode = down;
								wayBot[BotPosition(jY, iX)] = (step + down);
							}
							if (jY > Y && iX > X) {
								BotMap.push_back(BotPosition(jY, iX, Y, X, step + down_right));
								TurnCode = down_right;
								wayBot[BotPosition(jY, iX)] = (step + down_right);
							}
							if (TileMap[jY][iX] == 's') {
								wayBot[BotPosition(jY, iX + 1)] = (step + up_right);
								wayBot[BotPosition(jY, iX - 1)] = (step + up_left);
							}
							else {
								if ((TileMap[Y - 1][X] == 's' || TileMap[Y - 2][X] == 's'
									|| TileMap[Y - 2][X + 1] == 's' || TileMap[Y - 2][X - 1] == 's' || TileMap[Y - 1][X + 1] == 's' || TileMap[Y - 1][X - 1] == 's')
									&& ((jY < Y && iX < X) || (jY < Y && iX == X) || (jY < Y && iX > X))) {
								}
								else {
									BotMapQ.push(BotPosition(jY, iX));
								}
							}
							cout << "Join = " << BotMap.size() << (char)TileMap[jY][iX] << "x=" << iX << "y=" << jY << endl;
							auto find1 = find(ItemsInWindow.begin(), ItemsInWindow.end(), TileMap[jY][iX]);
							auto find2 = find(Items.begin(), Items.end(), TileMap[jY][iX]);
							if ((find1 != ItemsInWindow.end()) || (find2 != Items.end())) {
								cout << "Вошел";
								//vector<BotPosition> wayCorrector;
								int Previous = 5, ParentX, OwnY = jY, OwnX = iX;
								while (!(OwnY == J && OwnX == I)) {
									for (int i = BotMap.size() - 1; i > -1; i--) {
										if (BotMap[i] == BotPosition(OwnY, OwnX)) {
											cout << "TUrn " << BotMap[i].step % 10 << endl;
											cout << (char)TileMap[BotMap[i].Py - 1][BotMap[i].Px] << " - " << (char)TileMap[BotMap[i].Py - 2][BotMap[i].Px] << endl;
											cout << "Previous " << Previous << endl;
											if (BotMap[i].step % 10 == 4) {
												if (Previous == 3) {
													MapForBot.push(3);
													MapForBot.push(4);
													//CheckRoute.push_back(4);
													//CheckRoute.push_back(3);
												}
												if (Previous == 2) {
													MapForBot.push(2);
													MapForBot.push(4);
													//CheckRoute.push_back(4);
													//CheckRoute.push_back(2);
												}
												if (Previous == 9) {
													MapForBot.push(9);
													MapForBot.push(4);
													//CheckRoute.push_back(4);
													//CheckRoute.push_back(9);
												}
												else {
													MapForBot.push(4);
													//CheckRoute.push_back(4);
												}
												Previous = 4;
											}
											if (BotMap[i].step % 10 == 6) {
												if (Previous == 1) {
													MapForBot.push(1);
													MapForBot.push(6);
													//CheckRoute.push_back(6);
													//CheckRoute.push_back(1);
												}
												if (Previous == 2) {
													MapForBot.push(2);
													MapForBot.push(6);
													//CheckRoute.push_back(6);
													//CheckRoute.push_back(2);
												}
												if (Previous == 7) {
													MapForBot.push(7);
													MapForBot.push(6);
													//CheckRoute.push_back(6);
													//CheckRoute.push_back(7);
												}
												else {
													MapForBot.push(6);
													//CheckRoute.push_back(6);
												}
												Previous = 6;
											}
											else {
												MapForBot.push(BotMap[i].step % 10);
												Previous = BotMap[i].step % 10;
												//CheckRoute.push_back(BotMap[i].step % 10);
											}
											//MapForBot.push(BotMap[i].step % 10);
											OwnY = BotMap[i].Py;
											OwnX = BotMap[i].Px;
										}
									}
								}
								/*for (int it = CheckRoute.size() - 1; it > 0; it--) {
									cout << CheckRoute[it] << " ";
								}
								cout << endl;*/
								NeedToFind = 0;
								return 0;
							}
						}
					}
				}
			}
			//Доделать поиск в ширину, добавить проверку координат на соответствие цели и выход из функции и цикла,сделать вектор маршрута с привязкой к числу(Энуму) (в зависимости от числа будет
			//выполняться опредленное действие, добавить вектор родителей для построения обратного пути )
		}
	}
	if (Healthy == 0) {
		while (!BotMapQ.empty() && NeedToFind) {
			int Y = BotMapQ.front().y;
			int X = BotMapQ.front().x;
			BotMapQ.pop();
			if (abs(Y - J) > abs(X - I)) {// проверить правильно ли реализован модуль чисел!!!!!
				step = (abs(Y - J) + 1) * 10;
			}
			else { step = (abs(X - I) + 1) * 10; }
			for (int jY = Y ; jY < Y + 2; jY++) {
				for (int iX = X-1 ; iX < X + 2; iX++) {
					if (jY > 0 && jY < Height && iX>0 && iX < Width) {
						if ((Y != jY || X != iX) && wayBot.count(BotPosition(jY, iX)) == 0) {
							if (jY < Y && iX < X) {
								if (TileMap[Y - 1][X] == 's' || TileMap[Y - 2][X] == 's'
									|| TileMap[Y - 2][X + 1] == 's' || TileMap[Y - 2][X - 1] == 's' || TileMap[Y - 1][X + 1] == 's' || TileMap[Y - 1][X - 1] == 's') {
									//wayBot[BotPosition(jY, iX)] = (step + up_left);
								}
								else {
									BotMap.push_back(BotPosition(jY, iX, Y, X, step + up_left));
									TurnCode = up_left;
									wayBot[BotPosition(jY, iX)] = (step + up_left);
								}
							}
							if (jY < Y && iX == X) {
								if (TileMap[Y - 1][X] == 's' || TileMap[Y - 2][X] == 's'
									|| TileMap[Y - 2][X + 1] == 's' || TileMap[Y - 2][X - 1] == 's' || TileMap[Y - 1][X + 1] == 's' || TileMap[Y - 1][X - 1] == 's') {
									//wayBot[BotPosition(jY, iX)] = (step + up);
								}
								else {
									BotMap.push_back(BotPosition(jY, iX, Y, X, step + up));
									TurnCode = up;
									wayBot[BotPosition(jY, iX)] = (step + up);
								}
							}
							if (jY < Y && iX > X) {
								if (TileMap[Y - 1][X] == 's' || TileMap[Y - 2][X] == 's'
									|| TileMap[Y - 2][X + 1] == 's' || TileMap[Y - 2][X - 1] == 's' || TileMap[Y - 1][X + 1] == 's' || TileMap[Y - 1][X - 1] == 's') {
									//wayBot[BotPosition(jY, iX)] = (step + up_right);
								}
								else {
									BotMap.push_back(BotPosition(jY, iX, Y, X, step + up_right));
									TurnCode = up_right;
									wayBot[BotPosition(jY, iX)] = (step + up_right);
								}
							}
							if (jY == Y && iX < X) {
								BotMap.push_back(BotPosition(jY, iX, Y, X, step + left));
								TurnCode = left;
								wayBot[BotPosition(jY, iX)] = (step + left);
							}
							if (jY == Y && iX > X) {
								BotMap.push_back(BotPosition(jY, iX, Y, X, step + right));
								TurnCode = right;
								wayBot[BotPosition(jY, iX)] = (step + right);
							}
							if (jY > Y && iX < X) {
								BotMap.push_back(BotPosition(jY, iX, Y, X, step + down_left));
								TurnCode = down_left;
								wayBot[BotPosition(jY, iX)] = (step + down_left);
							}
							if (jY > Y && iX == X) {
								BotMap.push_back(BotPosition(jY, iX, Y, X, step + down));
								TurnCode = down;
								wayBot[BotPosition(jY, iX)] = (step + down);
							}
							if (jY > Y && iX > X) {
								BotMap.push_back(BotPosition(jY, iX, Y, X, step + down_right));
								TurnCode = down_right;
								wayBot[BotPosition(jY, iX)] = (step + down_right);
							}
							if (TileMap[jY][iX] == 's') {
								wayBot[BotPosition(jY, iX + 1)] = (step + up_right);
								wayBot[BotPosition(jY, iX - 1)] = (step + up_left);
							}
							else {
								if ((TileMap[Y - 1][X] == 's' || TileMap[Y - 2][X] == 's'
									|| TileMap[Y - 2][X + 1] == 's' || TileMap[Y - 2][X - 1] == 's' || TileMap[Y - 1][X + 1] == 's' || TileMap[Y - 1][X - 1] == 's')
									&& ((jY < Y && iX < X) || (jY < Y && iX == X) || (jY < Y && iX > X))) {
								}
								else {
									BotMapQ.push(BotPosition(jY, iX));
								}
							}
							auto find1 = find(ItemsInWindow.begin(), ItemsInWindow.end(), TileMap[jY][iX]);
							auto find2 = find(Items.begin(), Items.end(), TileMap[jY][iX]);
							if ((find1 != ItemsInWindow.end()) || (find2 != Items.end())) { 
								int Previous = 5, ParentX, OwnY = jY, OwnX = iX;
								while (!(OwnY == J && OwnX == I)) {
									for (int i = BotMap.size() - 1; i > -1; i--) {
										if (BotMap[i] == BotPosition(OwnY, OwnX)) {
											if (BotMap[i].step % 10 == 4) {
												if (Previous == 3) {
													MapForBot.push(3);
													MapForBot.push(4);
													//CheckRoute.push_back(4);
													//CheckRoute.push_back(3);
												}
												if (Previous == 2) {
													MapForBot.push(2);
													MapForBot.push(4);
													//CheckRoute.push_back(4);
													//CheckRoute.push_back(2);
												}
												if (Previous == 9) {
													MapForBot.push(9);
													MapForBot.push(4);
													//CheckRoute.push_back(4);
													//CheckRoute.push_back(9);
												}
												else {
													MapForBot.push(4);
													//CheckRoute.push_back(4);
												}
												Previous = 4;
											}
											if (BotMap[i].step % 10 == 6) {
												if (Previous == 1) {
													MapForBot.push(1);
													MapForBot.push(6);
													//CheckRoute.push_back(6);
													//CheckRoute.push_back(1);
												}
												if (Previous == 2) {
													MapForBot.push(2);
													MapForBot.push(6);
													//CheckRoute.push_back(6);
													//CheckRoute.push_back(2);
												}
												if (Previous == 7) {
													MapForBot.push(7);
													MapForBot.push(6);
													//CheckRoute.push_back(6);
													//CheckRoute.push_back(7);
												}
												else {
													MapForBot.push(6);
													//CheckRoute.push_back(6);
												}
												Previous = 6;
											}
											else {
												MapForBot.push(BotMap[i].step % 10);
												Previous = BotMap[i].step % 10;
												//CheckRoute.push_back(BotMap[i].step % 10);
											}
											//MapForBot.push(BotMap[i].step % 10);
											OwnY = BotMap[i].Py;
											OwnX = BotMap[i].Px;
										}
									}
								}
								cout << "return 0" << endl;
								/*for (int it = CheckRoute.size() - 1; it > 0; it--) {
									cout << CheckRoute[it] << " ";
								}
								cout << endl;*/
								NeedToFind = 0;
								return 0;
							}
						}
					}
				}
			}
			//Доделать поиск в ширину, добавить проверку координат на соответствие цели и выход из функции и цикла,сделать вектор маршрута с привязкой к числу(Энуму) (в зависимости от числа будет
			//выполняться опредленное действие, добавить вектор родителей для построения обратного пути )
	}
	}
}

bool BotPosition::operator==(const BotPosition& other) const
{
	if (this->y == other.y && this->x == other.x) {
		return true;
	}
	else
	 {
	return false;
}
}

bool BotPosition::operator!=(const BotPosition& other) const
{
	if (this->y == other.y && this->x == other.x) {
		return false;
	}
	else
	{
		return true;
	}
}

bool BotPosition::operator<(const BotPosition& other) const
{
	if (this->y < other.y) {
		return true;
	}
	else {
		if (this->y == other.y) {
			if (this->x < other.x) {
				return true;
			}
			else {
				return false;
			}
		}
		return false;
	}
}

bool BotPosition::operator>(const BotPosition& other) const
{
	if (this->y > other.y) {
		return true;
	}
	else {
		if (this->y == other.y) {
			if (this->x > other.x) {
				return true;
			}
			else {
				return false;
			}
		}
		return false;
	}
}
bool Bot::NeedToFind = 1;