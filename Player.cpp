#include "Player.h"

Player::PlayerType::PlayerType(string file, string fileOfDeaths, int width, int height)
{	
		fileName.push_back(file);
		fileName.push_back(fileOfDeaths);
		this->width = width;
		this->height = height;
}

Player::PlayerType::PlayerType()
{
	this->width = 0;
	this->height = 0;
}

Player::Player(int HeroType, int number)
{
	MyNumberAtVector = number;
	TypeName = HeroType;
	Character = Types[HeroType];
	bindKeys(number);
	image.loadFromFile("images/" + Character.fileName[0]);
	image.createMaskFromColor(Color::White);
	setSounds();
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(430, 300, Character.width, Character.height));
	sprite.setPosition(x + Character.width / 2, y + Character.height / 2);
	sprite.setOrigin(Character.width/2 , (Character.height / 2));
	onGround = 0;
	if (MyNumberAtVector > 0) {
		x = 850; y = 450;
	}
}

Player::Player()
{
}

void Player::Pause(bool a)
{
	if (a == 1) {
		freezeOrNot = 1;
}
	if (a == 0) {
		freezeOrNot = 0;
	}
}

void Player::setSounds()
{
	jumpBuffer.loadFromFile(sounds[jump_so]);//загружаем в него звук
	s_jump.setBuffer(jumpBuffer);
}

bool Player::CheckOnGround()
{
		int groundY = getCoordinateY()/53;
	int groundX = getCoordinateX() / 36;
	if ((char)TileMap[groundY + 2][groundX] == 's') {
		return true;
	}
	else{ return false; }
}

void Player::bindKeys(int a)
{
	if (a == 0) {
		leftDir = Keyboard::A;
		rightDir = Keyboard::D;
		upDir = Keyboard::W;
	}
	if (a == 1) {
		leftDir = Keyboard::Left;
		rightDir = Keyboard::Right;
		upDir = Keyboard::Up;
	}
}

void Player::controlCharacter(float time)
{
	if ((freezeOrNot == 0) || ((freezeOrNot == 1) && (imFreezer == 1))) {
		if ((Keyboard::isKeyPressed(leftDir)) && (x > 4)) {
			//this_thread::sleep_for(0.035s);
			State = left; speed = Movespeed;
			currenframe += 0.05 * time;
			if (Healthy == 2) {
				sprite.setTextureRect(IntRect(515, 310, Character.width, Character.height));
			}
			if (Healthy == 0) { sprite.setTextureRect(IntRect(685, 310, Character.width, Character.height)); }
			getPlayerCoordinate(getCoordinateX(), getCoordinateY());
		}
		if ((Keyboard::isKeyPressed(rightDir)) && (x < 1540)) {
			State = right; speed = Movespeed;
			currenframe += 0.05 * time;
			if (Healthy == 2) {
				sprite.setTextureRect(IntRect(430, 310, Character.width, Character.height));
			}
			if (Healthy == 0) { sprite.setTextureRect(IntRect(600, 310, Character.width, Character.height)); }
			getPlayerCoordinate(getCoordinateX(), getCoordinateY());
		}
		if ((onGround == true) && (Keyboard::isKeyPressed(upDir)) && (getCoordinateY() > 90)) {
			State = jump; speed = JumpSpeed;
			currenframe += 0.05 * time;
			onGround = 0;
			s_jump.setVolume(30);
			s_jump.play();
			//sprite.setTextureRect(IntRect(0, 0, Character.width, Character.height));
			getPlayerCoordinate(getCoordinateX(), getCoordinateY());
		}

	}
}

void Player::checkCollisionWithMap(float Dx, float Dy)
{
	for (int i = (int)(this->y / 53); i < (this->y + Character.height) / 53; i++)//проходимся по элементам карты
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

void Player::Death()
{
	if (TypeName == 0) {
		sprite.setTextureRect(IntRect(430, 310, Character.width, Character.height));
	}
	else{ sprite.setTextureRect(IntRect(418, 310, Character.width, Character.height)); }
	lifes--;
	x = 850; y = 450;
	sprite.setPosition(x / 2, y / 2);
	Movespeed = 0.2;
	JumpSpeed = 0.8;
	Healthy = 2;
	imFreezer = 0;
	imLifeChanger = 0;
	lifesChanger = 0;
}

void Player::BecomeInvalid()
{
	sprite.setTextureRect(IntRect(520, 310, Character.width, Character.height));
	x = 850; y = 450;
	sprite.setPosition(x / 2, y / 2);
	Movespeed = 0.05;
	JumpSpeed = 0.2;
	Healthy = 0;
	imLifeChanger = 0;
}

bool Player::ChanceToDie()
{
	srand(time(NULL));
	int DieOrNot = rand() % 100 + 1;
	std::cout << "--------------------CHANCE----" << DieOrNot << endl;
	if (DieOrNot <= Chance) { return 1; }
	else { return 0; }
}

void Player::Moving(float& time)
{
	if (Healthy != 1) {
		switch (State)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
		{
		case left: dx = -speed;   break;//по иксу задаем положительную скорость, по игреку зануляем. получаем, что персонаж идет только вправо
		case right: dx = speed;    break;//по иксу задаем отрицательную скорость, по игреку зануляем. получается, что персонаж идет только влево
		case up:   break;//по иксу задаем нулевое значение, по игреку положительное. получается, что персонаж идет только вниз
		case down: dy = speed;   break;//по иксу задаем нулевое значение, по игреку отрицательное. получается, что персонаж идет только вверх
		case jump:dy = -speed; break;
		}
		std::cout << "\n" << dx << "=DX True+T" << endl;
		x += dx * time;//то движение из прошлого урока. наше ускорение на время получаем смещение координат и как следствие движение
		checkCollisionWithMap(dx, 0);
		std::cout << "\n" << x << "=X True+T" << endl;
		y += dy * time;//аналогично по игреку
		checkCollisionWithMap(0, dy);
		speed = 0;//зануляем скорость, чтобы персонаж остановился.
		//interactionWithMap();
	}
}

bool Player::CheckUseItems(Clock& clock)
{
	if (Healthy != 1) {
		for (int i = y / 53; i < (y + Character.height) / 53; i++)//проходимся по элементам карты
			for (int j = x / 36; j < (x + Character.width) / 36; j++) {
				
				if ((TileMap[i][j] == 't')) {
					Chance = 40; Item = 't'; Buffer.loadFromFile(sounds[blevota]); sound_Items.setBuffer(Buffer);
					sound_Items.setVolume(100); sound_Items.play(); TileMap[i][j] = ' '; Healthy = 1; return 1;
				}//tabl
				if ((TileMap[i][j] == 'T')) {
					Chance = 40; Item = 'T'; Buffer.loadFromFile(sounds[blevota]); sound_Items.setBuffer(Buffer);
					sound_Items.setVolume(100); sound_Items.play(); TileMap[i][j] = 'w'; Healthy = 1; return 1;
				}//tabl in window
				if ((TileMap[i][j] == 'g')) {
					Chance = 70; Item = 'g'; Buffer.loadFromFile(sounds[gun]); sound_Items.setBuffer(Buffer);
					sound_Items.setVolume(70); sound_Items.play(); TileMap[i][j] = ' '; Healthy = 1; return 1;
				}//Gun
				if ((TileMap[i][j] == 'G')) {
					Chance = 70; Item = 'G'; Buffer.loadFromFile(sounds[gun]); sound_Items.setBuffer(Buffer);
					sound_Items.setVolume(70); sound_Items.play(); TileMap[i][j] = 'w'; Healthy = 1; return 1;
				}//Gun in window
				if ((TileMap[i][j] == 'p')) {
					Chance = 60; Item = 'p'; Buffer.loadFromFile(sounds[blevota]); sound_Items.setBuffer(Buffer);
					sound_Items.setVolume(100); sound_Items.play(); TileMap[i][j] = ' '; Healthy = 1; return 1;
				}//poison
				if ((TileMap[i][j] == 'P')) {
					Chance = 60; Item = 'P'; Buffer.loadFromFile(sounds[blevota]); sound_Items.setBuffer(Buffer);
					sound_Items.setVolume(100); sound_Items.play(); TileMap[i][j] = 'w'; Healthy = 1; return 1;
				}//poison in window
				if ((TileMap[i][j] == 'h')) {
					Chance = 80; Item = 'h'; Buffer.loadFromFile(sounds[hanging]); sound_Items.setBuffer(Buffer);
					sound_Items.setVolume(100); sound_Items.play(); TileMap[i][j] = ' '; Healthy = 1; return 1;
				}//nahgman
				if ((TileMap[i][j] == 'k')) {
					Chance = 50; Item = 'K'; Buffer.loadFromFile(sounds[knife]); sound_Items.setBuffer(Buffer);
					sound_Items.setVolume(50); sound_Items.play(); TileMap[i][j] = ' '; Healthy = 1; return 1;
				}//knife
				if ((TileMap[i][j] == 'K')) {
					Chance = 50; Item = 'K'; Buffer.loadFromFile(sounds[knife]); sound_Items.setBuffer(Buffer);
					sound_Items.setVolume(50); sound_Items.play(); TileMap[i][j] = 'w'; Healthy = 1; return 1;
				}//knife in window
				if ((TileMap[i][j] == 'r')) {
					Chance = 30; Item = 'r'; TileMap[i][j] = ' '; Buffer.loadFromFile(sounds[blevota]); sound_Items.setBuffer(Buffer);
					sound_Items.setVolume(100); sound_Items.play(); Healthy = 1; return 1;
				}//Radiotion 
				if ((TileMap[i][j] == 'R')) {
					Chance = 30; Item = 'R'; TileMap[i][j] = 'w'; Buffer.loadFromFile(sounds[blevota]); sound_Items.setBuffer(Buffer);
					sound_Items.setVolume(100); sound_Items.play(); Healthy = 1; return 1;
				}//Radiotion in window
				if ((TileMap[i][j] == 'I')) {
					Item = 'I'; TileMap[i][j] = 'w'; Buffer.loadFromFile(sounds[blizzard]); sound_Items.setBuffer(Buffer);
					sound_Items.setVolume(100); sound_Items.play(); imFreezer = 1; freezeOrNot = 1; return 1;
				}//ice in window
				if ((TileMap[i][j] == 'i')) {
					Item = 'i'; TileMap[i][j] = ' '; Buffer.loadFromFile(sounds[blizzard]); sound_Items.setBuffer(Buffer);
					sound_Items.setVolume(100); sound_Items.play(); imFreezer = 1; freezeOrNot = 1; return 1;
				}//ice
				if ((TileMap[i][j] == 'L')) {
					Item = 'L'; TileMap[i][j] = 'w'; Buffer.loadFromFile(sounds[scream]); sound_Items.setBuffer(Buffer);
					sound_Items.setVolume(100); sound_Items.play(); imLifeChanger = 1; lifesChanger = 1; return 1;
				}//Life in window
				if ((TileMap[i][j] == 'l')) {
					Item = 'l'; TileMap[i][j] = ' '; Buffer.loadFromFile(sounds[scream]); sound_Items.setBuffer(Buffer);
					sound_Items.setVolume(100); sound_Items.play(); imLifeChanger = 1; lifesChanger = 1; return 1;
				}// life in window
			}
		return 0;
	}
}



void Player::Gravity(int zero)
{
	if (Healthy != 1) {
		if (y <= 1350) {
			if ((CheckOnGround() == false)) {
			}
			else {				
				dy = 0;
				onGround = true;
			}
		}
	}
}

void Player::update(float& time, Clock& clock)
{
	if (((lifes > 0) && ((freezeOrNot == 0))) || ((lifes > 0) && (freezeOrNot == 1) && (imFreezer == 1))) {
		//cout << lifes;
		//cout << "x= " << getCoordinateX() << "y= " << getCoordinateY() << endl;
		Gravity(0);
		if (CheckUseItems(clock) == 1) {
			clock.restart();
		}
		if (imLifeChanger == 0 && lifesChanger == 1) {
			if (lifes < 9) {
				lifes++;
			}
		}
		if (Healthy == 1) {
			DeathTimer = clock.getElapsedTime().asMilliseconds();
			if (DeathTimer <= 1000) {
				/*image.loadFromFile("images/" + Character.fileName[1]);
				image.createMaskFromColor(Color::White);
				texture.loadFromImage(image);
				sprite.setTexture(texture);*/
				if (Item == 't' || Item == 'T' || Item == 'p' || Item == 'P' || Item == 'R' || Item == 'r') {
					sprite.setTextureRect(IntRect(630, 0, Character.width, Character.height));
					sprite.setPosition(x + Character.width / 2, y + Character.height / 2);
					//sprite.setOrigin(Character.width / 2, Character.height / 2);
				}
				if (Item == 'k' || Item == 'K' || Item == 'g' || Item == 'G') {
					//sprite.setTextureRect(IntRect(640, 155, Character.width, Character.height));
					//sprite.setPosition(x + Character.width / 2, y + Character.height / 2);
					////sprite.setOrigin(Character.width / 2, Character.height / 2);
				}
				if (Item == 'h') {
					sprite.setTextureRect(IntRect(0, 0, 200, 313));
					sprite.setPosition(1300, 340);
					//sprite.setOrigin(Character.width / 2, Character.height / 2);
				}
				if (Item == 'f') {
					sprite.setTextureRect(IntRect(640, 155, Character.width, Character.height));
					sprite.setRotation(90);
					sprite.setPosition(x, 1470);
					//sprite.setOrigin(Character.width / 2, Character.height / 2);
				}
			}
			if (DeathTimer > 1000 && DeathTimer <= 4000) {
				if (Item == 'f') {
					sprite.setTextureRect(IntRect(640, 155, Character.width, Character.height));
					sprite.setRotation(90);
					sprite.setPosition(x, 1470);
					//sprite.setOrigin(Character.width / 2, Character.height / 2);
				}
				if (Item == 't' || Item == 'T' || Item == 'p' || Item == 'P' || Item == 'R' || Item == 'r') {
					if ((int)DeathTimer % 1000 < 500) {
						sprite.setTextureRect(IntRect(730, 0, Character.width, Character.height));
						sprite.setPosition(x + Character.width / 2, y + Character.height / 2);
					}
					else {
						sprite.setTextureRect(IntRect(815, 0, Character.width, Character.height));
						sprite.setPosition(x + Character.width / 2, y + Character.height / 2);
					}
					//sprite.setOrigin(Character.width / 2, Character.height / 2);
				}
				if (Item == 'k' || Item == 'K') {
					sprite.setTextureRect(IntRect(640, 155, Character.width, Character.height));
					sprite.setPosition(x + Character.width / 2, y + Character.height / 2);
					//sprite.setOrigin(Character.width / 2, Character.height / 2);
				}
				if (Item == 'g' || Item == 'G') {
					if (DeathTimer > 1500) {
						sprite.setTextureRect(IntRect(640, 155, Character.width, Character.height));
						sprite.setPosition(x + Character.width / 2, y + Character.height / 2);
					}
					//sprite.setOrigin(Character.width / 2, Character.height / 2);
				}
				if (Item == 'h') {
					if (DeathTimer > 1500) {
						if ((int)DeathTimer % 400 < 200) {
							sprite.setTextureRect(IntRect(201, 0, 200, 300));
							sprite.setPosition(1300, 340);
						}
						else {
							sprite.setTextureRect(IntRect(401, 0, 230, 300));
							sprite.setPosition(1300, 340);
						}
					}
					//sprite.setOrigin(Character.width / 2, Character.height / 2);
				}
			}
			if (DeathTimer > 4000 && DeathTimer <= 6000) {
				if (sentenceId == 0) {
					if (Item == 'f') {
						sprite.setRotation(0);
						//cout << "HUIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII" << endl;
					}
					if (Item != 'f') {
						x = 200;
					}
					sentenceTo = ChanceToDie();
					sentenceId = 1;
					//cout << "Sentence TO = " << sentenceTo << endl; 
				}
				if (sentenceTo == 1) {
					sprite.setTextureRect(IntRect(740, 160, Character.width, Character.height));
					sprite.setPosition(850, 530);
				}
				else {
					sprite.setTextureRect(IntRect(0, 330, 420, 228));
					if (x < 1300) { x += 30; }
					sprite.setPosition(x, 1370);
				}
			}
			if (DeathTimer > 6000) {
				if (sentenceTo == 1) {
					Death();
					sentenceId = 0;
				}
				else {
					BecomeInvalid();
					sentenceId = 0;
				}
				DeathTimer = 0;
			}
		}
		Gravity(0);
		Moving(time);
		if (Healthy != 1) {
			sprite.setPosition(x + Character.width / 2, y + Character.height / 2); //выводим спрайт в позицию x y , посередине. бесконечно выводим в этой функции, иначе бы наш спрайт стоял на месте.
		}
		if (Healthy != 1) {
			if ((y > 1350 && x < 175) || (y > 1350 && x > 1470)) {
				Item = 'f';
				Chance = 50;
				Healthy = 1;
				clock.restart();
			}
		}
		if (Healthy != 1) {
			if ((y > 1105 && y < 1250 && x>175 && x < 1470)) {
				y = 1104;
			}
		}
		if (Healthy != 1) {
			if (y <= 1350) {
				if((CheckOnGround()==false)) {
					dy = dy + 0.0015*time;
				}
				else {
					dy = 0;
					onGround = true;
				}
			}
		}
		if (imLifeChanger == 0 && lifesChanger == 1) {
			lifesChanger = 0;
		}
	}
	if ((lifes > 0) && (freezeOrNot == 1) && (imFreezer == 0)) {
		if (DeathTimer == 0) { clock.restart(); }
		DeathTimer =1+clock.getElapsedTime().asMilliseconds();
		cout<<DeathTimer<<"Death TImer"<<endl;
		if (DeathTimer <= 5000) {
			sprite.setTextureRect(IntRect(790, 300, 123, 115));
			sprite.setPosition(x + Character.width / 2, y + Character.height / 2);
			//sprite.setOrigin(Character.width / 2, Character.height / 2);
		}
		if (DeathTimer > 5000) {
			freezeOrNot = 0;
			DeathTimer = 0;
		}
		std::cout << DeathTimer << endl;
	}
}
bool Player::freezeOrNot = 0;
bool Player::lifesChanger = 0;
