#include <stdio.h>
#include <stdlib.h>

#include <stdint.h>
#include <stdbool.h>

#include <bcm2835.h>

#include "tm1638.h"

int main(int argc, char *argv[])
{
  tm1638 t;

  if (!bcm2835_init())
    {
      printf("Unable to initialize BCM library\n");
      return -1;
    }

  tm1638_init(&t, RPI_GPIO_P1_11, RPI_GPIO_P1_13, RPI_GPIO_P1_15);

  tm1638_set_7seg_text(&t, "Buttons!");
  
  while(1)
    {
      uint8_t  x = tm1638_read_8buttons(&t);
      tm1638_set_8leds(&t, 0, x);
      
      //for(int i = 0, j = 128; i < 8; i++, j >>= 1)
      //tm1638_set_led(&t, i, (x & j) ? 2 : 0);

      delay(10);
    }

  return 0;
}
