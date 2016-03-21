#include <stdio.h>

int main( int argc, char** argv )
{
	puts("Lispy version 0.0.1");
	puts("Press ctrl+c to exit\n");

	auto exit = 0;

	auto inSize = 2048;
	char input[inSize];
	while( exit != 1 )
	{
		fputs("lispy> ", stdout);
		fgets(input, inSize, stdin);
		printf(input);
	}
	return 0;
}
