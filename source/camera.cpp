#include "camera.h"

camera::camera()
{

}

camera::camera(int startX, int startY, int background, int background2)
{
	x = startX;
	y = startY;
	bg = background;
	bg2 = background2;
}
void camera::init(int startX, int startY, int background, int background2)
{
	x = startX;
	y = startY;
	bg = background;
	bg2 = background2;
}
void camera::panLeft()
{
	if(0 !=x )
		x--;
}
void camera::panRight()
{
	//768 is the farthest to the right the cam is allowed to go
	if(768 !=x)
		x++;
}
void camera::panUp()
{
	if(0 !=y)
		y--;
}
void camera::panDown()
{
	if(320 !=y)
		y++;
}
void camera::update()
{
	bgSetScroll(bg, x, y);
	bgSetScroll(bg2, x-512, y);
	bgUpdate();
}
s16 camera::getX()
{
	return x;
}
s16 camera::getY()
{
	return y;
}