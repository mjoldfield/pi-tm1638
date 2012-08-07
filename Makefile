CC              = gcc
CC_FLAGS        = -std=c99 -pedantic -Wall -O9

TEST_TARGETS	= test.o  tm1638.o
KEYS_TARGETS	= keys.o  tm1638.o
CLOCK_TARGETS	= clock.o tm1638.o

%.o:	%.c
	$(CC) $(CC_FLAGS) -c $<

all:    test tm_clock keys

test:   $(TEST_TARGETS)
	gcc -O9 $(TEST_TARGETS) -lbcm2835 -o test

tm_clock:   $(CLOCK_TARGETS)
	gcc -O9 $(CLOCK_TARGETS) -lbcm2835 -o tm_clock

keys:	$(KEYS_TARGETS)
	gcc -O9 $(KEYS_TARGETS) -lbcm2835 -o keys

clean:
	rm -f *.o test tm_clock keys *~

.PHONY:	all clean
