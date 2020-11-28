#include "hashmap.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
static int compare_ints_udata(const void *a, const void *b, void *udata) {
    return *(int*)a - *(int*)b;
}

static uint64_t hash_int(const void *item, uint64_t seed0, uint64_t seed1) {
    return hashmap_murmur(item, sizeof(int), seed0, seed1);
}

static bool iter_ints(const void *item, void *udata) {
    int *vals = *(int**)udata;
    vals[*(int*)item] = 1;
    return true;
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
	struct hashmap *map;
	int seed = time(NULL);
	map = hashmap_new(sizeof(int), 0, seed, seed,
                               hash_int, compare_ints_udata, NULL);
	
	for(int i = 0 ; i < 4; i++)
	{
		if(data[i] % 4 == 0)
		{
			hashmap_oom(map);
		}
		else if(data[i] % 4== 1)
		{
		
			hashmap_get(map,(int*)&data[i]);
		}
		else if(data[i] % 4 == 2)
		{
			hashmap_set(map,(int*)&data[i]);
		}
		else if(data[i] % 4 == 3)
		{
			hashmap_scan(map,iter_ints,(int*)data);
		}
		else
		{
			 struct hashmap *tmp;
			 tmp = hashmap_new(sizeof(int), 0, seed, seed,
                               hash_int, compare_ints_udata, NULL);
			hashmap_free(tmp);

		}
	}
	hashmap_free(map);
	return 0;
}
