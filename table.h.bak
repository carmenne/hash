#include <stdlib.h>
#include <stdio.h>

typedef struct node {
	char *name;
	struct node *next;
} bucket;

bucket **create_hashtable(int size);

void add_hash(char *token, bucket **hashtable, int size);
void remove_hash(char *token, bucket **hashtable, int size);
void clear_hash(bucket **hashtable);
void resize_hash(char *type, bucket **hashtable);
void find_hash(char *token, bucket **hashtable, int size, FILE *pFile_out);
void print(bucket **hashtable, FILE *pFile_out);
void print_bucket(int index, bucket **hashtable, FILE *pFile_out);