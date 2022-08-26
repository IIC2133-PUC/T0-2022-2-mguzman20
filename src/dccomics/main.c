#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct song {
	int id;
	int disc_id;
	int length;
	int rating;
} Song;

typedef struct disco {
	int songs_count;
	int id;
	Song *songs;
} Disco;

typedef struct list {
	Song song;
	struct list* next;
} List;

typedef struct batiplaylists {
	int id;
	int songs_count;
	struct list* first;
	struct list* last;
} Batiplaylists;

List* list_init(Song song){
	List* list = malloc(sizeof(List));
	*list = (List){
		.song = song,
		.next = NULL
	};
	return list;
};

void list_append(List* list, Song song){
	List *last = list;
	while (last -> next){
		last = last -> next;
	};
	List *new_list = list_init(song);
	last -> next = new_list;
};

void list_print(List* list)
{
  printf("%i %i -> ", list->song.length, list->song.rating);

  // Revisamos si sigue
  if (!list->next)
  {
    printf("NULL\n");
  }
  else
  {
    // Hacemos llamado recursivo
    list_print(list->next);
  }
}

/* Retorna true si ambos string so iguales */
bool string_equals(char *string1, char *string2) {
	return !strcmp(string1, string2);
}

/* Función encargada de chequear los argumentos ingresados */
bool check_arguments(int argc, char **argv) {
	if (argc != 3) {
		printf("Modo de uso: %s INPUT OUTPUT\n", argv[0]);
		printf("Donde:\n");
		printf("\tINPUT es la ruta del archivo de input\n");
		printf("\tOUTPUT es la ruta del archivo de output\n");
		return false;
	}
	return true;
}

int main(int argc, char **argv) {
	/////////////////////////
	//        Input        //
	/////////////////////////
	/* Si los parámetros del programa son inválidos */
	if (!check_arguments(argc, argv)) {
		/* Salimos del programa indicando que no terminó correctamente */
		return 1;
	}

	/* Abrimos el archivo de input */
	FILE *input_file = fopen(argv[1], "r");

	/* Abrimos el archivo de output */
	FILE *output_file = fopen(argv[2], "w");

	/* String que usaremos para guardar la instrucción actual*/
	char command[32];

	// Lectura del número de batiplaylists
	int N_BATIPLAYLISTS;
	fscanf(input_file, "%d", &N_BATIPLAYLISTS);
	Batiplaylists **playlists = calloc(N_BATIPLAYLISTS, sizeof(Batiplaylists *));

	// Lectura del número de discos
	int N_DISCS;
	fscanf(input_file, "%d", &N_DISCS);
	Disco **discos = calloc(N_DISCS, sizeof(Disco*));
	for (int i = 0; i < N_DISCS; i += 1) {
		discos[i] = malloc(sizeof(Disco));
	};
	int n_del_disco = 0;
	/* Leemos la primera instrucción */
	fscanf(input_file, "%s", command);

	/* Mientras la instrucción sea distinta a FIN */
	while (!string_equals(command, "FIN")) {
		/////////////////////////
		//       Parte A       //
		/////////////////////////

		if (string_equals(command, "CREAR-DISCO")) {
			/* Obtenemos la información del disco */
			int capacity, length, rating;
			fscanf(input_file, "%d", &capacity);

			/* COMPLETAR */

			Song **songs = calloc(capacity, sizeof(Song *));
			for (int i = 0; i < capacity; i++) {
				songs[i] = malloc(sizeof(Song));
			};

			*discos[n_del_disco] = (Disco){
			    .id = n_del_disco,
			    .songs_count = capacity,
			    .songs = calloc(capacity, sizeof(Song))};

			for (int i = 0; i < capacity; i++) {
				fscanf(input_file, "%i", &length);
				fscanf(input_file, "%i", &rating);
				discos[n_del_disco]->songs[i] = (Song){.id = i, .disc_id=n_del_disco, .length = length, .rating = rating};
				fprintf(output_file, "CANCION AGREGADA %i %i\n", i, n_del_disco);
			};
			n_del_disco += 1;
		}

		else if (string_equals(command, "IMPRIMIR-DISCO")) {
			/* Obtenemos la información correspondiente */
			int disc_id;
			fscanf(input_file, "%d", &disc_id);
			int max_rating = 0;
			int song_id_max = 0;
			int min_rating = 100;
			int min_song_id = 0;
			int total_length = 0;
			/* COMPLETAR */
			int song_c = discos[disc_id]->songs_count;
			fprintf(output_file, "ESTADO DISCO %i\n", disc_id);
			fprintf(output_file, "\t\t%i\n", song_c);

			for (int i = 0; i < song_c; i++) {
				if (discos[disc_id]->songs[i].rating > max_rating) {
					max_rating = discos[disc_id]->songs[i].rating;
					song_id_max = i;
				};
				if (discos[disc_id]->songs[i].rating < min_rating) {
					min_rating = discos[disc_id]->songs[i].rating;
					min_song_id = i;
				};
				total_length += discos[disc_id]->songs[i].length;
			};
			fprintf(output_file, "\t\t%i %i\n", max_rating, song_id_max);
			fprintf(output_file, "\t\t%i %i\n", min_rating, min_song_id);
			fprintf(output_file, "\t\t%i\n", total_length);
			fprintf(output_file, "\t\tCANCIONES\n");
			for (int i = 0; i < song_c; i++) {
				fprintf(output_file, "\t\t\t\t%i\n", discos[disc_id]->songs[i].id);
			};
			fprintf(output_file, "FIN ESTADO\n");
		}
		else if (string_equals(command, "IMPRIMIR-CANCION")) {
			/* Obtenemos la información correspondiente */
			int disc_id, song_id;
			fscanf(input_file, "%d %d", &disc_id, &song_id);

			/* COMPLETAR */
			fprintf(output_file, "ESTADO CANCION %i\n", song_id);
			fprintf(output_file, "\t\t%i\n", discos[disc_id]->songs[song_id].length);
			fprintf(output_file, "\t\t%i\n", discos[disc_id]->songs[song_id].rating);
			fprintf(output_file, "FIN ESTADO\n");
		}

		/////////////////////////
		//       Parte B       //
		/////////////////////////

		else if (string_equals(command, "CREAR-BATIPLAYLIST")) {
			/* Obtenemos la información correspondiente */
			int playlist_id;
			fscanf(input_file, "%d", &playlist_id);

			/* COMPLETAR */
			playlists[playlist_id] = malloc(sizeof(Batiplaylists *));
			*playlists[playlist_id] = (Batiplaylists){
			    .id = playlist_id,
				.songs_count = 0,
			    .first = NULL,
			    .last = NULL};
			fprintf(output_file, "BAIPLAYLIST CREATED %i\n", playlists[playlist_id]->id);
		}

		else if (string_equals(command, "AGREGAR-CANCION-BATIPLAYLIST")) {
			int playlist_id, disc_id, song_id;
			fscanf(input_file, "%d %d %d", &playlist_id, &disc_id, &song_id);

			/* COMPLETAR */
			Batiplaylists* playlist = playlists[playlist_id];
			Disco* disco = discos[disc_id];
			Song song = disco-> songs[song_id];
			if (disco->id == song.disc_id) {
				if (playlist->first == NULL) {
					List* list = list_init(song);
					playlist->first = list;
					fprintf(output_file, "NEW SONG ADDED %i %i %i\n", song_id, disc_id, playlist_id);
				}
				else {
					list_append(playlist->first, song);
					fprintf(output_file, "NEW SONG ADDED %i %i %i\n", song_id, disc_id, playlist_id);
				};
				playlist->songs_count += 1;
			}
			else {
				fprintf(output_file, "SONG NOT FOUND\n");
			};
		}

		else if (string_equals(command, "ELIMINAR-CANCION-BATIPLAYLIST")) {
			int playlist_id, disc_id, song_id;
			fscanf(input_file, "%d %d %d", &playlist_id, &disc_id, &song_id);

			/* COMPLETAR */
			Batiplaylists* playlist = playlists[playlist_id];
			List* list = playlist->first;

			if (list->song.id == song_id && list->song.disc_id == disc_id){
				playlist -> first = list->next;
			};
			for (int i = 0; i<N_BATIPLAYLISTS; i++) {
				if (list->next->song.id == song_id && list->next->song.disc_id == disc_id){
					list->next = list->next->next;
					fprintf(output_file, "ELIMINADO %i %i %i\n", song_id, disc_id, playlist_id);
					break;
				}
				list = list->next;
			};
			playlist->songs_count -= 1;

		}

		else if (string_equals(command, "AGREGAR-DISCO-BATIPLAYLIST")) {
			int playlist_id, disc_id;
			fscanf(input_file, "%d %d", &playlist_id, &disc_id);

			/* COMPLETAR */
			Batiplaylists* playlist = playlists[playlist_id];
			for (int i = 0; i < discos[disc_id]->songs_count; i++){
				list_append(playlist->first, discos[disc_id]->songs[i]);
			};
			fprintf(output_file, "AGREGADO %i %i %i\n", discos[disc_id]->songs_count, disc_id, playlist_id);
			playlist->songs_count += discos[disc_id]->songs_count;
		}

		else if (string_equals(command, "PLAY-BATIPLAYLIST")) {
			int playlist_id;
			fscanf(input_file, "%d", &playlist_id);

			/* COMPLETAR */
			Batiplaylists* playlist = playlists[playlist_id];
			List* song_list = playlist->first;
			fprintf(output_file, "ESTADO BATIPLAYLIST %i\n", playlist->id);
			fprintf(output_file, "\t\t%i\n", playlist->songs_count);
			fprintf(output_file, "\t\tCANCIONES\n");
			for (int i = 0; i < playlist->songs_count; i++){
				fprintf(output_file, "\t\t\t\t%i %i\n", song_list->song.id, song_list->song.disc_id);
				song_list = song_list-> next;
			};
			fprintf(output_file, "FIN ESTADO\n");
			
		}

		else if (string_equals(command, "RATE-BATIPLAYLIST")) {
			int playlist_id;
			fscanf(input_file, "%d", &playlist_id);

			/* COMPLETAR */
			int rating = 0;
			Batiplaylists* playlist = playlists[playlist_id];
			List* song_list = playlist->first;
			for (int i = 0; i < playlist->songs_count; i++) {
				rating += song_list->song.rating;
				song_list = song_list->next;
			};
			fprintf(output_file, "BATIPLAYLIST %i: %i",playlist_id, rating/playlist->songs_count);

		}

		/////////////////////////
		//       Parte C       //
		/////////////////////////

		else if (string_equals(command, "ELIMINAR-BATIPLAYLIST")) {
			int playlist_id;
			fscanf(input_file, "%d", &playlist_id);

			/* COMPLETAR */
		}

		else if (string_equals(command, "UNIR-BATIPLAYLIST")) {
			int playlist_id1, playlist_id2;
			fscanf(input_file, "%d %d", &playlist_id1, &playlist_id2);

			/* COMPLETAR */
		}

		else if (string_equals(command, "SPLIT-BATIPLAYLIST")) {
			int playlist_id, new_playlist_id, position;
			fscanf(input_file, "%d %d %d", &playlist_id, &new_playlist_id, &position);

			/* COMPLETAR */
		}

		else if (string_equals(command, "ORDENAR-BATIPLAYLIST")) {
			int playlist_id;
			fscanf(input_file, "%d", &playlist_id);

			/* COMPLETAR */
		}

		else if (string_equals(command, "PURGAR-BATIPLAYLIST")) {
			int playlist_id, rating;
			fscanf(input_file, "%d %d", &playlist_id, &rating);

			/* COMPLETAR */
		}

		/* Leemos la siguiente instrucción */
		fscanf(input_file, "%s", command);
	}

	/////////////////////////////////////
	//        Cerramos archivos        //
	////////////////////////////////////

	fclose(input_file);
	fclose(output_file);

	///////////////////////////////////
	//     Liberamos memoria         //
	///////////////////////////////////

	/* COMPLETAR */
	for (int i = 0; i < N_DISCS; i++) {
		free(discos[i]);
	};

	return 0;
}
