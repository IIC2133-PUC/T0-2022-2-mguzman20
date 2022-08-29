#pragma once

typedef struct song {
	int id;
	int disc_id;
	int length;
	int rating;
} Song;

typedef struct disco {
	int songs_count;
	int id;
	Song** songs;
} Disco;

typedef struct list {
	Song* song;
	struct list* next;
} List;

typedef struct batiplaylists {
	int id;
	int songs_count;
	List* first;
} Batiplaylists;

List* list_init(Song* song);
void list_append(List* list, Song* song);
void list_print(List* list);