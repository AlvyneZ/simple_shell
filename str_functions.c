#include "shell.h"
#include <stdlib.h>

/**
* _strlen - Gets the length of a string
 * @s: String whose length is required
 * Return: Length of string s
 */
int _strlen(char *s)
{
	int ind;

	for (ind = 0; (*(s + ind) != '\0'); ind++)
	;
	return (ind);
}

/**
 * _strchr - Locates a character in a string
 * @s: String to be searched through
 * @c: Character to be searched for
 * Return: Pointer to first occurence of c or
 *  NULL if c is absent
 */
char *_strchr(char *s, char c)
{
	char *sCurs;

	sCurs = s;
	for (; (*sCurs != '\0'); sCurs++)
	{
		if (*sCurs == c)
			return (sCurs);
	}
	if (c == '\0')
		return (sCurs);
	return (NULL);
}

/**
* _strcpy - Copies a string to another string
 * @dest: Destination to paste string
 * @src: Source string to copy from
 * Return: destination string
 */
char *_strcpy(char *dest, char *src)
{
	char *destCurs, *srcCurs;

	srcCurs = src;
	destCurs = dest;
	for (; (*srcCurs != '\0'); srcCurs++, destCurs++)
		*destCurs = *srcCurs;
	*destCurs = '\0';

	return (dest);
}

/**
 * _strdup - Duplicates a string
 * @str: String to be duplicated
 * Return: a pointer to the duplicated string, or NULL if
 *  it fails or provided string is NULL
 */
char *_strdup(char *str)
{
	char *dup;

	if (str == NULL)
		return (NULL);
	dup = malloc(_strlen(str) + 1);
	if (dup != NULL)
		return (_strcpy(dup, str));
	return (NULL);
}

/**
* _strncmp - Compares two strings upto a certain index
 * @s1: First string
 * @s2: second string
 * @n: number of bytes to compare
 * Return: Lexicographic difference of the strings
 */
int _strncmp(char *s1, char *s2, int n)
{
	int ind;

	for (ind = 0; ((s1[ind]) && (s2[ind]) && (ind < n)); ind++)
	{
		if (s1[ind] - s2[ind])
			return (s1[ind] - s2[ind]);
	}

	if (ind >= n)
		return (0);
	return (s1[ind] - s2[ind]);
}
