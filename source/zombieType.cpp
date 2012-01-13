#include "zombieType.h"


zombieType::zombieType()
{
	startRandom();
	init();
	state = W_UP;
	anim_frame=0;
	frameDelay=0;
	health = 1;
}

void zombieType::startRandom()
{
	int startLoc;
	srand(getTime());
	startLoc = rand()%4;
	
	srand(time(NULL));
	switch(startLoc)
	{
		//left
	case 0:
		x = -36;
		y = rand()%320;
		break;
	//right
	case 1:
		x = 768;
		y = rand()%320;
		break;
	//up
	case 2:
		x = rand()%768;
		y = 0;
		break;
		//down
	case 3:
		x = rand()%768;
		y = 320;
		break;
	}
}

int zombieType::getTime()
{
	
	time_t unixTime = time(NULL);
	
	struct tm* timeStruct = gmtime((const time_t *)&unixTime);
	int hours, minutes, seconds, day, month, year;
	hours = timeStruct->tm_hour;
	minutes = timeStruct->tm_min;
	seconds = timeStruct->tm_sec;
	day = timeStruct->tm_mday;
	month = timeStruct->tm_mon;
	year = timeStruct->tm_year +1900;
	return hours*10000+minutes*100+seconds;
}
//---------------------------------------------------------------------
// Initializing hero requires little work, allocate room for one frame
// and set the frame gfx pointer
//---------------------------------------------------------------------
void zombieType::init()
{
	sprite_gfx_mem = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);

	frame_gfx = (u8*)zombieTiles-32*32; //needs to shift left one frame...dunno why
}

//---------------------------------------------------------------------
// Animating hero requires us to copy in a new frame of data each time
//---------------------------------------------------------------------
void zombieType::animate()
{
	if (frameDelay >3)
	{
	int frame = anim_frame + state * FRAMES_PER_ANIMATION_Z;

	u8* offset = frame_gfx + frame * 32*32;

	if(getFrame() >= FRAMES_PER_ANIMATION_Z) anim_frame = 0;
	
	dmaCopy(offset, sprite_gfx_mem, 32*32);
	frameDelay=0;
	addFrame();
	}
	else
	{
		frameDelay++;
	}
	
}

void zombieType::render(int i,camera &cam)
{
		animate();
	oamSet(&oamMain, i+10, x-cam.getX(), y-cam.getY(), 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, 
						sprite_gfx_mem, -1, false, offScreen(cam), false, false, false);
}
void zombieType::render(int i,camera &cam,bool unrender)
{
	animate();
	oamSet(&oamMain, i+10, x-cam.getX(), y-cam.getY(), 0, 0, SpriteSize_32x32, SpriteColorFormat_256Color, 
						sprite_gfx_mem, -1, false, unrender, false, false, false);
}
int zombieType::getX()
{
	return x;
}
int zombieType::getY()
{
	return y;
}
int zombieType::getFrame()
{
	return anim_frame;
}
void zombieType::addFrame()
{
	anim_frame++;
}
void zombieType::setFrame(int set)
{
	anim_frame = set;
}
void zombieType::move(int xDir, int yDir)
{
	if(xDir > x)
	{
		x++;
		setState(Z_RIGHT);
	}
	else if(xDir < x)
	{
		x--;
		setState(Z_LEFT);
	}
	if(yDir > y)
	{
		y++;
		setState(Z_DOWN);
	}
	else if(yDir < y)
	{
		y--;
		setState(Z_UP);
	}
}

void zombieType::setState(int set)
{
	state = set;
}
u16* zombieType::getGfx()
{
	return sprite_gfx_mem;
}
bool zombieType::offScreen(camera &cam)
{
	return !(
		x > cam.getX()-36 
		&& x < cam.getX() + SCREEN_RIGHT+36 
		&& y > cam.getY()-36 
		&& y < cam.getY() + SCREEN_BOTTOM+36);
}