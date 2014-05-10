#include "HashTable.h"
#include <string.h>

void print_table(HashTable *hash)
{
	int i, j, k;	
	Node *p;

	for(i = 0; i < hash->capacity; i++)
	{
		printf("%d:\t", i);
		p = hash->entries[i];
		if(p != NULL)
		{
			for(j = 0; p != NULL; j++, p = p->next)
			{	
				if(j != 0)
				{
					printf("\t");
				}
				for(k = 0; k < j * 4; k++)
				{
					printf(" ");
				}
				printf("Node[%p](\"%s\" : \"%s\", next = %p)\n", p, p->key, p->value, p->next);
			}
		}else
		{
			printf("NULL\n");
		}
	}
}

int main()
{
	HashTable *ht;
	char *keys[]   = {"a", "b", "c", "d", "e", "f", "g", "h", "i"};
	char *values[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
	char *duplicate_key = keys[0];
	char *duplicate_value = "123";

	char *sameHashKeys[] = {" !", "A"};
	char *sameHashValues[] = {"Hash(\" !\")", "Hash(\"A\")"};

	int i;
	char *r;

	printf("Testing create_table()\n");
	ht = create_table();
	if (ht != NULL){
		printf("ok\n");
	}else {
		printf("im shit\n");
	}

	printf("Testing table_set()\n");
	for(i = 0; i < 5; i ++)
	{
		table_set(ht, keys[i], values[i]);		
	}
	printf("ok\n");

	printf("Testing table_get()\n");
	for(i = 0; i < 5; i ++)
	{
		r = table_get(ht, keys[i]);
		if(strcmp(r, values[i]) != 0)
		{
			printf("Fail in testing...\n");
			printf("%s:%s, Excepted: %s:%s\n", keys[i], r, keys[i], values[i]);
			return -1;
		}
		else
		{
			printf("%s:%s\n", keys[i], r);
		}
	}
	printf("ok\n");

	printf("Testing duplicate key setting\n");
	table_set(ht, duplicate_key, duplicate_value);
	r = table_get(ht, duplicate_key);
	if(strcmp(r, duplicate_value))
	{
		printf("Fail in testing...\n");
		printf("%s:%s, Excepted: %s:%s\n", duplicate_key, r, duplicate_key, duplicate_value);
		return -1;
	}
	else
	{
		printf("%s:%s\n", duplicate_key, r);
	}
	printf("ok\n");

	printf("Testing encapacity()\n");
	for(i = 5; i < 9; i++)
	{
		table_set(ht, keys[i], values[i]);
	}
	if(ht->capacity != 16)
	{
		printf("Fail in testing...\n");
		printf("ht->capacity = %d, Excepted: %d\n", ht->capacity, 16);
		return -1;
	}
	else
	{
		printf("ht->capacity = %d\n", ht->capacity);
	}
	printf("ok\n");

	printf("Testing hash collision\n");
	for(i = 0; i < 2; i++)
	{
		printf("%s = %d\n", sameHashValues[i], Hash(sameHashKeys[i]));
		table_set(ht, sameHashKeys[i], sameHashValues[i]);
	}

	for(i = 0; i < 2; i++)
	{
		r = table_get(ht, sameHashKeys[i]);
		if(strcmp(r, sameHashValues[i]) != 0)
		{
			printf("Fail in testing...\n");
			printf("%s:%s, Excepted: %s:%s\n", sameHashKeys[i], r, sameHashKeys[i], sameHashValues[i]);
			return -1;
		}
		else
		{
			printf("%s:%s\n", sameHashKeys[i], r);
		}
	}
	printf("ok\n");

	print_table(ht);

	printf("Testing free_table()\n");
	free_table(ht);
	printf("ok\n");
	return 0;
}