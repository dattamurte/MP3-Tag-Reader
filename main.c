#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "reader.h"
#include "editor.h"
#include "id3.h"

int main(int argc, char *argv[])
{
    if(argc == 2 && (strcmp(argv[1], "-h")== 0 || strcmp(argv[1], "h")== 0))
    {

        printf("-----------------------------------------------\n");
        printf("        MP3 TAG EDITOR - HELP MENU\n");
        printf("-----------------------------------------------\n\n");

        printf("Usage:\n");
        printf("  %s <file.mp3>\n", argv[0]);
        printf("  %s -e <option> <value> <file>\n\n", argv[0]);

        printf("Edit Options:\n");
        printf("  -t   Edit Title\n");
        printf("  -a   Edit Artist\n");
        printf("  -A   Edit Album\n");
        printf("  -y   Edit Year (4 digits)\n");
        printf("  -c   Edit Comment\n");
        printf("  -g   Edit Genre (0–255)\n\n");

        printf("Interactive Mode:\n");
        printf("  %s -m   Start menu-based editing\n", argv[0]);

        printf("-----------------------------------------------\n");
        return 0;
    }


    if(argc == 2)
    {
         char const *filename = argv[1];
         id3v tag;

        if(readTag(filename, &tag))
        {
            displayID3v1(&tag);

        }
        else
        {
           printf("File is not able to open or no ID3v1 tag found\n");
        }

        return 0;
    }


    // EDIT MODE
    if (argc == 5 && strcmp(argv[1], "-e") == 0)
    {
        const char *editFlag = argv[2];
        const char *newValue = argv[3];
        const char *filename = argv[4];

        id3v tag;

        // Step 1: Read tag
        if (!readTag(filename, &tag))
        {
            printf("File is not able to open or no ID3v1 tag found\n");
            return 1;
        }

        // Step 2: Modify correct field
        if (strcmp(editFlag, "-t") == 0)
        {
            strncpy(tag.title, newValue, 30);
            tag.title[29] = '\0';
            printf("Title updated successfully.\n");
        }
        else if (strcmp(editFlag, "-a") == 0)
        {
            strncpy(tag.artist, newValue, 30);
            tag.artist[29] = '\0';
            printf("Artist updated successfully.\n");
        }
        else if (strcmp(editFlag, "-A") == 0)
        {
            strncpy(tag.album, newValue, 30);
            tag.album[29] = '\0';
            printf("Album updated successfully.\n");
        }
        else if (strcmp(editFlag, "-y") == 0)
        {
        if(strlen(newValue) != 4)
        {
            printf("Year must be exactly 4 digits.\n");
            return 1;
        }

            memcpy(tag.year, newValue, 4);  // EXACT 4 digits
            printf("Year updated successfully.\n");
        }
        else if (strcmp(editFlag, "-c") == 0)
        {
            strncpy(tag.comment, newValue, 30);
            tag.comment[29] = '\0';
            printf("Comment updated successfully.\n");
        }

        else if (strcmp(editFlag, "-g") == 0)
        {
            int genreValue = atoi(newValue);  // convert text to number

        if (genreValue < 0 || genreValue > 255)
            {
            printf("Invalid Genre! Must be 0–255.\n");
            return 1;
            }

        tag.genre = genreValue;   // assign 1 byte
        printf("Genre updated successfully.\n");
    }

        else
        {
            printf("Unsupported edit option: %s\n", editFlag);
            return 1;
        }

        // Step 3: Create duplicate file
        if (!createDuplicateFile(filename, "temp.mp3"))
        {
            printf("Failed to create temp file.\n");
            return 1;
        }

        // Step 4: Write updated tag
        if (!WriteUpdatedTag("temp.mp3", &tag))
        {
            printf("Failed to write updated tag.\n");
            return 1;
        }

        // Step 5: Replace original file
        if (!replaceOrignalFile(filename, "temp.mp3"))
        {
            printf("Failed to replace original file.\n");
            return 1;
        }

        return 0;
    }

  return 0;
}        

 




