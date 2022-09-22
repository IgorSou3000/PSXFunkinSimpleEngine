/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "events.h"
#include "timer.h"

 Events events;

 //blammed colors
 static u32 colors[] = 
  {
   0xFF000000, //nothing
   0xFF31A2FD, //blue
   0xFF31FD8C, //green
   0xFFF794F7, //pink
   0xFFF96D63, //red
   0xFFFBA633  //orange
	};

void Events_Tick(void)
{
	//Scroll Speed!
	stage.speed += (FIXED_MUL(events.speed.ogspd, events.speed.value1) - stage.speed) / (((events.speed.value2 >> 6) + 1));

	//BLAMMED LIGHT
	//convert hex to rgb
	fixed_t ogr = (fixed_t)((colors[events.blammed.value] >> 16) & 0xFF) << FIXED_SHIFT;  // Extract the RR byte
	fixed_t ogg = (fixed_t)((colors[events.blammed.value] >> 8) & 0xFF) << FIXED_SHIFT;   // Extract the GG byte
	fixed_t ogb = (fixed_t)((colors[events.blammed.value]) & 0xFF) << FIXED_SHIFT;        // Extract the BB byte

	if (events.blammed.blackfade > FIXED_DEC(1,1))
	{
		//adding effect
		if (events.blammed.value != 0)
		{
			if (events.blammed.last_value != 0)
			{
			  events.blammed.r += (ogr - events.blammed.r);
			  events.blammed.g += (ogg - events.blammed.g);
			  events.blammed.b += (ogb - events.blammed.b);
			}
	  	else
	  	{
			  events.blammed.r += (ogr - events.blammed.r) / timer_dt >> 1;
			  events.blammed.g += (ogg - events.blammed.g) / timer_dt >> 1;
			  events.blammed.b += (ogb - events.blammed.b) / timer_dt >> 1;
			}
		}

		//removing effect
		else if (events.blammed.value == 0)
		{
		 events.blammed.r += (FIXED_DEC(255,1) - events.blammed.r) / timer_dt >> 1;
		 events.blammed.g += (FIXED_DEC(255,1) - events.blammed.g) / timer_dt >> 1;
		 events.blammed.b += (FIXED_DEC(255,1) - events.blammed.b) / timer_dt >> 1;
		}
	}

	//BLAMMED LIGHT 
	if (events.blammed.blackfade > 0 && events.blammed.blackfade <= FIXED_DEC(255,1))
	{
		//Draw black fade
		if (events.blammed.value != 0)
		 events.blammed.blackfade += FIXED_DEC(timer_dt >> 2,1);

		//back to normal
		else if (events.blammed.value == 0)
		 events.blammed.blackfade -= FIXED_DEC(timer_dt >> 2,1);

		//avoid bugs
		if (events.blammed.blackfade > FIXED_DEC(255,1))
			events.blammed.blackfade = FIXED_DEC(255,1);

		if (events.blammed.blackfade < FIXED_DEC(0,1))
			events.blammed.blackfade = FIXED_DEC(0,1);
	}
}

void Events_StartEvents(void)
{
	for (Event *event = stage.cur_event; event->pos != 0xFFFF; event++)
	{
		//Update event pointer
		if (event->pos > (stage.note_scroll >> FIXED_SHIFT))
			break;

		else
			stage.cur_event++;

		if (event->event & EVENTS_FLAG_PLAYED)
		continue;

			//Events
			switch(event->event & EVENTS_FLAG_VARIANT)
			{
				case EVENTS_FLAG_SPEED: //Scroll Speed!!
				{
					events.speed.value1 = (events.speed.value1 == 0) ? FIXED_UNIT : event->value1;
					events.speed.value2 = event->value2;
					break;
				}

				case EVENTS_FLAG_BLAMMED: //Blammed Light!!
				{
					events.blammed.last_value = events.blammed.value;
					events.blammed.value = (event->value1 >> FIXED_SHIFT);

					if (events.blammed.value != 0 && events.blammed.blackfade < FIXED_DEC(70,1))
					  events.blammed.blackfade = FIXED_DEC(1,1);
					break;
				}

				case EVENTS_FLAG_GF: //Set GF Speed!!
				{
					//sooo easy LOL
					if (event->value1 == 0)
						stage.gf_speed = 1 << 2;
					else
						stage.gf_speed = (event->value1 >> FIXED_SHIFT) << 2;
					break;
				}

				default: //nothing lol
					break;
			}

				event->event |= EVENTS_FLAG_PLAYED;
			}

	Events_Tick();
}

//Initialize some stuffs
void Events_Load(void)
{
	//Scroll Speed
	events.speed.ogspd = stage.speed;
	events.speed.value1 = FIXED_UNIT;
	events.speed.value2 = 0;

	//Blammed Light
	events.blammed.value = events.blammed.last_value = 0;
	events.blammed.blackfade = FIXED_DEC(1,1);
	events.blammed.r = FIXED_DEC(255,1);
	events.blammed.g = FIXED_DEC(255,1);
	events.blammed.b = FIXED_DEC(255,1);
}

void Events_FG(void)
{
	//BLAMMED LIGHT 
	if (events.blammed.blackfade > FIXED_DEC(1,1))
	{
		static const RECT flash = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
		Gfx_BlendRect(&flash, 255 - (events.blammed.r >> FIXED_SHIFT) + 1, 255 - (events.blammed.g >> FIXED_SHIFT) + 1, 255 - (events.blammed.b >> FIXED_SHIFT) + 1, 2);
	}
}

void Events_BG(void)
{
	//BLAMMED LIGHT 
	if (events.blammed.blackfade > 0 && events.blammed.blackfade <= FIXED_DEC(255,1))
	{
		static const RECT flash = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
		u8 flash_col =  events.blammed.blackfade >> FIXED_SHIFT;

		Gfx_BlendRect(&flash, flash_col, flash_col, flash_col, 2);
	}
}
