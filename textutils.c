/* Utilities for handling text files in NLP
 * Written by oscillator */

/* Lib */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

char* file_chars;
char** file_strings;

/* readf
 * Reads input file contents by
 * specified type to string */
void readf(char* input, char* type){
	int i = 0;
	FILE* file=fopen(input, "r");
	fseek(file, 0, SEEK_END);
	int char_size=ftell(file);
	int str_size=char_size*sizeof(char*);
	rewind(file);
	char* text=(char*)malloc(sizeof(char));
	file_chars=(char*)malloc(sizeof(char)*char_size);
	file_strings=(char**)malloc(sizeof(char*));
	if(strcmp(type, "c")==0){
		while(fscanf(file,"%c",text)!=EOF){
			printf("%s",file_chars);
			file_chars[i]=text[0];
			i+=1;
		}
	}
	else{
		while(fscanf(file,"%s",text)!=EOF){
			file_strings[i]=text;
			printf("%s ",file_strings[i]);
			i+=1;
			file_strings=(char**)realloc(file_strings,sizeof(char*)*(i+1));
		}
	}
}



/* counter
 * Returns a count of all
 * none space characters */

int main(){
	readf("melville.txt","s");
}
