/**
 *
 * @file 
 * @brief   Hello World for TM1638 based displays
 * @author  Martin Oldfield <ex-tm1638@mjo.tc>
 * @version 0.1
 *
 * @section DESCRIPTION
 *
 * A simple "Hello World" example program for the TM1638.
 *
 * @section HARDWARE
 *
 * The code hard wires pin connections:
 *
 *    * data: GPIO 17
 *    * clock: GPIO 21
 *    * strobe: GPIO 22
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * http://www.gnu.org/copyleft/gpl.html
 *
 */

/** @cond NEVER */

#include <stdio.h>
#include <stdlib.h>

#include <stdint.h>
#include <stdbool.h>

#include <bcm2835.h>
#include <tm1638.h>

int main(int argc, char *argv[])
{
  tm1638_p t;

  if (!bcm2835_init())
    {
      printf("Unable to initialize BCM library\n");
      return -1;
    }

  t = tm1638_alloc(17, 21, 22);
  if (!t)
    {
      printf("Unable to allocate TM1638\n");
      return -2;
    }

  tm1638_set_7seg_text(t, "Hello!", 0xc0);
  delay(2500);
  
  for(int k = 0; k < 4; k++)
    {
      tm1638_send_cls(t);

      for(int i = 0; i < 8; i++)
	{
	  for(int j = 7; j >= 0; j--)
	    {
	      tm1638_set_intensity(t, j);
	      delay(50);
	    }

	  tm1638_set_7seg_raw(t, i, (1 << i));
	  
	  for(int j = 0; j < 8; j++)
	    {
	      tm1638_set_intensity(t, j);
	      delay(50);
	    }

	  tm1638_set_led(t, i, i);
	  delay(50);
	}
    }

  tm1638_free(&t);

  return 0;
}

/** @endcond */
