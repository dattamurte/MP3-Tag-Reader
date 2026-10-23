#include <stdio.h>
#include <string.h>
#include "reader.h"

int readTag(const char *filename, id3v *tag)
{
    FILE *fp = fopen(filename, "rb");
    if (!fp)
    {
        printf("File is not present\n");
        return 0;
    }

    if (fseek(fp, -128, SEEK_END) != 0)
    {
        printf("File too small or corrupted.\n");
        fclose(fp);
        return 0;
    }

    if (fread(tag, 1, sizeof(id3v), fp) != sizeof(id3v))
    {
        printf("Failed to read tag.\n");
        fclose(fp);
        return 0;
    }

    if (strncmp(tag->tag, "TAG", 3) != 0)
    {
        printf("🔈 ID3 TAG is not present 🎵\n");
        fclose(fp);
        return 0;
    }

    fclose(fp);
    return 1;
}

void displayID3v1(const id3v *tag)
{
    printf("\n========================================\n");
    printf("         MP3 TAG DETAILS (ID3v1)        \n");
    printf("========================================\n");

    printf("Title   : %s\n", tag->title);
    printf("Artist  : %s\n", tag->artist);
    printf("Album   : %s\n", tag->album);
    printf("Year    : %.4s\n", tag->year);
    printf("Comment : %s\n", tag->comment);
    printf("Genre   : %d\n", tag->genre);

    printf("========================================\n");
    printf("Metadata extraction completed.\n\n");
}



