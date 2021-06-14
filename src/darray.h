#ifndef DARRAY_H
#define DARRAY_H

#define ArrayPush(array, value, type) \
    do { \
        (array) = (type*)ArrayHold((array), 1, sizeof(type)); \
        (array)[ArrayLength(array) - 1] = (value); \
    } while (0);  


void* ArrayHold(void* array, int count, int itemSize);
int ArrayLength(void* array);
void ArrayFree(void* array);

#endif 


