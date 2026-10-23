#ifndef ID3_H
#define ID3_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#pragma pack(push,1)
typedef struct
{
    char tag[3];
    char title[30];
    char artist[30];
    char album[30];
    char year[4];
    char comment[30];
    unsigned char genre;
} id3v;
#pragma pack(pop)

#endif
