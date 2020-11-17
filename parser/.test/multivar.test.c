#include "../multivar.c"

#define SRC_size 10

#include <stdio.h>
extern int main()
{
	char** argarray;

	argarray = malloc((SRC_size + 1) * sizeof(char*));
	for (int i=0; i<SRC_size; i++) {
		argarray[i] = malloc(2 * sizeof(char));
		argarray[i][0] = '0' + i;
		argarray[i][1] = '\0';
	}
	argarray[SRC_size] = NULL;

	char* argv = "a\0bb\0ccc\0dddd\0eeeee\0ffffff";
	argarray = reinsert_multivar(argarray, 9, argv, 6);
	for(int i=0; i<(SRC_size + 6); i++) {
		printf("[%i] %s\n", i, argarray[i]);
	}

	for (char** c=argarray; *c; c++)
		free(*c);
	free(argarray);
}
