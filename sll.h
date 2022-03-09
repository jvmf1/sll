#pragma once

typedef struct sll_entry {
	struct sll_entry *next;
	struct sll_entry *prev;
	void *data;
} sll_entry;

typedef struct sll {
	sll_entry *head;
	sll_entry *tail;
	void (*free_data_function)(void*);
} sll;

#define SLL_FOREACH(entry, tmp) \
		for( ; (entry) && ( (tmp) = ((entry)->data), 1) ; (entry) = ((entry)->next) )

#define SLL_FOREACH_SAFE(entry, next_entry, tmp) \
		for( ; (entry) && ((next_entry) = ((entry)->next), 1) && ((tmp) = ((entry)->data), 1) ; (entry) = (next_entry) )

sll_entry* sll_entry_create(void *data); 

void sll_entry_free(sll *ll, sll_entry *entry);

sll* sll_create();

void sll_free(sll *ll);

int sll_push(sll *ll, void *data);

void sll_pop(sll *ll);

void sll_remove(sll *ll, sll_entry *entry);

void sll_print(sll *ll);

int sll_insert_after(sll *ll, sll_entry *entry, void *data);

int sll_insert_before(sll *ll, sll_entry *entry, void *data);
