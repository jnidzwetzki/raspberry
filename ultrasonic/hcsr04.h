#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <wiringPi.h>

#define HCSR04_MAX_DISTANCE 400

typedef struct 
{
	int trigger_pin;
	int echo_pin;
} hcsr04_context;

hcsr04_context* hcsr04_create_context(int, int);
void hcsr04_destroy_context(hcsr04_context*);

bool hcsr04_init(hcsr04_context*);
bool hcsr04_reset(hcsr04_context*);

double hcsr04_run(hcsr04_context*);


