#include "hcsr04.h"

hcsr04_context* hcsr04_create_context(int trigger_pin, int echo_pin)
{
	hcsr04_context* context = malloc(sizeof(hcsr04_context));
	if(context == NULL)
	{
		return NULL;
	}

	memset(context, 0, sizeof(hcsr04_context));

	context -> trigger_pin = trigger_pin;
	context -> echo_pin = echo_pin;

	return context;
}

void hcsr04_destroy_context(hcsr04_context *context)
{
	if(context != NULL)
	{
		free(context);
		context = NULL;
	}
}


bool hcsr04_init(hcsr04_context *context)
{
	// Start wiringPi API
	if (wiringPiSetup() == -1)
	{
		fprintf(stderr, "Error while init application\n");
		exit(EXIT_FAILURE);
	}

	// Init PINs
	pinMode(context -> trigger_pin, OUTPUT);
	pinMode(context -> echo_pin, INPUT);

	return true;
}

bool hcsr04_reset(hcsr04_context *context)
{
	digitalWrite(context -> trigger_pin, 0);
	pinMode(context -> trigger_pin, INPUT);
	pinMode(context -> echo_pin, INPUT);

	return true;
}

double hcsr04_run(hcsr04_context *context) 
{
	int count = 0;
	struct timeval start;
	struct timeval end;
	
	// Trigger up for 10 micro sec 
	digitalWrite(context -> trigger_pin, 1);
	delayMicroseconds(10);
	digitalWrite(context -> trigger_pin, 0);

	while (!digitalRead(context -> echo_pin))
	{
		count++;
		if(count > 999999) {
			// Timeout
			return -1;
		}
	}
	
	gettimeofday(&start, NULL);

	while (digitalRead(context -> echo_pin));

	gettimeofday(&end, NULL);

	long dSec = end.tv_sec - start.tv_sec;
	long dUsec = end.tv_usec - start.tv_usec;
	long time_in_micros = 1000000 * dSec + dUsec;
	double distance = ((double)time_in_micros) * 34300.0 / 2.0 / 1000000.0;

	if(distance > 400) {
		// Out of range
		return -1;
	}

	return distance;
}
