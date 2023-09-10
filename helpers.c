#include "main.h"


/**
 * ret_argv - This function returns the strings contained in argv
 * @argv: A NULL-teminated array of strings passed to CLI.
 * @idx: Index for string to be returned
 * Return: String corresponding to given index.
 */

char *ret_argv(char **argv, int idx)
{
	static char **argv_stor;

	if (argv)
	{
		argv_stor = argv;
		idx = idx;
	}

	return (argv_stor[idx]);
}


/**
 * validate_quotes - Function to check if string is properly quoted
 * single or double quotes are allowed.
 * @s: String to check
 * Return: Malloc'd raw string (without quotes) or NULL if not properly quoted.
 */

char *validate_quotes(char *s)
{
	char *word = NULL;
	int len_s = 0;

	if (!s)
		return (NULL);

	len_s = strlen(s);

	if (len_s >= 2 && ((s[0] == '"' && s[len_s - 1] == '"') ||
			(s[0] == '\'' && s[len_s - 1] == '\'')))
	{
		word = strndup(&s[1], len_s - 2);
		if (!word)
			return (NULL);
	}

	else
		return (NULL);

	return (word);
}

/**
 * extract_word - Function to get "words" from given string
 * @s: String to extract words from
 * Return: First word seen or NULL if no words found.
 */

char *extract_word(char *s)
{
	char *word = NULL;
	int i = 0;

	while (s && s[i])
	{
		/*Check if `word` is quoted and s[i] is not a newline.*/
		/*Or that `s[i]` is not a whitespace*/
		if ((s[i] != '\n' && word && (word[0] == '\'' || word[0] == '"')) ||
				(s[i] != ' ' && s[i] != '\t' && s[i] != '\n'))
		{
			if (!word)
				word = &s[i];
		}
		else if (word)
		{
			s[i] = '\0';
			return (word);
		}
		i++;
	}

	return (word);
}

/**
 * color_str - Add color to searched text for a given node.
 * @node: Node containing the searched line.
 * @search: Searched text.
 * Return: Alloc'd string with search text colored
 */
char *color_str(s_node *node, char *search)
{
	char *new_str = NULL;
	char *clr_code = "\033[1;31m";
	char *reset_code = "\033[0m";
	size_t len_new_str = strlen(clr_code) + strlen(reset_code) +
		strlen(node->data[0]) + 1;

	new_str = calloc(sizeof(*new_str), len_new_str);
	if (!new_str)
		return (NULL);
	strncat(new_str, node->data[0], node->start - node->data[0]);
	strcat(new_str, clr_code);
	strcat(new_str, search);
	strcat(new_str, reset_code);
	strcat(new_str, node->start + strlen(search));

	return (new_str);
}
