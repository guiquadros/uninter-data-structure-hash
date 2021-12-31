#include "stdio.h"
#include "stdlib.h"

#define BUCKET_SIZE 12

int menu();
void clean_keyboard_buffer();
struct hash_table* create_new_hash_table();
int get_hash_code(int value);
void insert_in_hash_table(struct hash_table* hash_table, int key, int bucket_position);
void show_hash_table(struct hash_table* hash_table);

struct hash_linked_list_node
{
	int key;
	struct hash_linked_list_node *next;
};

struct hash_table
{
	int size;
	struct hash_linked_list_node **bucket;
};

int main()
{
	struct hash_table *hash_table = create_new_hash_table();

	do
	{
		int option = menu();

		switch (option)
		{
		case 1:
			int key;
			printf("Inform the key (int) to be inserted in the Hash Table: ");
			scanf_s("%d", &key);
			clean_keyboard_buffer();

			int bucket_position = get_hash_code(key);
			insert_in_hash_table(hash_table, key, bucket_position);
			break;

		case 2:
			//TODO: Remove
			break;

		case 3:
			//TODO: Search
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

void insert_in_hash_table(struct hash_table* hash_table, int key, int bucket_position)
{
	struct hash_linked_list_node* entry = (struct hash_linked_list_node*)malloc(sizeof(struct hash_linked_list_node));
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
	struct hash_table *new_hash_table = (struct hash_table*)malloc(sizeof(struct hash_table));
	new_hash_table->size = BUCKET_SIZE;
	new_hash_table->bucket = (struct hash_linked_list_node**)malloc(BUCKET_SIZE * sizeof(struct  hash_linked_list_node*));

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

		struct hash_linked_list_node* entry_node = hash_table->bucket[i];

		while (entry_node != NULL)
		{
			printf("%d -> ", entry_node->key);
			entry_node = entry_node->next;
		}

		printf("\n");
	}

	printf("\n");
}
