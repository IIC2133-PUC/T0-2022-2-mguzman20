
#include "discos.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

List* list_init(Song* song){
	List* list = malloc(sizeof(List));
	*list = (List){
		.song = song,
		.next = NULL,
	};
	return list;
};

void list_append(List* list, Song* song){
	List *last = list;
	while (last -> next != NULL){
		last = last -> next;
	};
	List *new_list = list_init(song);
	last -> next = new_list;
}

bool list_find(List* list, Song* song){
	List* node = list;
	while(node != NULL){
		if (node->song == song)
		{
			return true;
		};
		node = node->next;
	};
	return false;
};

void list_destroy(List* list)
{
  // Si hay un nodo en la sig posicion, llamamos recursivamente a la funcion
  if (list->next)
  {
    list_destroy(list->next);
  }
  
  // Luego, liberamos la lista
  free(list);
};