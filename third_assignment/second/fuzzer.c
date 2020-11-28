#include "hashmap.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define KEY_MAX_LENGTH (256)
#define KEY_PREFIX ("somekey")
#define KEY_COUNT (1024*1024)


typedef struct data_struct_s
{
    char key_string[KEY_MAX_LENGTH];
    int number;
} data_struct_t;

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
        int index;
        data_struct_t* value;
        int error;
        map_t mymap = hashmap_new();
        char key_string[KEY_MAX_LENGTH];
        if(mymap == NULL)
        {
                return 0;
        }
        for(int i = 0 ; i < 1;i++)
        {
                if(data[i] % 1 == 0)
                {
                        value = malloc(sizeof(data_struct_t));
                        snprintf(value->key_string, KEY_MAX_LENGTH, "%s%d", KEY_PREFIX, index);
                        value->number = index;
                        value = malloc(sizeof(data_struct_t));
                        hashmap_put(mymap,value->key_string,data);
                }
                else
                {
                        snprintf(key_string, KEY_MAX_LENGTH, "%s%d", KEY_PREFIX, index);
                        error = hashmap_get(mymap, key_string, (void**)(&data[i]));
                }

        }
        hashmap_remove(mymap, key_string);
        hashmap_free(mymap);
        return 0;
}

