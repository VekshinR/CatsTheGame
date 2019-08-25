#include "map.h"


const int Height = 30;
const int Width = 46;
vector<char> ItemsInWindow{ 'P','T','K','R','I','G','L' };
vector<char> Items{ 'p','t','k','r','i','g','h','l','j' };
string Map_Text = "images/Textures.png";
sf::String TileMap[Height]{
	"                                             ",
	"                                             ",
	"                                             ",
	"                      ssssssss               ",
	"                      wwwwwwww               ",
	"                      wwwwwwww               ",
	"                      wwwwwwww               ",
	"             ssssssssssssssssssssss          ",
	"             wwwwwwwwwwwwwwwwwwwwww          ",
	"             wwwwwwwwwwwwwwwwwwwwww          ",
	"             wwwwwwwwwwwwwwwwwwwwww          ",
	"       ssssssssssssssssssssswwwssssssssss    ",
	"       wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwws    ",
	"  j    JwwwwwwwwwwwwwwwwwwwwwJwwwwwwwwwws  j ",
	"       wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwws    ",
	"       sssssssssssssswwwsssssssssssssssss    ",
	"       swwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww    ",
	"       swwwwwwwwwwwwwwJwwwwwwwwwwwwwwwwwJ    ",
	"       swwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww  j ",
	"       ssssswwwssssssssssssssssssssssssss    ",
	"       wwwwwwwwswwwwwwwwwwwwwwwwwwwwwwwww    ",
	"       JwwwwwJJswwwwwwwwwwwwwwwwwwwwwwwwJ    ",
	"       wwwwwwwwswwwwwwwwwwwwwwwwCwwwwwwww    ",
	"   j   ssssssssssssssssssssssssssssssssss  j ",
	"       swwwwwwwwswwwwwwwswwwwwwwwwwwwwwws    ",
	"       swwwwwwwwswwwwwwwswwwwwwwwwwwwwwws    ",
	"       swwwwwwwwswwwwwwwswwwwwwwwwwwwwwws    ",
	"       swwwwwwwwswwwwwwwswwwwwwwwwwwwwwws    ",
	"000000000000000000000000000000000000000000000",
	"000000000000000000000000000000000000000000000" };

void SpawnItems(int timer)
{
	srand(time(NULL));
	//cout << timer << endl;
	if (timer % 30 == 0) { timer = 1; }
	if (timer == 1) {
		TileMap[13][37] = ItemsInWindow[rand() % (ItemsInWindow.size()-1)];
		TileMap[13][10] = ItemsInWindow[rand() % (ItemsInWindow.size() - 2)];
		TileMap[1][25] = Items[rand() % 2 + 5];
		TileMap[17][10] = ItemsInWindow[rand() % (ItemsInWindow.size() - 2)];
		TileMap[5][16] = Items[rand() % (Items.size() - 1)];
		TileMap[21][19] = ItemsInWindow[6];
	}
}
