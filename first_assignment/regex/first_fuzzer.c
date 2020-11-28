#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
	re_compile((char*)data);
	return 0;
}
