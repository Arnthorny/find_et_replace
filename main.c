#include "main.h"

/**
  *err_prnt - A function that handles error printing.
  *@err_code: Error code.
  *@ptr: Part of error msg to be printed.
  */
void err_prnt(int err_code, __attribute__((unused))void *ptr)
{
	switch (err_code)
	{
		case 97:
			dprintf(2, "Usage: fetr file search_str [replace_str]\n");
			break;
		case 98:
			dprintf(2, "Error: Can't read from file %s\n", (char *) ptr);
			break;
		case 99:
			dprintf(2, "Error: Can't allocate space.\n");
			break;
		case 100:
			dprintf(2, "Error: Can't close file pointer\n");
			break;
		case 101:
			dprintf(2, "Error: Can't create backup file for %s\n", (char *) ptr);
			break;
		case 102:
			dprintf(2, "Error: Can't create search nodes\n");
			break;
	}
	exit(err_code);
}

/**
  *close_fp - A function to close file pointers.
  *@fp: File Pointers.
  *@end: 0 or 1 value to indicate end of program
  */

void close_fp(FILE *fp, int end)
{
	if (end && (fclose(fp) != 0))
		err_prnt(100, fp);
	else if (!end && fp != NULL)
		fclose(fp);
}

/**
 * handle_file_search - Function to delegate file backup and search
 * @fp: File pointer to file to be searched.
 * @fname: Name of File to be searched
 * @head: Pointer to pointer of dll head.
 * @search_str: Searched text.
 * Return: Number of searches found.
 */

int handle_file_search(FILE *fp, char *fname, char *search_str, s_node **head)
{
	int backup_status = 0, i_status = 0, count_nodes = 0;

	backup_status = backup_file(fp, fname);
	if (backup_status != 0)
	{
		close_fp(fp, 0);
		err_prnt(101, fname);
	}

	i_status = insert_srch_nodes(fp, search_str, head);
	if (i_status != 0)
	{
		free_search_list(head);
		close_fp(fp, 0);
		err_prnt(i_status, NULL);
	}
	count_nodes = len_search_list(head);
	printf("%s\n\n", help_str(1));

	if (count_nodes != 1)
		printf("There are %d occurences of `%s`: \n\n", count_nodes, search_str);
	else
		printf("There is %d occurence of `%s`: \n\n", count_nodes, search_str);

	return (count_nodes);
}

/**
 * help_str - Function to return help messages used in program
 * @type: Int flag to determine the type of message to return
 * Return: String containing the help message
 */

char *help_str(int type)
{
	char *help_1 = "fetr: fetr file search_str [replace_str]\n"
		"\tOptions:\n"
		"\t  p - Show previous \tn - Show next \ta - Show all\n"
		"\t  x <text> - Replace all with `text`  \tr <text> - Replace current with `text`\n"
		"\t  q - Quit \t\th - Help \ts - Save changes \tu - Undo replacement\n"
		"\n\tThe `text` argument takes precendence over `replace_str`.\n"
		"\tThe `text` argument, if provided must be quoted.\n"
		"\tIf neither is provided, a blank string is used for replacement.\n"
		"\tA line due for replacement is prefixed with an `r`.\n";

	char *help_2 = "p - Show previous \tn - Show next \ta - Show all\n"
		"x <text> - Replace all with `text`  \tr <text> - Replace current with `text`\n"
		"q - Quit \th - Help \ts - Save changes \tu - Undo replacement\n";

	if (type == 1)
		return (help_1);
	else
		return (help_2);
}


/**
  * main - This program mimics the UNIX shell.
  * @argc: Number of arguments passed in
  * @argv: A NULL-teminated array of strings passed to CLI.
  * Return: Exit status code.
  */
int main(int argc, char *argv[])
{
	char *file_name, *search_str, *lineptr = NULL;
	s_node *head = NULL;
	int node_count = 0;
	FILE *fp;

	/*signal(SIGINT, catch_sigint);*/
	if (argc != 3 && argc != 4)
		err_prnt(97, NULL);
	file_name = argv[1];
	search_str = argv[2];

	fp = fopen(file_name, "r");
	if (fp == NULL)
		err_prnt(98, file_name);

	ret_argv(argv, 0);
	node_count = handle_file_search(fp, file_name, search_str, &head);
	if (node_count > 0)
	{
		print_search_list(&head, search_str, 1);
		handle_input(&lineptr, &head, search_str, fp);
	}

	free(lineptr);
	free_search_list(&head);
	close_fp(fp, 1);
	return (0);
}
