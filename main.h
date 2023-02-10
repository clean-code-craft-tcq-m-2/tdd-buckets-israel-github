
typedef unsigned int uint32_t;

void DetectRange(int inputVals[], const uint32_t inputSize);
void FormatRangeLine(const uint32_t min, const int max, const uint32_t count);
uint32_t CountReadingsInRange(int inputVals[], const uint32_t inputSize, const uint32_t min, const int max);