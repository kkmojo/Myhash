#include "HashTable.h"

Node *create_node(KEY_TYPE key, VALUE_TYPE value)
{
	Node *p = (Node*)malloc(sizeof(Node*));
	p->key = key;
	p->value = value;
	p->next = 0;

	return p;
}

int Hash(KEY_TYPE key)
{
	int hash = 0;
	int len = strlen(key);
	int i;

	for(i = 0; i < len; i++)
	{
		hash+=key[i];
	}

	return hash;
}

HashTable *create_table()
{
	int i = 0;

	HashTable *hash = (HashTable*)malloc(sizeof(HashTable));
	if (hash == NULL){
		return NULL;

	}
	hash->entries = (Node**)malloc(sizeof(Node*)*INIT_CAPACITY);

	hash->size = 0;
	hash->capacity = INIT_CAPACITY;

	for(i = 0; i<INIT_CAPACITY; i++)
	{
		hash->entries[i] = NULL;
	}

	return hash;
}


void encapacity(HashTable *hash)
{
	int old_capacity = hash->capacity;
	int new_capacity = old_capacity * 2;
	int i = 0;
	Node **new_entre = (Node**)malloc(sizeof(Node*) * new_capacity);


	for(i = 0; i < old_capacity; i++)
	{
		new_entre[i] = hash->entries[i];
		printf("assign successful!\n");
	}

	for(i = 0; i < old_capacity; i++)
	{
		hash->entries[i] = NULL;
		printf("clear successful!\n");
	}

	free(hash->entries);

	hash->entries = new_entre;

	hash->capacity = new_capacity;

}



void table_set(HashTable *hash, KEY_TYPE key, VALUE_TYPE value)
{
	int index;
	double ratio = hash->size / hash->capacity;
	Node *entry = create_node(key, value);
	Node *p;
	if(ratio >= INC_RATIO)
	{
		encapacity(hash);
	}

	index = Hash(key) % hash->capacity;

	if(hash->entries[index] == NULL)
	{
		hash->entries[index] = entry;
	}
	else 
	{
		p = hash->entries[index];
		//find tail node 
		while(p->next)
		{
			if(strcmp(p->key,key) == 0)
			{
				p->value = value;
				free(entry);
				return;
			}
			p = p->next;
		}

		p->next = entry;
	}
	hash->size ++;

}

VALUE_TYPE table_get(HashTable *hash, KEY_TYPE key)
{
	int index = Hash(key);
	Node *p;
	if(hash->size == 0)
	{
		printf("NO Content!\n");
		return NULL;
	}
	else
	{
		index = index %  hash->capacity;
		p = hash->entries[index];

		while(p)
		{
			if(strcmp(p->key,key) == 0)
			{
				return p->value;
			}

			p = p->next;
		}

	}

	return NULL;
}

void table_del (HashTable *hash, KEY_TYPE key)
{
	int index = Hash(key) % hash->capacity;
	Node *p = hash->entries[index];
	Node *q;
	Node *needRemoved;
	if(hash->size == 0)
	{
		printf("NO content!");
		exit(1);
	}
	else
	{
		if(strcmp(p->key, key) != 0 )
		{
			while(p)
			{
				q = p;
				p = p->next;
			}

		}
		else 
		{
			needRemoved = p;
			p = p->next;
			q = p;
			free(needRemoved);
		}	
	}

}

void free_table(HashTable *hash)
{
	int i = 0; 
	for (i = 0; i < hash->capacity; i++)
	{
		hash->entries[i] = 0;
	}

	free(hash->entries);
	free(hash);
}

