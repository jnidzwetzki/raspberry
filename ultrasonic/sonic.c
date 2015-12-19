#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/ioctl.h>

#include "hcsr04.h"

// Wiring - change to real values
#define TRIGGER 	0
#define ECHO 		1

// Delay between two measurements
#define DELAY		50

#define LINES		2	

static int chars;

// Prototypes
double update_ema(double, double, float);
void init_terminal();
void update_terminal(double, double);

int main(int argc, char** argv)
{
	double ema = -1;
	
	hcsr04_context* sonic1_context = hcsr04_create_context(TRIGGER, ECHO);

	if(sonic1_context == NULL) 
	{
		fprintf(stderr, "Unable to create hcsr04 context\n");
		exit(EXIT_FAILURE);
	}

	hcsr04_init(sonic1_context);
	init_terminal();

	while (true)
	{
		double distance = hcsr04_run(sonic1_context);
		
		if(distance > 0)
		{
			ema = update_ema(ema, distance, 0.1);
			update_terminal(distance, ema);
		}

		delay(DELAY);
	}

	hcsr04_reset(sonic1_context);
	hcsr04_destroy_context(sonic1_context);

	return EXIT_SUCCESS;
}

void init_terminal()
{
	setvbuf(stdout, NULL, _IONBF, 1);

	for(int i = 0; i < LINES; i++) {
		printf("\n");
	}

	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	chars = w.ws_col;
}

void update_terminal(double distance, double ema)
{
	for(int i = 0; i < LINES; i++) {
	       	printf("\033[1A\033[2K");
	}
			
	printf("\rdistance: %.3lf, ema: %.3lf\n\n", distance, ema);

	double frac = ema / 400.0;
	int fill = (chars - 5) * frac;

	printf("[");
	for(int i = 0; i < fill; i++)
	{
		printf("#");
	}

	for(int i = 0; i < (chars - 5 - fill); i++)
	{
		printf(" ");
	}
	printf("]");
	fflush(stdout);
}

double update_ema(double old_value, double new_value, float alpha)
{
	if(old_value == -1) {
		return new_value;
	} else {
		double new_value_part = alpha * new_value;
		double old_value_part = (1.0 - alpha) * old_value;
		return new_value_part + old_value_part;
	}
}
