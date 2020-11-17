#include <stdio.h>

extern int main(int argc, char** argv)
{
	printf("Argc: %d\n", argc);
	for (int i=0; i<argc; i++)
		printf("[%i] %s\n", i, argv[i]);
}