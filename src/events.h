/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifndef PSXF_GUARD_EVENTS_H
#define PSXF_GUARD_EVENTS_H

#include "stage.h"

//EVENTS
#define EVENTS_FLAG_VARIANT 0xFFFC

#define EVENTS_FLAG_SPEED     (1 << 2) //Change Scroll Speed
#define EVENTS_FLAG_BLAMMED   (1 << 3) //Blammed Light
#define EVENTS_FLAG_GF        (1 << 4) //Set GF Speed

#define EVENTS_FLAG_PLAYED    (1 << 15) //Event has been already played

//Psych Engine Events Reader By IgorSou3000
typedef struct
{
  //Scroll Speed!!
  struct
  {
    fixed_t ogspd;
    fixed_t value1, value2;
  }speed;

  //BLAMMED LIGHTS

/*color: 0 = Turn off, 1 = Blue, 2 = Green,
3 = Pink, 4 = Red, 5 = Orange, anything else = Random;
*/
  struct
  {
    u8 last_value;
    u8 value;
    fixed_t r, g, b;
    fixed_t blackfade;
  }blammed;

}Events;

void Events_ScrollSpeed(void);

void Events_Tick(void);
void Events_StartEvents(void);
void Events_Load(void);

void Events_FG(void);
void Events_BG(void);

extern Events events;

#endif
