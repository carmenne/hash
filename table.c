#include "string.h"

#include "table.h"

bucket *create_bucket(char *w);
void add_node(char *w, bucket* current);

// creates an array of pointers to bucket (pointers has NULL value)
bucket **create_hashtable(unsigned int size) {
	
	bucket **hashtable = calloc(size, sizeof(bucket*));
	DIE(!hashtable, "Hashtabble memory allocation not succeeded.\n");
	
	return hashtable;
}

void add_hash(char *token, bucket **hashtable, unsigned int size)
{
	unsigned int index = hash(token, size);
	
	if (!hashtable[index]) {
		hashtable[index] = create_bucket(token);
	} else {
	
		bucket *current = hashtable[index];
		
		// go to the last node
		while(current->next) {
			current = current->next;
		}
		
		add_node(token, current);
	}
	
}
void remove_hash(char *token, bucket **hashtable, unsigned int size)
{
	
}
void clear_hash(bucket **hashtable)
{
	
}
void resize_hash(char *type, bucket **hashtable)
{
	
}
void find_hash(char *token, bucket **hashtable, unsigned int size, FILE *pFile_out)
{
	
}
void print(bucket **hashtable, FILE *pFile_out, unsigned int size)
{
	int index = 0;

	while (index < size)
	{
		if (hashtable[index])
		{
			print_bucket(index, hashtable, pFile_out);
			index++;
		}
	}
}
void print_bucket(int index, bucket **hashtable, FILE *pFile)
{
		if (hashtable[index])
		{
			bucket *current = hashtable[index];
			while(current) {
				fputs(current->word, pFile);
				fputs(" ", pFile);
				current = current->next;
			}
		fputs("\n", pFile);
	}
}

// Helper functions
bucket *create_bucket(char *w)
{
	bucket *b = calloc(1, sizeof(bucket));
	
	int len = strlen(w);
	b->word = malloc(len);
	strncpy(b->word, w, len);

	b->next = 0;
	return b;
}


void add_node(char *w, bucket* current)
{
	current->next = calloc(1, sizeof(bucket));
	
	int len = strlen(w);
	current->next->word = malloc(len);
	strncpy(current->next->word, w, len);

	current = current->next;
}