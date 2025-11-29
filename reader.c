#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "reader.h"


int read_size(unsigned char size_bytes[4])
{
     return (size_bytes[0] << 24) |
           (size_bytes[1] << 16) |
           (size_bytes[2] << 8)  |
           (size_bytes[3]);
}


int validate_ext(const char *filename)
{
    const char *ext = strrchr(filename,'.');    //Get file extension
    if(!ext || strcmp(ext,".mp3") != 0)         //chech if .mp3
    {
        printf("Error:%s is not an MP3 file!\n",filename);
        return 0;
    }

    FILE *fp = fopen(filename,"rb");    //open file in binary read mode
    if(fp == NULL)
    {
        printf("Error:Cannot open %s\n",filename);
        return 0;
    }

    unsigned char header[3];        //read first 3 bytes of header
    if(fread(header,1,3,fp) != 3)
    {
        fclose(fp);
        printf("Error:Failed to read file header!\n");
        return 0;
    }
    fclose(fp);

    //check if first 3 bytes are 'ID3'
    if(strncmp((char*)header,"ID3",3) != 0)
    {
        printf("Error:No ID3V2.3 tag found in %s\n",filename);
        return 0;
    }
    return 1;   //valid MP3 with ID3v2.3 tag
}


void view_tags(const char *filename)
{
    FILE *fp = fopen(filename,"rb");    //open MP3 in read mode
    if(fp == NULL)
    {
        printf("Error:cannot open %s\n",filename);
        return;
    }

    unsigned char header[10];
    fread(header,1,10,fp);      //Read ID3 header(10 bytes)
   
    while(1)
    {
        char frame_id[5] = {0};         //frame ID(TIT2,TPE1,etc..)
        unsigned char size_bytes[4];    //size of frame
        unsigned short flags;           //flags(2 bytes)

        if(fread(frame_id,1,4,fp) != 4)     //Read frame ID
            break;
        if(fread(size_bytes,1,4,fp) != 4)    //Read frame size
            break;
        if(fread(&flags,1,2,fp) != 2)         //Read frame flags
            break;

        int size = read_size(size_bytes);       //convert size bytes into int
        if(size <= 0)                           //stop if invalid size
            break;

        char *data = (char*)malloc(size+1);     // Allocate memory for frame data
        fread(data,1,size,fp);                  // Read frame data
        data[size] = '\0';                      // Null terminate string

        int offset = (data[0] == 1) ? 3 : 1;

        // Print each frame if it matches
        if(strcmp(frame_id, "TIT2") == 0) 
            printf("Title : %s\n", data+offset);
        else if(strcmp(frame_id, "TPE1") == 0) 
            printf("Artist : %s\n", data+offset);
        else if(strcmp(frame_id, "TALB") == 0) 
            printf("Album : %s\n", data+offset);
        else if(strcmp(frame_id, "TYER") == 0 || strcmp(frame_id, "TDRC") == 0) 
            printf("Year : %s\n", data+offset);
        else if(strcmp(frame_id, "COMM") == 0) 
            printf("Comment : %s\n", data+4);  // Skip encoding + language + description
        else if(strcmp(frame_id, "TCON") == 0) 
            printf("Genre : %s\n", data+offset);
        
        free(data);     // Free allocated memory
    }
    fclose(fp);         // Close the file
}


void edit_tags(const char *filename,const char *tag,const char *new_value)
{
    FILE *fp = fopen(filename,"r+b");        // Open MP3 in read+write mode
    if(fp == NULL)
    {
        printf("Error:Cannot open %s\n",filename);
        return;
    }

    unsigned char header[10];
    fread(header,1,10,fp);          // Read ID3 header

    while(1)
    {
        char frame_id[5] = {0};
        unsigned char size_bytes[4];
        unsigned short flags;

        if(fread(frame_id,1,4,fp) != 4)
            break;
        if(fread(size_bytes,1,4,fp) != 4)
            break;
        if(fread(&flags,1,2,fp) != 2)
            break;

        int size = read_size(size_bytes);
        if(size <= 0)
            break;

        long pos = ftell(fp);       // Remember position for update

        if(strcmp(frame_id,tag) == 0)      
        {
            char *buffer = (char*)malloc(size);
            fread(buffer, 1, size, fp);

            fseek(fp,pos,SEEK_SET);          // Move to frame start
            fputc(0,fp);                    // Overwrite first byte (encoding)
            fwrite(new_value,1,strlen(new_value),fp);   // Write new value

            for(int i=strlen(new_value)+1; i<size; i++)     // Fill remaining space with 0
                fputc(0,fp);
            
            printf("%s updated successfully to %s\n",frame_id,new_value);
            free(buffer);
            fclose(fp);
            return;
        }
        fseek(fp,size,SEEK_CUR);          // Skip to next frame

    }
    printf("Tag %s not found!\n",tag);
    fclose(fp);       
}