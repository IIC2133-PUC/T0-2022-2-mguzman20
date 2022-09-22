#include "discos.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
	Batiplaylists** playlists = calloc(N_BATIPLAYLISTS, sizeof(Batiplaylists*));

	// Lectura del número de discos
	int N_DISCS;
	fscanf(input_file, "%d", &N_DISCS);
	Disco** discos = calloc(N_DISCS, sizeof(Disco*));

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

			Song** songs = calloc(capacity, sizeof(Song*));

			for (int i = 0; i < capacity; i++) {
				songs[i] = malloc(sizeof(Song));
				fscanf(input_file, "%i %i", &length, &rating);
				*songs[i] = (Song){.id = i, .disc_id=n_del_disco, .length = length, .rating = rating};
				fprintf(output_file, "CANCION AGREGADA %i %i\n", i, n_del_disco);
			};

			discos[n_del_disco] = malloc(sizeof(Disco));
			*discos[n_del_disco] = (Disco){
			    .id = n_del_disco,
			    .songs_count = capacity,
			    .songs = songs};
			n_del_disco += 1;
		}

		else if (string_equals(command, "IMPRIMIR-DISCO")) {
			/* Obtenemos la información correspondiente */
			int disc_id;
			fscanf(input_file, "%d", &disc_id);
			int max_rating = 0;
			int song_id_max = 0;
			int min_rating = 1000;
			int min_song_id = 0;
			int total_length = 0;
			/* COMPLETAR */
			int song_c = discos[disc_id]->songs_count;
			Disco* disc = discos[disc_id];
			fprintf(output_file, "ESTADO DISCO %i\n", disc_id);
			fprintf(output_file, "\t%i\n", song_c);

			for (int i = 0; i < song_c; i++) {
				if (disc->songs[i]->rating > max_rating) {
					max_rating = disc->songs[i]->rating;
					song_id_max = i;
				};
				if (disc->songs[i]->rating < min_rating) {
					min_rating = disc->songs[i]->rating;
					min_song_id = i;
				};
				total_length += disc->songs[i]->length;
			};

			fprintf(output_file, "\t%i %i\n", max_rating, song_id_max);
			fprintf(output_file, "\t%i %i\n", min_rating, min_song_id);
			fprintf(output_file, "\t%i\n", total_length);
			fprintf(output_file, "\tCANCIONES\n");
			for (int i = 0; i < song_c; i++) {
				fprintf(output_file, "\t\t%i\n", disc->songs[i]->id);
			};
			fprintf(output_file, "FIN ESTADO\n");
		}

		else if (string_equals(command, "IMPRIMIR-CANCION")) {
			/* Obtenemos la información correspondiente */
			int disc_id, song_id;
			fscanf(input_file, "%d %d", &disc_id, &song_id);

			/* COMPLETAR */
			fprintf(output_file, "ESTADO CANCION %i\n", song_id);
			fprintf(output_file, "\t%i\n", discos[disc_id]->songs[song_id]->length);
			fprintf(output_file, "\t%i\n", discos[disc_id]->songs[song_id]->rating);
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
			for (int i = 0; i < N_BATIPLAYLISTS; i++){
				if (playlists[i] == 0) {
					playlists[i] = malloc(sizeof(Batiplaylists));
					*playlists[i] = (Batiplaylists){
						.id = playlist_id,
						.songs_count = 0,
						.first = NULL};
					fprintf(output_file, "BATIPLAYLIST CREATED %i\n", playlists[i]->id);
					break;
				};
			};
			
			
		}

		else if (string_equals(command, "AGREGAR-CANCION-BATIPLAYLIST")) {
			int playlist_id, disc_id, song_id;
			fscanf(input_file, "%d %d %d", &playlist_id, &disc_id, &song_id);

			/* COMPLETAR */
			Batiplaylists* playlist;
			for (int i = 0; i < N_BATIPLAYLISTS; i++) {
				if(playlists[i]!= 0) {
					if (playlists[i]->id == playlist_id) {
						playlist = playlists[i];
						break;
					};
				};
			};
			Disco* disco = discos[disc_id];
			if (disco->songs_count < song_id + 1){
				fprintf(output_file, "SONG NOT FOUND\n");
			}

			else {
				Song* song = disco->songs[song_id];
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
			};
		}

		else if (string_equals(command, "ELIMINAR-CANCION-BATIPLAYLIST")) {
			int playlist_id, disc_id, song_id;
			fscanf(input_file, "%d %d %d", &playlist_id, &disc_id, &song_id);

			/* COMPLETAR */
			Batiplaylists* playlist;
			for (int i = 0; i < N_BATIPLAYLISTS; i++) {
				if(playlists[i]!= 0) {
					if (playlists[i]->id == playlist_id) {
						playlist = playlists[i];
						break;
					};
				};
			};
			List* list = playlist->first;
			
			
			if (!list_find(list, discos[disc_id]->songs[song_id])|| list == NULL){
				fprintf(output_file, "SONG NOT FOUND ON PLAYLIST\n");
			}

			else if (list->song == discos[disc_id]->songs[song_id]){
				playlist->first = list->next;
				playlist->songs_count -= 1;
				fprintf(output_file, "ELIMINADO %i %i %i\n", song_id, disc_id, playlist_id);
			}
			else {
				while (list->next){
					if (discos[disc_id]->songs[song_id] == list->next->song){
						List* list_e = list->next;
						list->next = list->next->next;
						free(list_e);
						playlist->songs_count -= 1;
						fprintf(output_file, "ELIMINADO %i %i %i\n", song_id, disc_id, playlist_id);
					};
					list = list->next;
				};
			};
		}

		else if (string_equals(command, "AGREGAR-DISCO-BATIPLAYLIST")) {
			int playlist_id, disc_id;
			fscanf(input_file, "%d %d", &playlist_id, &disc_id);

			/* COMPLETAR */
			Batiplaylists* playlist;
			int canciones_agregadas = 0;
			Disco* disco = discos[disc_id];
			for (int i = 0; i < N_BATIPLAYLISTS; i++) {
				if(playlists[i]!= 0) {
					if (playlists[i]->id == playlist_id) {
						playlist = playlists[i];
						break;
					};
				};
			};
			
			List* list = playlist->first;
		
			for (int i = 0; i < disco->songs_count; i++){
				if (list == NULL){
					list = list_init(disco->songs[i]);
					playlist->first = list;
					canciones_agregadas += 1;
				}
				else if (!list_find(list, disco->songs[i])){
					list_append(list, disco->songs[i]);
					canciones_agregadas += 1;
				};
				
			};
			fprintf(output_file, "AGREGADO %i %i %i\n", canciones_agregadas, disc_id, playlist_id);
			playlist->songs_count += canciones_agregadas;
		}

		else if (string_equals(command, "PLAY-BATIPLAYLIST")) {
			int playlist_id;
			fscanf(input_file, "%d", &playlist_id);

			/* COMPLETAR */
			Batiplaylists* playlist;
			for (int i = 0; i < N_BATIPLAYLISTS; i++) {
				if(playlists[i]!= 0) {
					if (playlists[i]->id == playlist_id) {
						playlist = playlists[i];
						break;
					};
				};
			};
			
			List* song_list = playlist->first;
			fprintf(output_file, "ESTADO BATIPLAYLIST %i\n", playlist->id);
			fprintf(output_file, "\t%i\n", playlist->songs_count);
			fprintf(output_file, "\tCANCIONES\n");
			for (int i = 0; i < playlist->songs_count; i++){
				fprintf(output_file, "\t\t%i %i\n", song_list->song->id, song_list->song->disc_id);
				song_list = song_list->next;
			};
			fprintf(output_file, "FIN ESTADO\n");
			
		}

		else if (string_equals(command, "RATE-BATIPLAYLIST")) {
			int playlist_id;
			fscanf(input_file, "%d", &playlist_id);

			/* COMPLETAR */
			float rating = 0;
			Batiplaylists* playlist;
			for (int i = 0; i < N_BATIPLAYLISTS; i++) {
				if(playlists[i]!= 0) {
					if (playlists[i]->id == playlist_id) {
						playlist = playlists[i];
						break;
					};
				};
			};
			
			List* song_list = playlist->first;
			for (int i = 0; i < playlist->songs_count; i++) {
				rating += song_list->song->rating;
				song_list = song_list->next;
			};
			rating = rating/playlist->songs_count;
			fprintf(output_file, "BATIPLAYLIST %i: %.2f\n",playlist_id, rating);

		}

		/////////////////////////
		//       Parte C       //
		/////////////////////////

		else if (string_equals(command, "ELIMINAR-BATIPLAYLIST")) {
			int playlist_id;
			fscanf(input_file, "%d", &playlist_id);

			/* COMPLETAR */
			Batiplaylists* playlist;
			int x = 0;
			for (int i = 0; i < N_BATIPLAYLISTS; i++) {
				if(playlists[i]!= 0) {
					if (playlists[i]->id == playlist_id) {
						playlist = playlists[i];
						x = i;
						break;
					};
				};
			};
			fprintf(output_file, "BATIPLAYLIST DELETED %i %i\n", playlist_id, playlist->songs_count);
			if (playlists[x]->first != NULL){
				list_destroy(playlists[x]->first);
			};
			memset(playlists[x], 0, sizeof(Batiplaylists));
		}

		else if (string_equals(command, "UNIR-BATIPLAYLIST")) {
			int playlist_id1, playlist_id2;
			fscanf(input_file, "%d %d", &playlist_id1, &playlist_id2);

			/* COMPLETAR */
			Batiplaylists* playlist1;
			Batiplaylists* playlist2;
			int x = 0;
			for (int i = 0; i < N_BATIPLAYLISTS; i++) {
				if( playlists[i]!= 0 ) {
					if (playlists[i]->id == playlist_id1) {
						playlist1 = playlists[i];
					}
					else if (playlists[i]->id == playlist_id2){
						playlist2 = playlists[i];
						x = i;
				};
			};
			};
			List* list = playlist2 ->first;
			for (int i = 0; i <playlist2->songs_count;i++){
				Song* song = list->song;
				if(!list_find(playlist1->first, song)){
					list_append(playlist1->first, song);
					playlist1 -> songs_count += 1;
				};
				list = list->next;
			};
			
			if (playlists[x]->first != NULL){
				list_destroy(playlists[x]->first);
			};
			memset(playlists[x], 0, sizeof(Batiplaylists));
			fprintf(output_file, "JOINED %i AND %i\n", playlist_id1, playlist_id2);
		}

		else if (string_equals(command, "SPLIT-BATIPLAYLIST")) {
			int playlist_id, new_playlist_id, position;
			fscanf(input_file, "%d %d %d", &playlist_id, &new_playlist_id, &position);

			/* COMPLETAR */
			Batiplaylists* playlist;
			for (int i = 0; i < N_BATIPLAYLISTS; i++) {
				if(playlists[i]!= 0) {
					if (playlists[i]->id == playlist_id) {
						playlist = playlists[i];
						break;
					};
				};
			};

			List* nodo = playlist->first;
			for (int i = 0; i <position - 1;i++)
			{
				nodo = nodo->next;
			}

			for (int i = 0; i <N_BATIPLAYLISTS; i++){
				if (playlists[i] == 0)
				{
					playlists[i] = malloc(sizeof(Batiplaylists));
					*playlists[i] = (Batiplaylists){
					.id = new_playlist_id,
					.songs_count = playlist->songs_count - position,
					.first = nodo->next};
				};
				
			}

			nodo->next = NULL;
			playlist->songs_count = position;
			
		}

		else if (string_equals(command, "ORDENAR-BATIPLAYLIST")) {
			int playlist_id;
			fscanf(input_file, "%d", &playlist_id);

			/* COMPLETAR */
		}

		else if (string_equals(command, "PURGAR-BATIPLAYLIST")) {
			int playlist_id, m_rating;
			fscanf(input_file, "%d %d", &playlist_id, &m_rating);

			/* COMPLETAR */
			Batiplaylists* playlist;
			int songs_purged = 0;
			for (int i = 0; i < N_BATIPLAYLISTS; i++) {
				if(playlists[i]!= 0) {
					if (playlists[i]->id == playlist_id) {
						playlist = playlists[i];
						break;
					};
				};
			};
			List* list = playlist->first;
			List* prev;

			for (int i = 0; i <playlist->songs_count; i++){
				if (list == NULL){
					break;
				}
				else if (playlist->first->song->rating < m_rating){
					playlist->first = playlist->first->next;
					free(list);
					list = playlist->first;
					songs_purged += 1;
			
				}
				else if (list->song->rating < m_rating){
					prev->next = list->next;
					free(list);
					list = prev->next;
					songs_purged += 1;
				}
				else {
					prev = list;
					list = list->next;
				};
				
			}
			playlist ->songs_count -= songs_purged;
			fprintf(output_file, "BATIPLAYLIST PURGED %i %i\n", playlist_id, songs_purged);
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
		if(discos[i] != 0) {
			for (int j = 0; j < discos[i]->songs_count; j+=1){
				free(discos[i]->songs[j]);
			};
			free(discos[i]->songs);
			free(discos[i]);
		};
		
	};
	free(discos);

	for (int i = 0; i <N_BATIPLAYLISTS;i++){
		if (playlists[i] != 0)
		{
			if (playlists[i]->first != NULL){
				list_destroy(playlists[i]->first);
			};
			free(playlists[i]);
		}
		
		
	};
	free(playlists);


	return 0;
}
