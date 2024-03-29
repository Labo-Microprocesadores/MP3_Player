/* 
 * ID3 read library
 * Created by Tim O'Brien, t413.com
 * Oct 28, 2010
 *
 * * Releaced under the Creative Commons Attribution-ShareAlike 3.0
 * * You are free 
 * *  - to Share, copy, distribute and transmit the work
 * *  - to Remix — to adapt the work
 * * Provided 
 * *  - Attribution (my name and website in the comments in your source)
 * *  - Share Alike - If you alter, transform, or build upon this work, 
 * *      you may distribute the resulting work only under 
 * *      the same or similar license to this one
 *
 * if you are unfamiliar with the terms of this lisence,
 *  would like to see the full legal code of the license,
 *  or have any questions please email me (timo@t413.com) or visit:
 *  http://creativecommons.org/licenses/by-sa/3.0/us/   for details
 */

#ifndef READ_ID3_H_
#define READ_ID3_H_

#include <stdbool.h>

#ifdef __arm__  // for an embedded enviroment, using FatFs from chan

#include "ff.h"				// FAT File System Library
#include "diskio.h" 			// Disk IO Initialize SPI Mutex

#define file_seek_absolute(file,position) f_lseek(file, position)
#define file_seek_relative(fi,pos) f_lseek(fi,fi->fptr+pos)
#define file_read(f,str,l,rea) f_read(f,str,(l),&(rea))

#else

#define FIL FILE
#define rprintf printf
#include <stdio.h>
#define file_seek_absolute(file,position) fseek (file , position , SEEK_SET)
#define file_seek_relative(fi,pos) fseek(fi,pos,SEEK_CUR)
#define file_read(f,str,l,rea) rea=fread(str,1,l,f)

#endif

/* 
 * read_ID3_info - read spesified tag to a string.
 *  example useage: 
 *    FIL file;
 *    f_open(&file, file_name, (FA_READ | FA_OPEN_EXISTING));
 *    char str[40];
 *    read_ID3_info(TITLE_ID3,str,sizeof(str),&file);
 *    printf("Title: %s\n",str);
 *    f_close(&file);
 * 
 *  Input: 
 *   -tag type, use one of the macros below like TITLE_ID3
 *   -char* of an array to read a string to
 *   -the max length to read to
 *	 -pointer to variable where tag size will be stored
 *   -the file pointer to read from
 *  Output: 
 *   1 == success, your data has been read to the array.
 */

#define TITLE_ID3 0
#define ALBUM_ID3 1
#define ARTIST_ID3 2
#define TRACK_NUM_ID3 3
#define YEAR_ID3 4
#define LENGTH_ID3 5

bool has_ID3_tag(FIL *fp);

unsigned char read_ID3_info(const unsigned char tag_name, char* output_str, unsigned int res_str_l, FIL* fp);

unsigned int get_ID3_size(FIL* fp);



#endif /* READ_ID3_H_ */
