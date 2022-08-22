#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Retorna true si ambos string so iguales */
typedef struct song {
	int length;
	int rating;
} Song;

typedef struct disco {
	int songs_count;
	int id;
	Song* songs;
} Disco;


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

	// Lectura del número de discos
	int N_DISCS;
	fscanf(input_file, "%d", &N_DISCS);

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
			for (int i = 0; i < N_DISCS; i++) {
				Disco disco = {
					.id = i,
					.songs_count = capacity,
					.songs = calloc(capacity, sizeof(Song)),
				};

				fscanf(input_file, "%i", &length);
				fscanf(input_file, "%i", &rating);

				for (int j = 0; j < capacity; j++){
					disco.songs[i] = (Song){.length = length, .rating = rating};
					printf("CANCION AGREGADA %i %i\n", length, rating);
				}
				
			}
	}

	else if (string_equals(command, "ELIMINAR-CANCION")) {
		/* Obtenemos la información de la canción */
		int disc_id, song_id;
		fscanf(input_file, "%d %d", &disc_id, &song_id);

		/* COMPLETAR */
	}

	else if (string_equals(command, "IMPRIMIR-DISCO")) {
		/* Obtenemos la información correspondiente */
		int disc_id;
		fscanf(input_file, "%d", &disc_id);

		/* COMPLETAR */
	}
	else if (string_equals(command, "IMPRIMIR-CANCION")) {
		/* Obtenemos la información correspondiente */
		int disc_id, song_id;
		fscanf(input_file, "%d %d", &disc_id, &song_id);

		/* COMPLETAR */
	}

	/////////////////////////
	//       Parte B       //
	/////////////////////////

	else if (string_equals(command, "CREAR-BATIPLAYLIST")) {
		/* Obtenemos la información correspondiente */
		int playlist_id;
		fscanf(input_file, "%d", &playlist_id);

		/* COMPLETAR */
	}

	else if (string_equals(command, "AGREGAR-CANCION-BATIPLAYLIST")) {
		int playlist_id, disc_id, song_id;
		fscanf(input_file, "%d %d %d", &playlist_id, &disc_id, &song_id);

		/* COMPLETAR */
	}

	else if (string_equals(command, "ELIMINAR-CANCION-BATIPLAYLIST")) {
		int playlist_id, song_id;
		fscanf(input_file, "%d %d", &playlist_id, &song_id);

		/* COMPLETAR */
	}

	else if (string_equals(command, "AGREGAR-DISCO-BATIPLAYLIST")) {
		int playlist_id, disc_id;
		fscanf(input_file, "%d %d", &playlist_id, &disc_id);

		/* COMPLETAR */
	}

	else if (string_equals(command, "PLAY-BATIPLAYLIST")) {
		int playlist_id;
		fscanf(input_file, "%d", &playlist_id);

		/* COMPLETAR */
	}

	else if (string_equals(command, "RATE-BATIPLAYLIST")) {
		int playlist_id;
		fscanf(input_file, "%d", &playlist_id);

		/* COMPLETAR */
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

return 0;
}
