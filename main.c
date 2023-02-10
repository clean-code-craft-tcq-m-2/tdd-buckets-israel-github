#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "main.h"

 char* header = "Range, Readings";
char outputLine[20];

void DetectRange(int inputVals[],  int inputSize)
{
	int i = 0;
	int min;
	int max = -2;
	int rangeReadings = 0;
	int readingsAccu = 0;

	// [2,5,4,8,12,6,7,10,13]
	// [2,4,5,6,7,8,10,12,13]

	while(readingsAccu < inputSize)
	{
		// Find minimum value of range
		min = max + 2; // theoretical minimum

		for (i = 0; i < inputSize; i++)
		{
			if (inputVals[i] == min)
			{
				break; // theoretical value found
			}

			if (i == (inputSize - 1))
			{
				min++;
				i = -1; // Restart loop with new min value
			}
		}

		max = min;

		// Find next values in range
		for (i = 0; i < inputSize; i++)
		{
			if (inputVals[i] == (max + 1))
			{
				max++;
				i = -1; // Restart loop to find next in range
				continue;
			}
		}

		printf("\n");

		rangeReadings = CountReadingsInRange(inputVals, inputSize, min, max);

		// Range found
		FormatRangeLine(min, max, rangeReadings);
		printf("%s", outputLine);

		readingsAccu += rangeReadings;
	}
}

int CountReadingsInRange(int inputVals[],  int inputSize,  int min,  int max)
{
	int i = 0;
	int count = 0;

	for (i = 0; i < inputSize; i++)
	{
		if ((inputVals[i] >= min) && (inputVals[i] <= max))
		{
			count++;
		}
	}

	return count;
}

void FormatRangeLine( int min,  int max,  int count)
{
	if (min == max)
	{
		sprintf(outputLine, "%d, %d", min, count);
	}
	else
	{
		sprintf(outputLine, "%d-%d, %d", min, max, count);
	}
}

void PassTest(int inputVals[], int inputSize)
{
	sprintf(outputLine, "%d-%d, %d", inputVals[0], inputVals[1], inputSize);
	printf("%s", outputLine);
	printf("\n");
}

int main(void)
{
	int simpleInputs[2] = {4, 5};
	int simpleInputSize = sizeof(simpleInputs)/sizeof(simpleInputs[0]);

	int testInputs[9] = {2,5,4,8,12,6,7,10,13};
	int testInputSize = sizeof(testInputs)/sizeof(testInputs[0]);

	// PassTest(inputs, inputSize);
	// assert(strcmp(outputLine, "4-5, 2") == 0);

	printf("%s", header);
	DetectRange(simpleInputs, simpleInputSize);
	assert(strcmp(outputLine, "4-5, 2") == 0);

	DetectRange(testInputs, testInputSize);

	assert(CountReadingsInRange(testInputs, testInputSize, 2, 2) == 1);
	assert(CountReadingsInRange(testInputs, testInputSize, 4, 8) == 5);
	assert(CountReadingsInRange(testInputs, testInputSize, 10, 10) == 1);
	assert(CountReadingsInRange(testInputs, testInputSize, 12, 13) == 2);

	return 0;
}