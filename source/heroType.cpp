#include "heroType.h"

heroType::heroType()
{

}

heroType::heroType(int tempX, int tempY)
{
	x = tempX;
	y = tempY;
	state = W_UP;
	anim_frame=0;
	frameDelay=5;
}

//---------------------------------------------------------------------
// Initializing hero requires little work, allocate room for one frame
// and set the frame gfx pointer
//---------------------------------------------------------------------
void heroType::init(heroType *sprite, u8* gfx)
{
	sprite->sprite_gfx_mem = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);

	sprite->frame_gfx = gfx;
	animate();
}
void heroType::init(int tempX, int tempY,heroType *sprite, u8* gfx)
{
		x = tempX;
	y = tempY;
	state = W_UP;
	anim_frame=0;
	frameDelay=5;
	sprite->sprite_gfx_mem = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);

	sprite->frame_gfx = gfx;
	animate();
}

//---------------------------------------------------------------------
// Animating hero requires us to copy in a new frame of data each time
//---------------------------------------------------------------------
void heroType::animate()
{
	if(frameDelay>2)
	{
	int frame = anim_frame + state * FRAMES_PER_ANIMATION;

	u8* offset = frame_gfx + frame * 32*32;

	dmaCopy(offset, sprite_gfx_mem, 32*32);
	frameDelay=0;
	}
	else
	{
		frameDelay++;
	}
	oamSet(&oamMain, 0, x, y, 0, 1, SpriteSize_32x32, SpriteColorFormat_256Color, 
		sprite_gfx_mem, -1, false, false, false, false, true);

}

int heroType::getX()
{
	return x;
}
int heroType::getY()
{
	return y;
}
int heroType::getFrame()
{
	return anim_frame;
}
void heroType::addFrame()
{
	anim_frame++;
}
void heroType::setFrame(int set)
{
	anim_frame = set;
}
void heroType::moveHero(int direction)
{
	switch(direction)
	{
	case 0:
		y++;
		break;
	case 1:
		x--;
		break;
	case 2:
		y--;
		break;
	case 3:
		x++;
		break;

	}
}

void heroType::setState(int set)
{
	state = set;
}
u16* heroType::getGfx()
{
	return sprite_gfx_mem;
}
