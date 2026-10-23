#include "editor.h"
#include <stdio.h>
#include <string.h>

int createDuplicateFile(const char *srcfile, const char *tempfile)
{
    FILE *src = fopen(srcfile, "rb");
    if (!src)
    {
        printf("Invalid File Name: %s\n", srcfile);
        return 0;
    }

    FILE *temp = fopen(tempfile, "wb");
    if (!temp)
    {
        printf("Error: Cannot create tempfile: %s\n", tempfile);
        fclose(src);
        return 0;
    }

    char buffer[1024];
    size_t bytes;

    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0)
    {
        if (fwrite(buffer, 1, bytes, temp) != bytes)
        {
            fclose(src);
            fclose(temp);
            return 0;
        }
    }

    fclose(src);
    fclose(temp);
    return 1;
}

int WriteUpdatedTag(const char *tempfile, id3v *tag)
{
    FILE *fp = fopen(tempfile, "rb+");
    if (!fp)
    {
        printf("Error: cannot open the file: %s\n", tempfile);
        return 0;
    }

    memcpy(tag->tag, "TAG", 3);

    if (fseek(fp, -128, SEEK_END) != 0)
    {
        printf("Error: Cannot seek to tag position.\n");
        fclose(fp);
        return 0;
    }

    if (fwrite(tag, 1, sizeof(id3v), fp) != sizeof(id3v))
    {
        printf("Error: Failed to write tag data.\n");
        fclose(fp);
        return 0;
    }

    fclose(fp);
    return 1;
}

int replaceOrignalFile(const char *originalFile, const char *tempFile)
{
    if (remove(originalFile) != 0)
    {
        printf("Error: Cannot remove original file: %s\n", originalFile);
        return 0;
    }

    if (rename(tempFile, originalFile) != 0)
    {
        printf("Error: Cannot rename temp file to original.\n");
        return 0;
    }

    return 1;
}
