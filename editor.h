#ifndef EDITOR_H
#define EDITOR_H

#include <stdio.h>
#include "id3.h"

int createDuplicateFile(const char *srcfile, const char *tempfile);
int WriteUpdatedTag(const char *tempfile, id3v *tag);
int replaceOrignalFile(const char *originalFile, const char *tempFile);

#endif
