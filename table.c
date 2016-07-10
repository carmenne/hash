#include "table.h"
#include "util.h"

// creates an array of pointers to bucket (pointers has NULL value)
bucket **create_hashtable(int size) {
	
	bucket **hashtable = calloc(size, sizeof(bucket*));
	DIE(!hashtable, "Hashtabble memory allocation not succeeded.\n");
	
	return hashtable;
}

void add_hash(char *token, bucket **hashtable, int size)
{
	
}
void remove_hash(char *token, bucket **hashtable, int size)
{
	
}
void clear_hash(bucket **hashtable)
{
	
}
void resize_hash(char *type, bucket **hashtable)
{
	
}
void find_hash(char *token, bucket **hashtable, int size, FILE *pFile_out)
{
	
}
void print(bucket **hashtable, FILE *pFile_out)
{
	
}
void print_bucket(int index, bucket **hashtable, FILE *pFile_out)
{
	
}