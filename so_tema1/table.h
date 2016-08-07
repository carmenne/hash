#include <stdlib.h>
#include <stdio.h>

#include "hash.h"
#include "util.h"

typedef struct node {
	char *word;
	struct node *next;
} bucket;

bucket **create_hashtable(unsigned int size);

void add_hash(char *token, bucket **hashtable, unsigned int size);
void remove_hash(char *token, bucket **hashtable, unsigned int size);
void clear_hash(bucket **hashtable, int size);
bucket **resize_hash(char *type, bucket **hashtable, int size);
void find_hash(char *token, bucket **hashtable, unsigned int size, FILE *pFile_out);
void print_hash(bucket **hashtable, FILE *pFile_out, unsigned int size);
void print_bucket(int index, bucket **hashtable, FILE *pFile_out);
