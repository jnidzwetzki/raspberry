CFLAGS += -Wall
CFLAGS += -O3
CFLAGS += -std=c99

LINKDEPS += -lwiringPi

SONIC_OBJ = shiftregister.o 

.PHONY: all
all: shiftregister

.PHONY: clean
clean:
	rm -f shiftregister
	rm -f *.o

shiftregister: $(SONIC_OBJ)
	$(CC) $(CFLAGS) $(SONIC_OBJ) $(LINKDEPS) -o shiftregister

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

