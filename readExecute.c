#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "util.h"
#include "table.h"

#define COMMAND_SIZE 20000
#define CMP(x, y) strncmp(x, y, strlen(y))

typedef enum {ADD, REMOVE, FIND, CLEAR, PRINT_BUCKET, PRINT, RESIZE} command_type;
void execute_command(FILE *pFile, bucket **hashtable, unsigned int size);
command_type get_command(char *c);
FILE *get_file(char* filename);
char *copy_str(char *input);
int main(int argc, char **argv)
{
	DIE(argc < 2, "Please enter the initial length of hashtable:\n");
	
	int i = 2; // itearates through args
	unsigned int size = 0;
	bucket **hashtable;
	
	size = atoi(argv[1]);

	// create the hashtable
	hashtable = create_hashtable(size);
	
	FILE *pFile;
	
	
	if (argc == 2) {
		// there are no optional parameters, read from stdin
		execute_command(stdin, hashtable, size);
	} else {
		for (int i = 2; i < argc; i++) {
			
			pFile = fopen (argv[i], "r");
			
			DIE (!pFile, "Error when opening file.\n");
			execute_command(pFile, hashtable, size);
			
			fclose (pFile);
		}
	}
}

void execute_command(FILE *pFile, bucket **hashtable, unsigned int size)
{
	char command_name[COMMAND_SIZE];
	FILE *pFile_out;
	
	while(fgets(command_name, COMMAND_SIZE , pFile)) {
	
		char *clean_line = strtok(command_name, "\r\n");

		char *token = strtok(clean_line, " ");
		if (!token)
			continue;
		// printf("Command:%s\n", token);
		
		command_type command = get_command(token);
		
		token = strtok(NULL, " ");
		// printf("Param:%s\n", token);
	
		
		switch(command) {
			case ADD :
				DIE (!token, "Please provide the word to be added.\n");
				add_hash(token, hashtable, size);
				break;
			
			case REMOVE :
				DIE (!token, "Please provide the word to be removed.\n");			
				remove_hash(token, hashtable, size);
				break;
			
			case CLEAR :
				clear_hash(hashtable, size);
				break;
				
			case RESIZE :
				hashtable = resize_hash(token, hashtable, size);
				if (strcmp(token, "double") == 0)
					size = 2 * size;
				else
					size = size / 2;
				break;
			
			case FIND :
				DIE (!token, "Please provide the word to be found.\n");		
				
				// file ouput is the 3rd argument, split again
				
				char *to_f = copy(token);
				printf("%s\n", token);
				printf("%s\n", to_f);
				token = strtok( NULL, " ");
				pFile_out = get_file(token);
				
				
				find_hash(to_f, hashtable, size, pFile_out);
				
				break;
			
			case PRINT :
				// file ouput is the 2nd argument (already splitted)
				pFile_out = get_file(token);
				
				DIE(!pFile_out, "Error with writing to file or stdout");
				
				print_hash(hashtable, pFile_out, size);
								
				break;
				
			case PRINT_BUCKET :
			
				DIE (!token, "Please provide the Bucket Index.\n");
				
				int index = atoi(token);
				
				DIE (index < 0, "Please provide a positive Bucket Index.\n");
				
				// file ouput is the 3rd argument, split again
				token = strtok( NULL, " ");

				pFile_out = get_file(token);
				
				print_bucket(index, hashtable, pFile_out);
				
				break;
				
			default:
			continue;	
		}
	}
	fclose(pFile_out);
}

command_type get_command(char *c)
{
	if (CMP(c, "add") == 0)
		return ADD;
	else if (CMP(c, "find") == 0)
		return FIND;
	else if (CMP(c, "print_bucket") == 0)
		return PRINT_BUCKET;
	else if (CMP(c, "print") == 0)
		return PRINT;
	else if (CMP(c, "remove") == 0)
		return REMOVE;
	else if (CMP(c, "clear") == 0)
		return CLEAR;			
	else if (CMP(c, "resize") == 0)
		return RESIZE;				
}

FILE *get_file(char* f)
{

	FILE *fp;
	if (f == NULL)
	{
		fp = stdout;
	} else {
		fp = fopen (f, "a");
					
		DIE(!fp, "Error when opening the file to write");
	}
	
	return fp;
}

copy(char *t)
{
	int len = strlen(t);
	char *to_f = malloc(len);
	strncpy(to_f, t, len);
	return to_f;
}
