CFLAGS += -Wall
CFLAGS += -O3
CFLAGS += -std=c99

LINKDEPS += -lwiringPi

SONIC_OBJ = hcsr04.o sonic.o

.PHONY: all
all: sonic

.PHONY: clean
clean:
	rm -f sonic
	rm -f *.o

sonic: $(SONIC_OBJ)
	$(CC) $(CFLAGS) $(SONIC_OBJ) $(LINKDEPS) -o sonic

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

