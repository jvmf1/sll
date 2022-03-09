#include "sll.h"
#include <stdio.h>
#include <stdlib.h>

sll_entry* sll_entry_create(void *data) {
	sll_entry *entry = malloc(sizeof(sll_entry));
	entry->next=NULL;
	entry->prev=NULL;
	entry->data=data;
	return entry;
}

void sll_entry_free(sll *ll, sll_entry *entry) {
	if (ll->free_data_function!=NULL)
		ll->free_data_function(entry->data);
	free(entry);
}

sll* sll_create() {
	sll *ll = malloc(sizeof(sll));
	ll->head=NULL;
	ll->tail=NULL;
	ll->free_data_function=NULL;
	return ll;
}

void sll_pop(sll *ll) {
	// there is no entries
	if (ll->head==NULL) return;

	if (ll->head==ll->tail) {
		// there is only one entry
		sll_entry_free(ll,ll->head);
		ll->head=NULL;
		ll->tail=NULL;
		return;
	}
	if (ll->head->next==ll->tail) {
		// there is two entries
		sll_entry_free(ll,ll->tail);
		ll->head->next=NULL;
		ll->tail=ll->head;
		return;
	}
	// there is 3+
	sll_entry *last = ll->tail;
	ll->tail=ll->tail->prev;
	ll->tail->next=NULL;
	sll_entry_free(ll,last);
}

void sll_remove(sll *ll, sll_entry *entry) {
	if (entry==NULL) return;
	if (ll->head==NULL) return;
	if (ll->head->next==NULL) {
		// is the only entry
		sll_entry_free(ll,entry);
		ll->head=NULL;
		ll->tail=NULL;
		return;
	}

	// there is 2 entries
	if (ll->head->next==ll->tail) {
		if (entry==ll->tail) {
			sll_entry_free(ll,ll->tail);
			ll->head->next=NULL;
			ll->head->prev=NULL;
			ll->tail=ll->head;
			return;
		} else {
			sll_entry_free(ll,ll->head);
			ll->tail->next=NULL;
			ll->tail->prev=NULL;
			ll->head=ll->tail;
			return;
		}
	}

	if (entry==ll->head) {
		// is the first entry
		entry->next->prev=NULL;
		ll->head=entry->next;
		sll_entry_free(ll,entry);
		return;
	}

	if (entry==ll->tail) {
		// is the last entry
		entry->prev->next=NULL;
		ll->tail=entry->prev;
		sll_entry_free(ll,entry);
		return;
	}

	entry->prev->next=entry->next;
	entry->next->prev=entry->prev;
	sll_entry_free(ll,entry);
}

int sll_push(sll *ll, void *data) {
	sll_entry *new_entry = sll_entry_create(data);
	if (new_entry==NULL) return -1;
	if (ll->head==NULL) {
		// is empty
		ll->head=new_entry;
		ll->tail=new_entry;
		return 0;
	}

	new_entry->prev=ll->tail;
	ll->tail->next=new_entry;
	ll->tail=new_entry;
	return 0;
}

int sll_insert_after(sll *ll, sll_entry *entry, void *data) {
	sll_entry *new_entry = sll_entry_create(data);
	if (new_entry==NULL) return -1;
	if (ll->head==NULL) {
		// linked list is empty
		ll->head=new_entry;
		ll->tail=new_entry;
		return 0;
	}
	new_entry->prev=entry;
	new_entry->next=entry->next;
	if (entry->next==NULL) {
		// is inserting in the last position
		entry->next=new_entry;
		ll->tail=new_entry;
		return 0;
	}
	entry->next->prev=new_entry;
	entry->next=new_entry;
	return 0;
}

int sll_insert_before(sll *ll, sll_entry *entry, void *data) {
	sll_entry *new_entry = sll_entry_create(data);
	if (new_entry==NULL) return -1;
	if (ll->head==NULL) {
		// linked list is empty
		ll->head=new_entry;
		ll->tail=new_entry;
		return 0;
	}
	new_entry->next=entry;
	new_entry->prev=entry->prev;
	if (entry->prev==NULL) {
		// is inserting in the first position
		entry->prev=new_entry;
		ll->head=new_entry;
		return 0;
	}
	entry->prev->next=new_entry;
	entry->prev=new_entry;
	return 0;
}

void sll_free(sll *ll) {
	sll_entry *current = ll->head;
	if (current==NULL) {
		free(ll);
		return;
	}
	
	sll_entry *next;
	while(current!=NULL) {
		next = current->next;
		sll_entry_free(ll,current);
		current=next;
	}

	free(ll);
}

void sll_print(sll *ll) {
	printf("ll %p head:%p tail:%p\n", ll, ll->head, ll->tail);
	sll_entry *current = ll->head;
	while (current!=NULL) {
		printf("\t%p data:%p\tprev:%p next:%p\n", current, current->data, current->prev, current->next);
		current=current->next;
	}
}
