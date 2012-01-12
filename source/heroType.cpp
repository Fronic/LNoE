#include "heroType.h"

heroType::heroType()
{
	maxHealth = 3;
	health = 3;
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

	for(int i=0;i<maxHealth;i++)
	{
		heart_gfx_mem.push_back(oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color));
		heart_frame_gfx.push_back((u8*)lifeTiles);
	}

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
	for(int i=0;i<maxHealth;i++)
	{
		heart_gfx_mem.push_back(oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color));
		heart_frame_gfx.push_back((u8*)lifeTiles);
	}
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
	oamSet(&oamMain, 30, x, y, 0, 1, SpriteSize_32x32, SpriteColorFormat_256Color, 
		sprite_gfx_mem, -1, false, false, false, false, true);
	displayHealth();
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

	void heroType::setLife(int set)
	{
		health = set;
	}
	void heroType::addLife(int)
	{

	}
	int heroType::getLife()
	{
		return health;
	}
	void heroType::displayHealth()
	{
		int frame = 0;
		int i;
		for(i = 0;i<health;i++)
		{
		u8* offset = heart_frame_gfx[i] + frame * 16*16;

	dmaCopy(offset, heart_gfx_mem[i], 32*32);
	oamSet(&oamMain, i, (i * 16) +(2*i)+4 , 4, 0, 2, SpriteSize_16x16, SpriteColorFormat_256Color, 
		heart_gfx_mem[i], -1, false, false, false, false, true);
		}
		if(health < maxHealth)
		{
			frame = 1;
			for(int j=0;j<(maxHealth-health);i++,j++)
		{
		u8* offset = heart_frame_gfx[i] + frame * 16*16;

	dmaCopy(offset, heart_gfx_mem[i], 32*32);
	oamSet(&oamMain, i, (i * 16) +(2*i)+4 , 4, 0, 2, SpriteSize_16x16, SpriteColorFormat_256Color, 
		heart_gfx_mem[i], -1, false, false, false, false, true);
		}
		}
	}