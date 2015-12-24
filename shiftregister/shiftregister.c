#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/ioctl.h>
#include <wiringPi.h>

// Wiring - change to real values
#define SRIN	 	0
#define SRCK		1
#define RCK 		2

int main(int argc, char** argv)
{

        // Start wiringPi API
        if (wiringPiSetup() == -1)
        {
                fprintf(stderr, "Error while init application\n");
                exit(EXIT_FAILURE);
        }

        // Init PINs
        pinMode(SRIN, OUTPUT);
        pinMode(SRCK, OUTPUT);
        pinMode(RCK, OUTPUT);

	for(int i = 0; i < 10000; i++)
	{
		printf("New run\n");
		digitalWrite(SRIN, (i % 6) == 0);
		
		digitalWrite(SRCK, 1);
		delay(10);
		digitalWrite(SRCK, 0);
		delay(10);
		digitalWrite(RCK, 1);
		delay(10);
		digitalWrite(RCK, 0);
		
		delay(250);
	}
	
	
	return EXIT_SUCCESS;
}

