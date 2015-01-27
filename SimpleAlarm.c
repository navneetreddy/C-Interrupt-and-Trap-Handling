/* 
 * Written by Zhouyang Michael Ye & Navneet Reddy
 * Section 2
 * November 4, 2014
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

/*
 * Prints the current time to the console.
 *
 * Parameters:
 * signal: int equvalent of the SIGALRM interrupt.
 */
void printTime(int signal)
{	
	//Gets the current time
	time_t currentTime;
	time(&currentTime);

	//Checks to see if the function was called correctly
	if(signal != SIGALRM)
	{
		fprintf(stderr, "Wrong signal received --- quitting");
		exit(1);
	}

	//Attempts to format the time as a string and print it
	char *time = ctime(&currentTime);
	if(time == NULL)
	{
		fprintf(stderr, "error obtaining current time --- quitting");
		exit(1);
	}
	else
	{
		fprintf(stdout, "\nCurrent time is %s", time);
		alarm(1);
	}
}

/*
 * Main method that runs an infinte loop, repeatedly printing the current time every second.
 *
 * Parameters:
 * argc: the number of arguments passed in the command line.
 * *argv: pointer to the char aray containing the specified file names.
 */
int main(int argc, char *argv[])
{
	//Randomly generated number
	int step;
	//Iterator that counts up to the randomly generated number
	int i;
	//Struct of the sigaction
	struct sigaction catchAlarm;

	//Check if the correct number of arguments are given
	if (argc != 1) 
	{
		fprintf(stderr, "usage: simplealarm\n");
		exit(1);
	}

	//Setup the function to call when catchAlarm encounters an interrupt
	catchAlarm.sa_handler = &printTime;
	//Handle a SIGALRM interrupt, exiting if failed
	if(sigaction(SIGALRM, &catchAlarm, NULL) < 0)
	{
		fprintf(stderr, "Error handling SIGALRM --- quitting");
	}

	//Use the current time as a seed for the randomly generated number
	srandom(time(NULL));

	//Setup the alarm interrupt to every second, exiting if failed
	if(alarm(1) != 0)
	{
		fprintf(stderr, "error setting alarm --- quitting");
		exit(1);
	}
	
	//Infinite loop to print a random number of periods between each time output
	while(1)
	{
		//Obtain a random number
		step = (random() % 10) * 10000000;
		
		//Count up to the random number
		for(i = 0; i < step; i++) {}
		
		fprintf(stdout, ".");
		fflush(stdout);
	}
	
}
