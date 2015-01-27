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

//Global counter for the number of operations completed
int divisionCounter = 0;

/*
 * Prints an error and exits the program if divided by zero.
 */
void divisionZero() 
{
	fprintf(stderr, "Error dividing by zero --- quiting\n");
	exit(1);
}

/*
 * Prints the number of operations completed and exits program.
 */
void exitProgram() 
{
	fprintf(stdout, "\n%d operations completed.\n", divisionCounter);
	exit(1);
}

/*
 * Main method that runs an infinte loop, repeatedly prompting the user for two integers and 
 * calculates the quotient of the two integers and prints the quotient and the remainder.
 *
 * Parameters:
 * argc: the number of arguments passed in the command line.
 * *argv: pointer to the char aray containing the specified file names.
 */
int main(int argc, char *argv[])
{
	//Stores the first integer from user
	int int1;
	//Stores the second integer from user
	int int2;
	//Stores the first integer from user as a string
	char intStr1[100];
	//Stores the second integer from user as a string
	char intStr2[100];
	//Struct of the sigaction
	struct sigaction catchDivide;

	//Check if the correct number of arguments are given
	if (argc != 1) 
	{
		fprintf(stderr, "usage: divide\n");
		exit(-1);
	}

	//Setup the function to call when catchDivide encounters a SIGFPE interrupt
	catchDivide.sa_handler = &divisionZero;
	//Handle a SIGFPE interrupt, exiting if failed
	if(sigaction(SIGFPE, &catchDivide, NULL) < 0)
	{
		fprintf(stderr, "Error handling SIGFPE --- quitting");
	}
	 
	//Setup the function to call when catchDivide encounters a SIGINT interrupt
	catchDivide.sa_handler = &exitProgram;
	//Handle a SIGINT interrupt, exiting if failed
	if(sigaction(SIGINT, &catchDivide, NULL) < 0)
	{
		fprintf(stderr, "Error handling SIGINT --- quitting");
	}

	//Infinite loop to get user input and print quotient
	while(1)
	{
		fprintf(stdout, "Enter first integer: ");
		
		//Get first integer from user
		if (fgets(intStr1,100,stdin) == NULL)
		{
			fprintf(stderr, "Error obtaining first integer.");
		}
		
		//Convert first integer from a string to an integer
		int1 = atoi(intStr1);

		fprintf(stdout, "Enter second integer: ");
		
		//Get second integer from user
		if (fgets(intStr2,100,stdin) == NULL)
		{
			fprintf(stderr, "Error obtaining second integer.");
		}

		//Convert second integer from a string to an integer
		int2 = atoi(intStr2);
		
		//Calculate and print out the quotient of the two integers and the remainder
		fprintf(stdout, "%d / %d is %d with a remainder of %d\n", int1, int2, int1/int2, int1%int2);
		divisionCounter++;
	}
	
}
