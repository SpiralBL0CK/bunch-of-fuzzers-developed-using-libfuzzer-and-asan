#include <stdio.h>
#include <stdint.h>
#include "json.h"
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
	json_value* value;
	value = json_parse((char*)data,(int)size);
	//process_value(value, 0);

        json_value_free(value);
	return 0;

}
