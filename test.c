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

  printf("Hello World\n");

  tm1638_init(&t, RPI_GPIO_P1_11, RPI_GPIO_P1_13, RPI_GPIO_P1_15);

  printf("init done\n");

  tm1638_set_7seg_text(&t, "Hello !!");
  delay(2500);

  
  while(1)
    {
      tm1638_send_cls(&t);

      for(int i = 0; i < 8; i++)
	{
	  for(int j = 7; j >= 0; j--)
	    {
	      tm1638_set_intensity(&t, j);
	      delay(50);
	    }

	  tm1638_set_7seg_raw(&t, i, (1 << i));
	  
	  for(int j = 0; j < 8; j++)
	    {
	      tm1638_set_intensity(&t, j);
	      delay(50);
	    }

	  tm1638_set_led(&t, i, i);
	  delay(50);
	}
    }

  return 0;
}
