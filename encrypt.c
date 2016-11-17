/*
 * Encrypt a password with an MD5 hash function 
 *
 * Robert Stefanic
 *
 * A program built around the built in crypt function 
 */
#include <stdio.h>
#include <string.h>

#define _XOPEN_SOURCE
#include <unistd.h>

char *crypt(const char *key, const char *salt);

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("**Error: Invalid number of arguments entered.\n");
		printf("\tPlease enter two arguments.\n");
		return 1;
	}

	if (strlen(argv[2]) > 2)
	{
		printf("**Error: Invalid salt entered\n");
		printf("**\tPlease enter only two characters for the salt");
		return 2;
	}

	printf("%s\n", crypt(argv[1], argv[2]));

	return 0;
}
