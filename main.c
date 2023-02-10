#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "main.h"

const char* header = "Range, Readings";
char outputLine[20];

void DetectRange(int inputVals[], const uint32_t inputSize)
{
	int i = 0;
	uint32_t min;
	int max = -2;
	uint32_t rangeReadings = 0;
	uint32_t readingsAccu = 0;

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

uint32_t CountReadingsInRange(int inputVals[], const uint32_t inputSize, const uint32_t min, const int max)
{
	int i = 0;
	uint32_t count = 0;

	for (i = 0; i < inputSize; i++)
	{
		if ((inputVals[i] >= min) && (inputVals[i] <= max))
		{
			count++;
		}
	}

	return count;
}

void FormatRangeLine(const uint32_t min, const int max, const uint32_t count)
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
	uint32_t simpleInputs[2] = {4, 5};
	uint32_t simpleInputSize = sizeof(simpleInputs)/sizeof(simpleInputs[0]);

	uint32_t testInputs[9] = {2,5,4,8,12,6,7,10,13};
	uint32_t testInputSize = sizeof(testInputs)/sizeof(testInputs[0]);

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