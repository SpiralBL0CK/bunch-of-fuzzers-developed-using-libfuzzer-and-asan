#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Expects a null-terminated string and returns an integer.
 */
int attack_me(char *buffer) {
    if (strlen(buffer) != 36) {
        return 0;
    }

    if (buffer[10] != 'A' && buffer[20] != 'B') {
        return 1;
    } 

    int cs = 0;
    for (int i = 0; i < 10; i++) {
        if (buffer[i] == 'C') {
            cs++;
        }
    }
    if (cs < 2) {
        return 2;
    }

    int idx = (int)buffer[25];
    if (buffer[idx] != 'D') {
        return -1;
    }
    return 3;
}
int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    attack_me((char*)data);
    return 0;
}