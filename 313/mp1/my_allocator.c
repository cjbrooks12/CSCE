#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "my_allocator.h"

int get_block_size(int _length_needed);
int get_previous_fibonacci_number(int _length);
int get_free_list_index(int _length);

//Allocator does not work. Throughout the code, I have explained what should be going on
//		so as to try and make sense of what I have done, regardless

//Header contains all the information necessary to track the memory blocks
//	~magic_number is a check to make sure that the memory pointed to is correct
//	~size keeps track of current block
//	~free denoted whether the block currently contains user-requested data
//	~inheritance tells of the data of the parent block
//	~buddy tells whether this block is a left or a right buddy.
//		Left buddies are always the larger buddy
//		Left buddies will always be boolean false
//	~next points to the following block in the linked list of that free list
//	~previous points to the previous, this allows us to correctly add/remove blocks from the list
//------------------------------------------------------------------------------
typedef struct header {
	int magic_number; 			//@0: at position 0 from start of pointer
	int size;					//@4
	bool free;					//@8
	bool inheritance;			//@10
	bool buddy;					//@12
	struct header* next;		//@16
	struct header* previous;	//@24
} header;

Addr heap;
header* free_list; //largest fibonacci number at free_list[0]
header* first;
unsigned int basic_block_size;
int global_magic_number = 48684;
int size_of_free_list; 
bool can_allocate;
int smallest_block; //makes splitting blocks easier to manage

//Initialization and release of allocator
//-----------------------------------------------------------------------------
unsigned int init_allocator(unsigned int _basic_block_size, unsigned int _length) {
	basic_block_size = _basic_block_size;
	can_allocate = true;
	heap = (Addr) malloc(get_block_size(_length));

	//determine how many lists need to be stored in the free_list 
	int counter = 2;
	int size = get_block_size(_length);
	while(size > 1) {
		size = get_previous_fibonacci_number(size);
		counter++;
	}

	size_of_free_list = counter;
	smallest_block = 0;
	free_list = (header*) malloc(size_of_free_list*sizeof(header*));

	//create the first header from which all other headers come from
	first = (header*) heap;
	first->magic_number = global_magic_number;
	first->size = get_block_size(_length);
	first->free = true;
	first->inheritance = false;
	first->buddy = false;
	first->next = NULL;
	first->previous = NULL;

	free_list[0] = *first;

	return get_block_size(_length);
}

int release_allocator() {
	free(heap);
	free(free_list);
	can_allocate = false;
}

//Helper functions to manage fibonacci numbers and how they relate to the free list
//------------------------------------------------------------------------------
int get_block_size(int _length_needed) {
	if(_length_needed <= basic_block_size) {
		return basic_block_size + sizeof(header);
	}
	else {
		int n_minus_one=2, n_minus_two=1;

		while(_length_needed + sizeof(header) > (n_minus_one*basic_block_size)) {
			int temp = n_minus_two;
			n_minus_two = n_minus_one;
			n_minus_one = n_minus_two + temp;
		}
		return n_minus_one*basic_block_size;
	}
}

int get_previous_fibonacci_number(int _length) {
	if(_length == basic_block_size) {
		return basic_block_size;
	}
	else {
		int n_minus_one=2, n_minus_two=1;

		while(_length > (n_minus_one*basic_block_size)) {
			int temp = n_minus_two;
			n_minus_two = n_minus_one;
			n_minus_one = n_minus_two + temp;
		}
		return n_minus_two*basic_block_size;
	}
}

int get_free_list_index(int _length) {
	int counter =  - 2;
	int size = _length;
	while(size > 1) {
		size = get_previous_fibonacci_number(size);
		counter++;
	}
	return size_of_free_list - counter;
}

int get_fibonacci_number_at_index(int _index) {
	int n_minus_one=2, n_minus_two=1;

	for(int i = 0; i <= (size_of_free_list - _index); i++) {
		int temp = n_minus_two;
		n_minus_two = n_minus_one;
		n_minus_one = n_minus_two + temp;
	}
	return n_minus_one*basic_block_size;
}

//functions to manage memory blocks
//------------------------------------------------------------------------------
void add_to_free_list(header* hdr, int list) {
	if(hdr->magic_number == global_magic_number) {
		header* pos = free_list + list*sizeof(header*);

		if(pos->magic_number != global_magic_number) {
			hdr->next = NULL;
			hdr->previous = pos;
			pos->next = hdr;
			pos[0] = *hdr;
			return;
		}
		else {
			while(true) {
				if(pos->next == NULL) {
					hdr->next = NULL;
					hdr->previous = pos;
					pos->next = hdr;
					hdr = (header*) (((char*)pos) + pos->size);
					return;
				}
				else {
					pos = pos->next;
				}
			}
		}
	}
	else {
		printf("1: error accessing memory address\n");
	}
}

void split_smallest_block() {
	header* pos = free_list + smallest_block*sizeof(header*);
	if(pos->magic_number == global_magic_number) {
	
		//create a left and right block from the single larger block
		bool buddy = pos->buddy;
		bool inheritance = pos->inheritance;
		int size = pos->size;

		header* left = pos;
		left->magic_number = global_magic_number;
		left->size = get_previous_fibonacci_number(size);
		left->free = true;
		left->buddy = false;
		left->inheritance = buddy;
		add_to_free_list(left, get_free_list_index(left->size));

		header* right = (header*) (((char*)pos) + (get_previous_fibonacci_number(size)/sizeof(header*)));
		right->magic_number = global_magic_number;
		right->size = get_previous_fibonacci_number(left->size);
		right->free = true;
		right->buddy = true;
		right->inheritance = inheritance;
		add_to_free_list(right, get_free_list_index(right->size));

		smallest_block = get_free_list_index(right->size);
	}
	else {
		printf("2: error accessing memory address\n");
	}
}

void merge_blocks(header* pos) {
	if(pos->magic_number == global_magic_number) {
		//if this block is a right buddy...
		if(pos->buddy == true) {
			if(pos->free == true) {
				header* left_buddy = (header*) (((char*)pos) - (get_block_size(pos->size)/sizeof(header*)));
				left_buddy->size = left_buddy->size + pos->size;
				left_buddy->free = true;
				left_buddy->buddy = pos->inheritance;
				left_buddy->inheritance = pos->buddy;
				add_to_free_list(pos, get_free_list_index(pos->size));
			}
		}
		//if it isn't right it must be left...
		else {
			header* right_buddy = (header*) (((char*)pos) + (pos->size/sizeof(header*)));
			if(right_buddy->free == true) {
				pos->size = pos->size + right_buddy->size;
				pos->free = true;
				pos->buddy = pos->inheritance;
				pos->inheritance = right_buddy->inheritance;
				add_to_free_list(pos, get_free_list_index(pos->size));
			}
			else {
				//buddy block isn't free, so just return;
				return;
			}
		}
	}
}

//User-called functions for allocating memory
//------------------------------------------------------------------------------
extern Addr my_malloc(unsigned int _length) {
	if(can_allocate == false) {
		printf("allocator not initialized\n");
		return NULL;
	}
	else {
		header* pos = first;
		if(pos->magic_number == global_magic_number) {
			int size = get_free_list_index(get_block_size(_length));

			//repeatedly splits the smallest block until one is found that is
			//	just big enough for what the user requested
			while(size > smallest_block) {
				split_smallest_block();
			}

			//returns the last item added to the correct free_list
			header* returned = &free_list[smallest_block];
			while(true) {
				if(returned->next == NULL) {
					//remove item from free list, set it to be not free, and return to caller
					returned->previous->next = NULL;
					returned->previous = NULL;
					returned->free = false;

					return returned + sizeof(header);
				}
				else {
					returned = returned->next;
				}
			}
		}
		return pos + sizeof(header);
	}
}

extern int my_free(Addr _a) {
	if(can_allocate == false) {
		printf("allocator not initialized\n");
		return -1;
	}
	else {
		header* pos = (header*) ((char*)_a) - sizeof(header);
		if(pos->magic_number == global_magic_number) {
			//take the item to be freed, add it to its correct free list, and set to be free
			int size = get_free_list_index(pos->size);
			add_to_free_list(pos, size);
			pos->free = true;

			merge_blocks(pos);
		}
		else {
			printf("3: error accessing memory address\n");
		}
		return 0;
	}
}





