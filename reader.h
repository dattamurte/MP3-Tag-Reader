#ifndef READER_H
#define READER_H

#include <stdio.h>
#include "id3.h"

int readTag(const char *filename, id3v *tag);
void displayID3v1(const id3v *tag);

#endif
