
#include <stdio.h>
#include <string.h>
#include "reader.h"


void print_help() {
    printf("Usage:\n");
    printf("  chandana_MP3TAG -h              Show help\n");
    printf("  chandana_MP3TAG -v <file.mp3>   View tags of MP3 file\n");
    printf("  chandana_MP3TAG -e -t|-a|-y|-l|-c|-g <updated_text> <file.mp3>   Edit tags\n");
}

int main(int argc, char *argv[]) 
{
    if (argc < 2) {
        print_help();
        return 1;
    }

    if (strcmp(argv[1], "-h") == 0) {
        print_help();
        return 0;
    }

    else if (strcmp(argv[1], "-v") == 0) {
        if (argc < 3) {
            printf("❌ Please provide a filename after -v\n");
            return 1;
        }

        // Corrected validation logic: return 1 only if file is invalid
        if (!validate_ext(argv[2])) {
            return 1;
        }

        // Now this will run only if file is valid
        view_tags(argv[2]);
    }

        else if (strcmp(argv[1], "-e") == 0) 
    {
        if (argc < 5) 
        {
            printf("❌ Please provide a tag and filename after -e\n");
            return 1;
        }
        //printf("✏️ Editing tags of: %s\n", argv[2]);
        char *tag = NULL;
        if(strcmp(argv[2],"-t") == 0)
            tag = "TIT2";  // Title
        else if (strcmp(argv[2], "-a") == 0) 
            tag = "TPE1"; // Artist
        else if (strcmp(argv[2], "-l") == 0) 
            tag = "TALB"; // Album
        else if (strcmp(argv[2], "-y") == 0) 
            tag = "TYER"; // Year
        else if (strcmp(argv[2], "-c") == 0) 
            tag = "COMM"; // Comment
        else if (strcmp(argv[2], "-g") == 0) 
            tag = "TCON"; // Genre
        else 
        {
            printf("Invalid tag option!\n");
            return 1;
        }

        if(validate_ext(argv[4]))
        {
            return 1;
        }

        edit_tags(argv[4],tag,argv[3]);
        printf("\nUpdated Details:\n");
        view_tags(argv[4]);         
    }
    else 
    {
    printf("Invalid option. Use -v to view or -e to edit.\n");    
    }


  return 0;
}



