#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <stdbool.h>
#include "parse.h"


struct stat
{
	int Max;
	int Min;
	int Number;
	int Yar;
	double Value;
};

int main(int argc, char** argv)
{

    char fileName[200] = "file.csv";
    char ret;
    FILE* f = fopen(fileName, "r");
	char str[50];
	int value[6];
	int max = 12;
	int min = 0;
    int error = 0;

	struct stat year = { 0, 0, 0, 0.0f };
	struct stat month[12];

	if (argc <= 1)
	{
		printf("syntax : \n\t%s\n\t-h help\n\t-f <File name>\n\t-m <Month number>\n", argv[0]);
		return 0;
	}
	else
	{
        while ((ret = getopt(argc, argv, "f:m:h")) != -1)
        {
		    switch (getopt(argc, argv, "f:m:h"))
            {
                case 'h':
                    printf("syntax : \n\t%s\n\t-h help\n\t-f <File name>\n\t-m <Month number>\n", argv[0]);
                    return 0;
                    break;
                case 'f':
                    sprintf(fileName, "%s", optarg);
                    break;
                case 'm':
                    sscanf(optarg, "%d", &min);
                    if(min > 0 && min < 13)
                    {
                        max = min;
                        min--;
                    }
                    else
                    {
                        min = 0;
                        max = 12;
                    }
                break;
            }
        }

	}

	for (int i = 0; i < 12; i++)
	{
		month[i].Max = 0;
		month[i].Min = 0;
		month[i].Number = 0;
		month[i].Value = 0.0f;
	}

	if (!f)
	{
		perror("Error open file.csv\n");
		return 1;
	}
	else
	{
		while ((fgets(str, 50, f)) != NULL)
		{
			if (Parse(str, value))
			{
				year.Number++;
				year.Value += (double)value[5];
				if (value[5] < year.Min) year.Min = value[5];
				if (value[5] > year.Max) year.Max = value[5];

				value[1]--;

				month[value[1]].Yar = value[0];
				month[value[1]].Number++;
				month[value[1]].Value+= value[5];
				if (value[5] < month[value[1]].Min) month[value[1]].Min = value[5];
				if (value[5] > month[value[1]].Max) month[value[1]].Max = value[5];
 			}
             else
             {
                 error++;
             }
		}
		fclose(f);

        if(error > 0)
        {
            printf("Error read: %d\n\n", error);
        }

		printf("Max Year: %d\n", year.Max);
		printf("Min Year: %d\n", year.Min);
		printf("Mean value: %f\n\n", year.Value/(double)year.Number);

		for (int i = min; i < max; i++)
		{
			printf("Max Year %d Month %d: %d\n", month[i].Yar, i+1, month[i].Max);
			printf("Min Year %d Month %d: %d\n", month[i].Yar, i+1, month[i].Min);
			printf("Mean Year %d Month %d: %f\n\n", month[i].Yar, i+1, month[i].Value / (double)month[i].Number);
		}
	}
	return 0;
}