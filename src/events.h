/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifndef PSXF_GUARD_EVENTS_H
#define PSXF_GUARD_EVENTS_H

#include "stage.h"

//Psych Engine Events Reader By IgorSou3000
typedef struct
{
  //Scroll Speed!!
  struct
  {
    fixed_t ogspd;
    u16 value1, value2;
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
