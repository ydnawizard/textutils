/* Utilities for handling text files
 * Written by oscillator */

/* Lib */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>


/* Counter
 * Vestigal and stupid */
int counter(char *input){
	int count = 0;
	while(input[count] != 0){
		count += 1;
	}
	return count;
}

/* Char Counter
 * returns a count of all 
 * none space characters */
int char_counter(char *input, int size){
	char* chars = (char*)malloc(sizeof(char));
	int count = 0;
	int letter_count = 0;
	while(input[count] != 0){
		if (isspace(input[count])){
			count +=1;
		}
		else{
			chars[letter_count] = input[count];
			letter_count += 1;
			count += 1;
			chars = (char*)realloc(chars, sizeof(char)*(letter_count + 1));
		}
	}
	return letter_count;
	free(chars);
}

/* String Counter
 * returns a 1 if the input is a string
 * and 0 otherwise */

int string_counter(char *input){
	int count;
	char* c = " ";
	if (strcmp(input, c) != 0){
		count = 1;
	}
	else{
		count = 0;
	}
	return count;
}

/* Match Counter
 * returns a 1 if strings match and 0 otherwise */
int match_counter(char* input, char* match){
	int count;
	if(strcmp(input, match) == 0){
		count = 1;
	}
	else{
		count = 0;
	}
	return count;
}

/* Text Resize
 * Resizes an input text to the 
 * input character count */
char** text_resize(char** input, int size){
	int count = 0;
	char** resized_text = (char**)malloc(sizeof(char*));
	while(count < size){
		resized_text[count] = input[count];
		printf("%d ", count);
		count += 1;
		resized_text = (char**)realloc(resized_text, sizeof(char*)*(count+1));
	}
	return resized_text;
	free(resized_text);
}

int main(char argc, char* argv[]){
	int i = 0;
	int j = 0;
	int opt;
	int size;
	int input_size;
	int result = 0;
	char* string_result;
	FILE* file;
	FILE* new_file;
	char* text;
	char* inter_text;
	char* final_text;
	while((opt = getopt(argc, argv, ":csrmh")) != -1){
		switch(opt){
			case 'c':
				file = fopen(argv[2], "r");
				fseek(file, 0, SEEK_END);
				size = ftell(file);
				text = (char*)malloc(sizeof(char)*size);
				rewind(file);
				while(fscanf(file, "%c ", text) != EOF){
					result = result + char_counter(text, size);
				}
				printf("%d %s", result, "\n");
				fclose(file);
				free(text);
				break;
			case 's':
				file = fopen(argv[2], "r");
				fseek(file, 0, SEEK_END);
				size = ftell(file);
				rewind(file);
				text = (char*)malloc(sizeof(char)*size);
				while(fscanf(file, "%s", text) != EOF){
					result = result + string_counter(text);
				}
				printf("%d %s", result, "\n");
				fclose(file);
				free(text);
				break;
			case 'm':
				file = fopen(argv[2], "r");
				fseek(file, 0, SEEK_END);
				size = ftell(file);
				rewind(file);
				input_size = strlen(argv[3]);
				text = (char*)malloc(sizeof(char)*size);
				inter_text = (char*)malloc(sizeof(char)*size);
				final_text = (char*)malloc(sizeof(char)*input_size);
				while(fscanf(file, "%c", text) != EOF){
					inter_text[i] = text[0];
					i += 1;
				}
				i = 0;
				j = 0;
				while(i <= size){
					if (input_size >= size){
						i=size+1;
					}
					else if(i == input_size){
						printf("%s ", final_text);
						result = result + match_counter(final_text, argv[3]);
						input_size = input_size + 1;
						i = input_size - j;
						j = 0;
						}
					else{
						final_text[j] = inter_text[i];
						i += 1;
						j += 1;
					}
				}
				printf("%d %s", result, "\n");
				fclose(file);
				free(text);
				free(inter_text);
				free(final_text);
				break;
			case 'r':
				file = fopen(argv[2], "r");
				fseek(file, 0, SEEK_END);
				size = ftell(file);
				text = (char*)malloc(sizeof(char)*(size));
				string_result = (char*)malloc(sizeof(char)*strtol(argv[3], NULL, 10));
				rewind(file);
				while(i <= strtol(argv[3], NULL, 10)){
					fscanf(file, "%c", text);
					string_result = strcat(string_result, text);
					i += 1;

				}
				new_file = fopen(strcat(argv[2],"_resize"), "w");
				fprintf(new_file, string_result);
				fclose(file);
				fclose(new_file);
				free(text);
				free(string_result);
				break;

			case 'h':
				printf("%s"," Oscillator's text file utilities: \n \n -c	for no space character count (input file as arg)\n \n -s	for raw string count (input file as arg) \n \n -m	for specific matched string count (input file and string to match as args)\n \n -r	for resize (input file and char count as args)\n \n");
				break;
			default:
				printf("%s", "invalid option, use -h for help");
				break;
		}
	}
	return 0;
}
