#include "stdio.h"
#include "stdlib.h"

// to reduce collisions it is better to use prime numbers for the bucket size
//(the bucket size is used in the hash function that is based on the division method)
//#define BUCKET_SIZE 12
#define BUCKET_SIZE 13

struct entry_node;
int menu();
void clean_keyboard_buffer();
struct hash_table* create_new_hash_table();
int get_hash_code(int value);
void insert_in_hash_table(struct hash_table* hash_table, int key);
void show_hash_table(struct hash_table* hash_table);
struct search_result* search_key_in_hash_table(struct hash_table* hash_table, int key);

// type each node of the linked list that stores the entries associated with a bucket position
//(each bucket position points to a linked list, this simplifies collision handling)
struct entry_node
{
	int key;
	struct entry_node* next;
};

struct hash_table
{
	int size;
	struct entry_node** bucket;
};

struct search_result
{
	struct entry_node* entry;
	int bucket_position;
	int entries_linked_list_position;
};

int main()
{
	struct hash_table* hash_table = create_new_hash_table();

	do
	{
		int option = menu();

		switch (option)
		{
		case 1:
			printf("Inform the key (int) to be inserted in the Hash Table: ");
			int new_key;
			scanf_s("%d", &new_key);
			clean_keyboard_buffer();

			insert_in_hash_table(hash_table, new_key);
			break;

		case 2:
			//TODO: Remove
			break;

		case 3:
			printf("Inform the key (int) to be searched in the Hash Table: ");
			int search_key;
			scanf_s("%d", &search_key);
			clean_keyboard_buffer();

			struct search_result* search_result = search_key_in_hash_table(hash_table, search_key);

			if (search_result != NULL)
			{
				printf("\nEntry found!\n");
				printf(" - bucket position: %d\n", search_result->bucket_position);
				printf(" - entries linked list position: %d\n", search_result->entries_linked_list_position);
				printf(" - key: %d\n", search_result->entry->key);

				free(search_result);
			}
			else
			{
				printf("\nEntry NOT found!\n");
			}
			break;

		case 4:
			show_hash_table(hash_table);
			break;

		case 5:
			printf("Bye!\n");
			system("pause");
			return 0;

		default:
			printf("Invalid option!\n");
			break;
		}

		printf("\n");
		system("pause");
	} while (1);
}


int menu()
{
	system("cls");

	printf("1 - Insert into Hash Table.\n");
	printf("2 - Remove from Hash Table.\n");
	printf("3 - Search in Hash Table.\n");
	printf("4 - Show the Hash Table.\n");
	printf("5 - Exit.\n");
	printf("\nInform your option: ");

	int option;
	scanf_s("%d", &option);

	clean_keyboard_buffer();

	system("cls");

	return option;
}

void clean_keyboard_buffer()
{
	int c;

	do
	{
		c = getchar();
	} while (c != '\n' && c != EOF);
}

int get_hash_code(const int value)
{
	int hash_code = value % BUCKET_SIZE;
	return hash_code;
}

void insert_in_hash_table(struct hash_table* hash_table, int key)
{
	int bucket_position = get_hash_code(key);

	struct entry_node* entry = (struct entry_node*)malloc(sizeof(struct entry_node));
	entry->key = key;

	// the new entry's next element is set to be the current first element of that bucket space 
	entry->next = hash_table->bucket[bucket_position];

	// now, the first element of that bucket space becomes the new entry,
	//in other words, we inserted 'entry' in the beginning, as the first node, of the linked list of that bucket
	hash_table->bucket[bucket_position] = entry;

	printf("Key '%d' inserted in the position '%d' of the bucket's hash obtained from the hash code function (division method).\n", key, bucket_position);
}

struct hash_table* create_new_hash_table()
{
	struct hash_table* new_hash_table = (struct hash_table*)malloc(sizeof(struct hash_table));
	new_hash_table->size = BUCKET_SIZE;
	new_hash_table->bucket = (struct entry_node**)malloc(BUCKET_SIZE * sizeof(struct  entry_node*));

	for (int i = 0; i < BUCKET_SIZE; ++i)
	{
		new_hash_table->bucket[i] = NULL;
	}

	return new_hash_table;
}

void show_hash_table(struct hash_table* hash_table)
{
	for (int i = 0; i < hash_table->size; ++i)
	{
		printf("\nLinked List of the keys stored in Hash Table's Bucket #%d:\n", i);

		struct entry_node* entry_node = hash_table->bucket[i];

		while (entry_node != NULL)
		{
			printf("%d -> ", entry_node->key);
			entry_node = entry_node->next;
		}

		printf("\n");
	}

	printf("\n");
}

struct search_result* search_key_in_hash_table(struct hash_table* hash_table, int key)
{
	const int bucket_position = get_hash_code(key);
	struct entry_node* entry = hash_table->bucket[bucket_position];

	int i = 0;
	while (entry != NULL)
	{
		if (entry->key == key)
		{
			struct search_result* search_result = (struct search_result*)malloc(sizeof(struct search_result));

			search_result->bucket_position = bucket_position;
			search_result->entries_linked_list_position = i;
			search_result->entry = entry;

			return search_result;
		}

		entry = entry->next;
		i++;
	}

	return NULL;
}
