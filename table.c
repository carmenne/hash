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
	// printf("Token: %s\n", token);
	
	if (!hashtable[index]) {
		hashtable[index] = create_bucket(token);
	} else {
		// printf("Token: %s\n", token);
		bucket *current = hashtable[index];
		
		// go to the last node
		while(current->next) {
			current = current->next;
		}
		
		if (is_present(token, hashtable, size) == 0)
			add_node(token, current);
	}
	
}
void remove_hash(char *token, bucket **hashtable, unsigned int size)
{
	unsigned int index = hash(token, size);
	
	if (!hashtable[index])
		return;
	
	
	bucket *tmp;
	
	
	if (strcmp(hashtable[index]->word, token) == 0) {
		// This  is the first word in the bucket
		tmp = hashtable[index]->next;
		free(hashtable[index]);
		hashtable[index]=tmp;
	} else {

		bucket *current = hashtable[index];
		while(current->next !=NULL) {
			if (strcmp(current->next->word, token) == 0){
				tmp = current->next->next;
				free(current->next);
				current->next = tmp;
				return;
			}else {
				current = current->next;
			}
		}
	}
	
}

void clear_hash(bucket **hashtable, int size)
{
	int index = 0;
	bucket *tmp;

	while (index < size)
	{
		if (hashtable[index])
		{
			bucket *current = hashtable[index];
			while(current->next) {
				tmp = current->next;
				free(current);
				current = tmp;
			}
			if (current != NULL)
				free(current);
		}
		hashtable[index] = NULL;
		index++;
	}
}
bucket** resize_hash(char *type, bucket **hashtable, int size)
{
	bucket **copy;
	int index = 0;
	int new_size = 0;
	
	if (strcmp(type, "double") == 0)
		new_size = 2 * size;
	else
		new_size = size / 2;
	
	copy = create_hashtable(new_size);

	while (index < size)
	{
		if (hashtable[index])
		{
			bucket *current = hashtable[index];
			while(current) {
				add_hash(current->word, copy, new_size);
				current = current->next;
			}
		}
		index++;
	}
	
	clear_hash(hashtable, size);
	return copy;
}
void find_hash(char *token, bucket **hashtable, unsigned int size, FILE *fp)
{
	if (is_present(token, hashtable, size) == 0) {
		fputs("False\n", fp); 
	} else {
		fputs("True\n", fp);
	}
		
	fflush(fp);	
}

void print_hash(bucket **hashtable, FILE *fp, unsigned int size)
{
	int index = 0;

	while (index < size)
	{
		if (hashtable[index])
		{
			print_bucket(index, hashtable, fp);
		}
		index++;
	}
		fputs("\n", fp);
}
void print_bucket(int index, bucket **hashtable, FILE *fp)
{
		if (hashtable[index])
		{
			bucket *current = hashtable[index];
			while(current->next) {
				fputs(current->word, fp);
				fputs(" ", fp);
				current = current->next;
			}
			fputs(current->word, fp);
		}
		fputs("\n", fp);
		fflush(fp);
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

	current->next->next = 0;
	current = current->next;
}

int is_present(char *w, bucket **hashtable, unsigned int size)
{
	unsigned int index = hash(w, size);
	
	if (!hashtable[index])
		return 0;
	
	bucket *current = hashtable[index];
	while(current) {
		if(strcmp(w, current->word) == 0)
			return 1;
			
		current = current->next;
	}

	return 0;
}
