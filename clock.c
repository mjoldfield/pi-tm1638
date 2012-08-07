#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

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

  while(1)
    {
      time_t now    = time(NULL);
      struct tm *tm = localtime(&now);

      char text[10];
      snprintf(text, 9, "%02d %02d %02d", tm->tm_hour, tm->tm_min, tm->tm_sec);

      tm1638_set_7seg_text(&t, text);
      delay(100);
    }

  return 0;
}
