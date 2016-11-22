/*
 * convgerber.c
 * 
 * Copyright 2016 Unknown <rmurphy@darkstar>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#define BS 0x08
#define LF 0x0A
#define FF 0x0C
#define CR 0x0D
#define SPACE 0x20
#define GERBER_TERM 0x2A

int main(int argc, char **argv)
{
	FILE* fptr_SRC;
	FILE* fptr_DEST;
	FILE* fptr_APERATURE;
	char* file_SRC = "BUFF-010.GBL";
	char* file_DEST = "BUFF-010.GBLX";
	const char *file_APERATURE= "aperture.dat";
	int gerber_read;
	int aperture_read;
	
	const char *header_1 = "G04 This is a Protel Autotrax gerber file converted by *\n";
	const char *header_2 = "G04 convgerber V-1.0 *\n";
    const char *header_3 = "G04 More information is available about convgerber at *\n";
	const char *header_4 = "G04 https://github.com/ozzyrob/convgerber *\n";
	const char *header_5 = "G04 --End of header info--*\n";
	const char *header_6 = "%MOIN*%\n";
	const char *header_7 = "%FSLAX23Y23*%\n";
	const char *header_8 = "%IPPOS*%\n";


//* Open data file	
	if ( ( fptr_APERATURE = fopen( file_APERATURE, "r" ) ) == NULL ) {
		printf( "\nCannot open the file:%s\n",file_APERATURE);
		return -1;
	}
//* Open source file	
	if ( ( fptr_SRC = fopen( file_SRC, "r" ) ) == NULL ) {
		printf( "\nCannot open the file:%s\n",file_SRC );
		return -1;
	}

//* Open destination file	
	if ( ( fptr_DEST = fopen( file_DEST, "w" ) ) == NULL ) {
		printf( "\nCannot open the file:%s\n",file_DEST );
		return -1;
	}	
	
	else {
		
//* Wirte header to destination file (this is a cludge)
			
		fputs( header_1, fptr_DEST);
		fputs( header_2, fptr_DEST);
		fputs( header_3, fptr_DEST);
		fputs( header_4, fptr_DEST);
		fputs( header_5, fptr_DEST);
		fputs( header_6, fptr_DEST);
		fputs( header_7, fptr_DEST);
		fputs( header_8, fptr_DEST);
		

//* Read aperture data file
//* Should check if it is a valid file
		while (  ( aperture_read = fgetc(fptr_APERATURE) ) != EOF ) { 
			
			fputc( aperture_read, fptr_DEST );
		}

//* Read source file a character at a time
		 while (  ( gerber_read = fgetc(fptr_SRC) ) != EOF ) {
				

				switch (gerber_read) {
					
//* If we have "*" write "*\n" to destination file					
					case GERBER_TERM:
						fputc( GERBER_TERM, fptr_DEST );
						fputc( LF, fptr_DEST );
						break;
//* Ignore Backspace, Line feed (newline), Form feed, Carriage return & space
					case BS :
					case LF :
					case FF :
					case CR :
					case SPACE :
						break;
//* Write X,Y, cordinates, D-codes, to destination file
//* Should check for "illegal characters"						
					default :
						fputc( gerber_read, fptr_DEST );
					}
			}
		}
	fclose( fptr_SRC );
	fclose( fptr_DEST );	
	fclose( fptr_APERATURE );
	
	return 0;
}

