/*Atomulator v1.0 by Tom Walker
   6847 video emulation*/

#include <stdio.h>
#include <allegro.h>
#include <allegro_primitives.h>  // for drawing rectangles
#include <allegro5/allegro_font.h>

extern char* getPath();

#include "atom.h"

int fullscreen = 0;
int winsizex = 512, winsizey = 384;

uint8_t fontdata[] =
{
	0x00, 0x00, 0x00, 0x1c, 0x22, 0x02, 0x1a, 0x2a, 0x2a, 0x1c, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x08, 0x14, 0x22, 0x22, 0x3e, 0x22, 0x22, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x3c, 0x12, 0x12, 0x1c, 0x12, 0x12, 0x3c, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1c, 0x22, 0x20, 0x20, 0x20, 0x22, 0x1c, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x3c, 0x12, 0x12, 0x12, 0x12, 0x12, 0x3c, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x3e, 0x20, 0x20, 0x3c, 0x20, 0x20, 0x3e, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x3e, 0x20, 0x20, 0x3c, 0x20, 0x20, 0x20, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1e, 0x20, 0x20, 0x26, 0x22, 0x22, 0x1e, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x22, 0x22, 0x22, 0x3e, 0x22, 0x22, 0x22, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1c, 0x08, 0x08, 0x08, 0x08, 0x08, 0x1c, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x02, 0x02, 0x02, 0x02, 0x22, 0x22, 0x1c, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x22, 0x24, 0x28, 0x30, 0x28, 0x24, 0x22, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x3e, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x22, 0x36, 0x2a, 0x2a, 0x22, 0x22, 0x22, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x22, 0x32, 0x2a, 0x26, 0x22, 0x22, 0x22, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x3e, 0x22, 0x22, 0x22, 0x22, 0x22, 0x3e, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x3c, 0x22, 0x22, 0x3c, 0x20, 0x20, 0x20, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1c, 0x22, 0x22, 0x22, 0x2a, 0x24, 0x1a, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x3c, 0x22, 0x22, 0x3c, 0x28, 0x24, 0x22, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1c, 0x22, 0x10, 0x08, 0x04, 0x22, 0x1c, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x3e, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x1c, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x22, 0x22, 0x22, 0x14, 0x14, 0x08, 0x08, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x22, 0x22, 0x22, 0x2a, 0x2a, 0x36, 0x22, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x22, 0x22, 0x14, 0x08, 0x14, 0x22, 0x22, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x22, 0x22, 0x14, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x3e, 0x02, 0x04, 0x08, 0x10, 0x20, 0x3e, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x38, 0x20, 0x20, 0x20, 0x20, 0x20, 0x38, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x20, 0x20, 0x10, 0x08, 0x04, 0x02, 0x02, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x0e, 0x02, 0x02, 0x02, 0x02, 0x02, 0x0e, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x08, 0x1c, 0x2a, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x08, 0x10, 0x3e, 0x10, 0x08, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x08, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x14, 0x14, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x14, 0x14, 0x36, 0x00, 0x36, 0x14, 0x14, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x08, 0x1e, 0x20, 0x1c, 0x02, 0x3c, 0x08, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x32, 0x32, 0x04, 0x08, 0x10, 0x26, 0x26, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x10, 0x28, 0x28, 0x10, 0x2a, 0x24, 0x1a, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x08, 0x10, 0x20, 0x20, 0x20, 0x10, 0x08, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x08, 0x04, 0x02, 0x02, 0x02, 0x04, 0x08, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x08, 0x1c, 0x3e, 0x1c, 0x08, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x08, 0x08, 0x3e, 0x08, 0x08, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x10, 0x20, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x30, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x02, 0x02, 0x04, 0x08, 0x10, 0x20, 0x20, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x18, 0x24, 0x24, 0x24, 0x24, 0x24, 0x18, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x08, 0x18, 0x08, 0x08, 0x08, 0x08, 0x1c, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1c, 0x22, 0x02, 0x1c, 0x20, 0x20, 0x3e, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1c, 0x22, 0x02, 0x0c, 0x02, 0x22, 0x1c, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x04, 0x0c, 0x14, 0x3e, 0x04, 0x04, 0x04, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x3e, 0x20, 0x3c, 0x02, 0x02, 0x22, 0x1c, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1c, 0x20, 0x20, 0x3c, 0x22, 0x22, 0x1c, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x3e, 0x02, 0x04, 0x08, 0x10, 0x20, 0x20, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1c, 0x22, 0x22, 0x1c, 0x22, 0x22, 0x1c, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x1c, 0x22, 0x22, 0x1e, 0x02, 0x02, 0x1c, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x08, 0x10, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x04, 0x08, 0x10, 0x20, 0x10, 0x08, 0x04, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x10, 0x08, 0x04, 0x02, 0x04, 0x08, 0x10, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x18, 0x24, 0x04, 0x08, 0x08, 0x00, 0x08, 0x00, 0x00,
};

int *textcol;
int *semigrcol;
int *grcol;
int black;

int textcols[2][4] = {
    {
        0xff202020,
        0xffe0e0e0,
        0xff202020,
        0xffe0e0e0,
    },
    {
        0xff000000,
        0xff00ff00,
        0xff000000,
        0xff007fff
    }
};


int semigrcols[2][8] = {
    {
        0xffe0e0e0,
        0xffffffff,
        0xff808080,
        0xff808080,
        0xffffffff,
        0xffe0e0e0,
        0xffe0e0e0,
        0xffe0e0e0,
    },
    {
        0xff00ff00,
        0xff00ffff,
        0xffff0000,
        0xff0000ff,
        0xffffffff,
        0xffffff00,
        0xffff00ff,
        0xff007fff
    }
};

int grcols[2][4] = {
    {
        0xff202020,
        0xffe0e0e0,
        0xff202020,
        0xffffffff
    },
    {
        0xff000000,
        0xff00ff00,
        0xff000000,
        0xffffffff
    }
};



int blacks[2] = {
    0xff202020,
    0xff000000
};


void updatepal()
{
    textcol = textcols[colourboard];
    semigrcol = semigrcols[colourboard];
    grcol = grcols[colourboard];
    black = blacks[colourboard];
}

ALLEGRO_BITMAP *b2;
ALLEGRO_STATE state;
ALLEGRO_LOCKED_REGION *lr;

#define ATOM_SCREEN_WIDTH 256.0
#define ATOM_SCREEN_HEIGHT 192.0

ALLEGRO_FONT *font;

void initvideo()
{
    b2 = al_create_bitmap(ATOM_SCREEN_WIDTH, ATOM_SCREEN_HEIGHT);
    
    al_init_font_addon();
    
    font = al_load_font(getPath("fixed_font.tga"), 0, 0);
    if (!font)
    {
        printf("failed to load font.\n");
        return;
    }

    updatepal();
    
    al_store_state(&state, ALLEGRO_STATE_TARGET_BITMAP);
    al_set_target_bitmap(b2);
    lr = al_lock_bitmap(b2, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_WRITEONLY);
}


uint8_t *ram;
int cy = 0, sy = 0;

int tapeon;
int frmcount;
int fskipcount = 0;

// For onscreen speed display
int totalframes = 0;
int old_totalframes = 0;
extern int totcyc; // from 6502.c
int old_totalcycles = 0;
double old_time = 0;
double new_time = 0;
char hudbuf[256];

char scrshotname[260];
int savescrshot = 0;

uint8_t fetcheddat[32];

void drawline(int line)
{
	int addr, chr, col;
    
	int x, xx;
	uint8_t temp;
    
	if (!line)
		vbl = cy = sy = 0;
  
	if (line < 192)
	{
        //printf(" In draw with gfxmode %d\n", gfxmode);
        
        unsigned int *ptr = (unsigned int *)(lr->data + lr->pitch * line);
        
        switch (gfxmode)
		{
		case 0: case 2: case 4: case 6:         /*Text mode*/
		case 8: case 10: case 12: case 14:
			addr = (cy << 5) + 0x8000;
                
			for (x = 0; x < 256; x += 8)
			{
				chr = fetcheddat[x >> 3];
				if (chr & 0x40)
				{
					temp = chr;
					chr <<= ((sy >> 2) << 1);
					chr = (chr >> 4) & 3;
					if (chr & 2)
						col = semigrcol[((temp >> 6) | (css << 1))];
					else
						col = black;
                    
                    *ptr++ = col;
                    *ptr++ = col;
                    *ptr++ = col;
                    *ptr++ = col;
                    
					if (chr & 1)
						col = semigrcol[((temp >> 6) | (css << 1))];
					else
						col = black;

                    *ptr++ = col;
                    *ptr++ = col;
                    *ptr++ = col;
                    *ptr++ = col;
				}
				else
				{
					chr = ((chr & 0x3F) * 12) + sy;
					if (fetcheddat[x >> 3] & 0x80)
					{
						for (xx = 0; xx < 8; xx++)
						{
	                        *ptr++ = textcol[(((fontdata[chr] >> (xx ^ 7)) & 1) ^ 1) | css];
						}
					}
					else
					{
						for (xx = 0; xx < 8; xx++)
						{
	                        *ptr++ = textcol[((fontdata[chr] >> (xx ^ 7)) & 1) | css];
						}
					}
				}
			}
			sy++;
			if (sy == 12)
			{
				sy = 0;
				cy++;
			}
			addr = (cy << 5) + 0x8000;
			for (x = 0; x < 32; x++)
				fetcheddat[x] = ram[addr++];
			break;
		
		/* Propper graphics modes */
		case 1:         /*64x64, 4 colours*/
			for (x = 0; x < 256; x += 16)
			{
				temp = fetcheddat[x >> 3];
				for (xx = 0; xx < 16; xx += 4)
				{
                    col = semigrcol[(temp >> 6) | (css << 1)];
                    *ptr++ = col;
                    *ptr++ = col;
                    *ptr++ = col;
                    *ptr++ = col;
					temp <<= 2;
				}
			}
			
			addr = (((line + 1) / 3) << 4) | 0x8000;
			for (x = 0; x < 32; x++)
				fetcheddat[x] = ram[addr + (x >> 1)];
			
			break;
			
		case 3:         /*128x64, 2 colours*/
			for (x = 0; x < 256; x += 16)
			{
				temp = fetcheddat[x >> 3];
				for (xx = 0; xx < 16; xx += 2)
				{
                    col = (temp & 0x80) ? grcol[css | 1] : grcol[css];
                    *ptr++ = col;
                    *ptr++ = col;
					temp <<= 1;
				}
			}
			
			addr = (((line + 1) / 3) << 4) | 0x8000;
			for (x = 0; x < 32; x++)
				fetcheddat[x] = ram[addr + (x >> 1)];
			
			break;

/* CHANGED FOR CORRECT CLEAR2a */

		case 5: /*128x64, 4 colours*/
			for (x = 0; x < 256; x += 8)
			{
				temp = fetcheddat[x >> 3];
                for (xx = 0; xx < 8; xx += 2)
                {
                    col = semigrcol[(temp >> 6) |(css << 1)];
                    *ptr++ = col;
                    *ptr++ = col;
					temp <<= 2;
				}
			}

			addr = (((line + 1) / 3) << 5) | 0x8000;
			for (x = 0; x < 32; x++)
			fetcheddat[x] = ram[addr + x];
			break;

/* END CHANGES */

		case 7:         /*128x96, 2 colours*/
			for (x = 0; x < 256; x += 16)
			{
				temp = fetcheddat[x >> 3];
                for (xx = 0; xx < 16; xx += 2)
				{
                    col = (temp & 0x80) ? grcol[css | 1] : grcol[css];;
                    *ptr++ = col;
                    *ptr++ = col;
					temp <<= 1;
				}
			}

			addr = (((line + 1) >> 1) << 4) | 0x8000;
			for (x = 0; x < 32; x++)
				fetcheddat[x] = ram[addr + (x >> 1)];

			break;

		case 9:         /*128x96, 4 colours*/
			for (x = 0; x < 256; x += 8)
			{
				temp = fetcheddat[x >> 3];
				for (xx = 0; xx < 8; xx += 2)
				{
                    col = semigrcol[(temp >> 6) | (css << 1)];
                    *ptr++ = col;
                    *ptr++ = col;
					temp <<= 2;
				}
			}

			addr = (((line + 1) >> 1) << 5) | 0x8000;

			for (x = 0; x < 32; x++)
				fetcheddat[x] = ram[addr + x];

			break;

		case 11:         /*128x192, 2 colours*/
			for (x = 0; x < 256; x += 16)
			{
				temp = fetcheddat[x >> 3];
				for (xx = 0; xx < 16; xx += 2)
				{
                    col = (temp & 0x80) ? grcol[css | 1] : grcol[css];
                    *ptr++ = col;
                    *ptr++ = col;
					temp <<= 1;
				}
			}

			addr = ((line + 1) << 4) | 0x8000;
			for (x = 0; x < 32; x++)
				fetcheddat[x] = ram[addr + (x >> 1)];

			break;

		case 13:         /*128x192, 4 colours*/
			for (x = 0; x < 256; x += 8)
			{
				temp = fetcheddat[x >> 3];
                for (xx = 0; xx < 8; xx += 2)
				{
                    col = semigrcol[(temp >> 6) | (css << 1)];
                    *ptr++ = col;
                    *ptr++ = col;
					temp <<= 2;
				}
			}

			addr = ((line + 1) << 5) | 0x8000;

			for (x = 0; x < 32; x++)
				fetcheddat[x] = ram[addr + x];

			break;

		case 15:         /*256x192, 2 colours*/
			for (x = 0; x < 256; x += 8)
			{
				temp = fetcheddat[x >> 3];
				for (xx = 0; xx < 8; xx++)
				{
				    *ptr++ = (temp & 0x80) ? grcol[css | 1] : grcol[css];
					temp <<= 1;
				}
			}

			addr = ((line + 1) << 5) | 0x8000;
/*rpclog("addr=%04X\n",addr);*/
			for (x = 0; x < 32; x++)
				fetcheddat[x] = ram[addr + x];

			break;

//                        default:
//                        printf("Bad GFX mode %i\n",gfxmode);
//                        dumpregs();
//                        dumpram();
//                        exit(-1);
		}
	}
    
    
	if (line == 192)
	{
		startblit();
		frmcount++;
		fskipcount++;

		if (savescrshot)
		{
            al_unlock_bitmap(b2);
            al_restore_state(&state);

            savescrshot = 0;
			al_save_bitmap(scrshotname, b2);
            
            al_store_state(&state, ALLEGRO_STATE_TARGET_BITMAP);
            al_set_target_bitmap(b2);
            lr = al_lock_bitmap(b2, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_WRITEONLY);
        }

		if ((!(tapeon && fasttape) && fskipcount >= fskipmax) || frmcount == 60)
		{
            al_unlock_bitmap(b2);
            al_restore_state(&state);

			fskipcount = 0;
            
			if (tapeon)
            {
				al_draw_filled_rectangle(ATOM_SCREEN_WIDTH - 12, 0, ATOM_SCREEN_WIDTH, 4, al_map_rgb(255, 0, 0));
            }
            
            totalframes++;
            new_time = al_get_time();
            
            if (showspeed && ((new_time-old_time)>1.0))
            {
                sprintf(hudbuf,"MHz %2.2f FPS %3.1f", (totcyc-old_totalcycles)/((new_time - old_time)*1000000), (totalframes-old_totalframes)/(new_time - old_time));

                old_time = new_time;
                old_totalframes = totalframes;
                old_totalcycles = totcyc;
            }
                
            // draw a pattern on the screen and scale to max
            al_draw_scaled_bitmap(b2, 0, 0, ATOM_SCREEN_WIDTH, ATOM_SCREEN_HEIGHT, 0, 0, winsizex, winsizey, 0);

            if (showspeed) al_draw_text(font, al_map_rgb(255, 255, 255), 0.0, 0.0, 0, hudbuf);

            al_flip_display();
			frmcount = 0;
            
            al_store_state(&state, ALLEGRO_STATE_TARGET_BITMAP);
            al_set_target_bitmap(b2);
            lr = al_lock_bitmap(b2, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_WRITEONLY);
		}
		endblit();
	}

	if (line == 200)
		vbl = 1;

	if (line == 261)
		vbl = 0;

	if ((line == 261 && !colourboard) || line == 311)
	{
		switch (gfxmode)
		{

/* CHANGED FOR CORRECT CLEAR2a */

		case 0: case 2: case 4: case 6:         /*Text mode*/
		case 8: case 10: case 12: case 14:
		case 5: case 9: case 13: case 15:
			for (x = 0; x < 32; x++)
				fetcheddat[x] = ram[0x8000 + x];
			break;
/* END CHANGES */

		case 1: case 3: case 7: case 11:         /*16-byte per line*/
			for (x = 0; x < 32; x++)
				fetcheddat[x] = ram[0x8000 + (x >> 1)];
			break;

		}
	}

//        sndbuffer[line]=(speaker)?255:0;
}

/*void mixaudio(uint8_t *p)
   {
        memcpy(p,sndbuffer,262);
   }*/

void enterfullscreen()
{
/*	if (opengl)
        {
                rpclog("Enter fullscreen start\n");
                openglreinit();
                rpclog("Enter fullscreen end\n");
                return;
        }*/
    
    //HACK
//	#ifdef WIN32
//	destroy_bitmap(b2);
//	#endif
//
//	set_color_depth(depth);
//	set_gfx_mode(GFX_AUTODETECT_FULLSCREEN, 1024, 768, 0, 0);
//
//	#ifdef WIN32
//	b2 = create_video_bitmap(256, 192);
//	#endif
//
//	set_color_depth(8);
//	updatepal();
//
}

void leavefullscreen()
{
/*	if (opengl)
        {
                openglreinit();
                return;
        }*/

//HACK
//#ifdef WIN32
//	destroy_bitmap(b2);
//	#endif
//
//	set_color_depth(depth);
//
//#ifdef WIN32
//	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 2048, 2048, 0, 0);
//#else
//	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 512, 384, 0, 0);
//#endif
//
//	#ifdef WIN32
//	b2 = create_video_bitmap(256, 192);
//	#endif
//
//	set_color_depth(8);
//	updatepal();
//
//	updatewindowsize(512, 384);
}


