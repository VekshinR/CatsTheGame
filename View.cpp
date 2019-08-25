#include "View.h"
View view;
View getPlayerCoordinate(float x, float y)
{
	{
		float Tempx = x; float Tempy = y;
		if (x < 320) { Tempx = 320; }
		if (x < 240) { Tempx = 240; }
		if (x > 554) { Tempx = 554; }
		view.setCenter(Tempx + 100, Tempy);
		return view;
	}
}

View changeView()
{
	{
		if (Keyboard::isKeyPressed(Keyboard::U)) {
			view.zoom(1.001);
		}
		if (Keyboard::isKeyPressed(Keyboard::I)) {
			view.zoom(0.999);
		}
		if (Keyboard::isKeyPressed(Keyboard::O)) {
			view.rotate(1);
		}
		if (Keyboard::isKeyPressed(Keyboard::P)) {
			view.setViewport(FloatRect(0, 0, 0.5, 1));
		}
		return view;
	}
}
