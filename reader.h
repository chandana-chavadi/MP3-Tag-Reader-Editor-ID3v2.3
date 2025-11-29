#ifndef READER_H
#define READER_H

/* Detect and read tags (wrapper). */
int validate_ext(const char *filename);

/* ID3v1 reader: reads last 128 bytes. */
void view_tags(const char *filename);

void edit_tags(const char *filename,const char *tag,const char *updated_text);

#endif // READER_H


