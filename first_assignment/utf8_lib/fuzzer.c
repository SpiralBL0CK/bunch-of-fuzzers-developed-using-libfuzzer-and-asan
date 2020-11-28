#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "utf8.h"
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
	utf8dup((char*)data);
	return 0;
}
