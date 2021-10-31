#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <stdbool.h>
#include "parse.h"


bool Parse(char* str, int* value)
{
	int i = 0;
	char* arrayPart = strtok(str, ";");
	while (arrayPart != NULL)
	{
		*value = atoi(arrayPart);
        if(i == 1)
            if(*value < 0 || *value > 12)
                return false;
		value++;
		i++;
		arrayPart = strtok(NULL, " ;");
	}

	if (i != 6)
		return false;
	return true;
}