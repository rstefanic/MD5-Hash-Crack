/*
 * MD5 Hash Crack
 *
 * Robert Stefanic <rps>
 *
 * CS50 pset 2
 */

#include <stdio.h>
#include <string.h>

#define _XOPEN_SOURCE
#include <unistd.h>

#define MAX_LENGTH 8

char *crypt(const char *key, const char *salt);
int dictionary(char *salt, char *encryption);
int brute_force(char *salt, char *encryption);
int cycle_through_letters(int position, char *test_string, char *salt, char *encryption);

int main(int argc, char *argv[])
{
	// Check to make sure there's only one argument given
	if (argc != 2)
	{
		printf("**Error: Invalid number of arguments entered.\n");
		printf("\tPlease enter only one argument.\n");
		return 1;
	}

	// Point to the encrypted string, create the salt 
	char *encryption = argv[1];
	char salt[2];
	
	// Grab the salt from the encrypted string
	salt[0] = encryption[0];
	salt[1] = encryption[1];

	// Create length and decrypted string variable
	unsigned length = strlen(argv[1]);
	char decrypted[length];

	/* Check the dictionary words first. If the dicitionary()
	 * function returns a 0, then exit the program. If the 
	 * function returns a 1, then run the brute_force()
	 * function to see if word can be found by going through 
	 * letter by letter */
	
	if (dictionary(salt, argv[1]) == 0)
	{
		return 0;
	}
	else
	{
		printf("No match found with dictionary words found.\nBrute force testing...\n");
		return brute_force(salt, argv[1]);
	}

}

int dictionary(char *salt, char *encryption)
{

	// Open the file, create the line and len variable
	FILE *dict;
	dict=fopen("/usr/share/dict/words", "r");
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	
	printf("Checking dictionary words...\n");

	/* Go through the dictionary word for word -- if the encrypted
	 * dictionary word and salt match, then return the 
	 * dictionary word that was passed to the crypt function */		
	
	while ((read = getline(&line, &len, dict)) != -1)
	{	

		// Copy the string from the file -- cut off the new line
		char current_line[strlen(line)];
		register int i = 0;
		
		while (line[i] != '\n')
		{
			current_line[i] = line[i];
			i++;
		
		}

		// End the string where the newline would be
		current_line[i] = '\0';
			
		/* If the encrypted word and the entered encryption match
		 * display the word and return 0 to exit. */

		if (strcmp(encryption, crypt(current_line, salt)) == 0)
		{
			fclose(dict);
			printf("%s\n", line);
			return 0;
		}
	} 

	// If no matches were found, return 1	
	fclose(dict);
	return 1;
}

int brute_force(char *salt, char *encryption)
{
	
	int i = 0;

	// Control the length of the string, and go through the possibilites	
	while (i < MAX_LENGTH)
	{	
		char test_string[i+2];
		test_string[i+1] = '\0';
		if (cycle_through_letters(i, test_string, salt, encryption) == 0)
		{
			return 0;
		}
		i++;
				
	}
	
	return 1;
}


int cycle_through_letters(int position, char *test_string, char *salt, char *encryption)
{
	char letters[] = 	"abcdefghijklmnopqrstuvwxyz"
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"0123456789./";
	
	int length = strlen(letters);
	register int j;

	// Go through each letter
	for (j = 0; j < length; j++)
	{
		// Change one letter
		test_string[position] = letters[j];
		
		/* If the position is not the 0 index, 
		 * then reenter the loop in the previous
		 * index to test every possible letter 
		 * for every possible index that came before it */
  
		if (position > 0)
		{
			if (cycle_through_letters(position - 1, test_string, salt, encryption) == 0)
			{
				return 0;
			}
			
		}

		// Compare the string each time to see if it's the encrypted string matches
		if (strcmp(encryption, crypt(test_string, salt)) == 0)
		{
			printf("%s\n", test_string);
			return 0;
		}
	} 
 
	printf("\nNo matches found");	
	return 1;
}

