
#include "discos.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

List* list_init(Song* song){
	List* list = malloc(sizeof(List));
	*list = (List){
		.song = song,
		.next = NULL
	};
	return list;
};

void list_append(List* list, Song* song){
	List *last = list;
	while (last -> next){
		last = last -> next;
	};
	List *new_list = list_init(song);
	last -> next = new_list;
};

void list_print(List* list)
{
  printf("%i %i -> ", list->song->length, list->song->rating);
  if (!list->next)
  {
    printf("NULL\n");
  }
  else
  {
    list_print(list->next);
  }
}
