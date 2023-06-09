#include "Utils.h"
#include <algorithm>
#include <stdlib.h>

//Generate a random nummber within lower and upper
int randomNumber(int lower, int upper)
{
	return(rand() % (upper - lower + 1)) + lower;
}

//Makes sure the number is between minimum and maximum
//if number is smaller as the minimum it gives minimumback
//if it is bigger then maximum gives max back
int limit(int minimum, int maximum, int number)
{
	return std::min(std::max(number, minimum), maximum);
}