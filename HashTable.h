#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY_TYPE char*
#define VALUE_TYPE char* 
#define INIT_CAPACITY 16
#define INC_RATIO 0.5

typedef struct _node
{
	KEY_TYPE key;
	VALUE_TYPE value;
	struct _node *next;
}Node;


typedef struct _hashtable
{
	Node **entries;
	int size;
	int capacity;
}HashTable;

Node *create_node(KEY_TYPE key, VALUE_TYPE value);

int Hash (KEY_TYPE key);

HashTable *creat_table();

void encapacity(HashTable *hash);

void table_set(HashTable *hash, KEY_TYPE key, VALUE_TYPE value);

VALUE_TYPE table_get(HashTable *hash, KEY_TYPE key);

//void table_del(Hashtable *hash, KEY_TYPE *key);

void free_table(HashTable *hash);


