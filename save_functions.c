#include "main.h"

/**
 * update_all_replacements - This functions updates every search node with
 * its corresponding replacement line(string).
 * @head: Double pointer to head of search doubly linked list.
 * @search: Searched string.
 * Return: 1 to indicate success else 0.
 */

int update_all_replacements(s_node **head, char *search)
{
	s_node *curr_node = NULL, *tmp = NULL;
	int repl_status = 0;

	curr_node = (*head);
	do {
		tmp = curr_node->next;
		if (curr_node->replace)
		{
			repl_status = update_replace_line(curr_node, search);
			if (!repl_status)
				return (0);
		}
		curr_node = tmp;
	} while (curr_node != *head);

	return (1);
}

/**
 * return_node - This function traverses through the search nodes
 * @node: The starting point to begin traversal
 * @head: Pointer to pointer to head of search list
 * @lnum: Line number of file being read from.
 * Return: Corresponding node if found or NULL
 * if not found or end of list is reached.
 *
 * Description: It checks the search list (circular dll) to see
 * if a node corresponds to the line number of the file being read from.
 */

s_node *return_node(s_node **node, s_node **head, int lnum)
{
	s_node *curr_node = NULL, *tmp = NULL;

	if (!*node)
		return (NULL);

	curr_node = (*node);
	do {
		tmp = curr_node->next;
		if (curr_node->replace && lnum == curr_node->line)
		{
			*node = curr_node;
			return (curr_node);
		}
		else if (curr_node->line > lnum)
		{
			*node = curr_node;
			return (NULL);

		}
		else if (tmp == *head)
			*node = NULL;
		curr_node = tmp;
	} while (curr_node != *head);

	return (NULL);
}


/**
 * save_change_to_file - This function writes all replacements to file
 * @head: Pointer to pointer to head of search node's list
 * @fp_orig: File pointer to original file.
 * Return: 1 to indicate success else 0.
 */

int save_change_to_file(s_node **head, FILE *fp_orig)
{
	s_node *node = (*head), *c_node = NULL;
	char *orig_file = ret_argv(NULL, 1), *bak_ext = ".bak",
	     *bak_name = NULL, *lptr = NULL;
	int status = 1;
	size_t bak_name_len = 0, n = 0, lnum = 0;
	ssize_t nchars = 0;
	FILE *fp_file = NULL, *fp_bak_file = NULL;

	bak_name_len = strlen(orig_file) + strlen(bak_ext) + 1;
	bak_name = calloc(sizeof(*bak_name), bak_name_len);
	if (!bak_name)
		return (0);
	strcpy(bak_name, orig_file);
	strcat(bak_name, bak_ext);

	fp_bak_file = fopen(bak_name, "r");
	free(bak_name);
	if (fp_bak_file == NULL)
		return (0);
	fp_file = freopen(NULL, "w", fp_orig);
	if (fp_file == NULL)
		status = 0;

	while (status)
	{
		lnum++;
		nchars = getline(&lptr, &n, fp_bak_file);
		if (feof(fp_bak_file))
			break;
		else if (ferror(fp_bak_file))
		{
			status = 0;
			break;
		}
		c_node = return_node(&node, head, lnum);
		if (c_node)
			fwrite(c_node->data[1], sizeof(char), strlen(c_node->data[1]), fp_file);
		else
			fwrite(lptr, sizeof(char), nchars, fp_file);
		/*TODO: Check that all bytes are written*/
	}
	free(lptr);
	fclose(fp_bak_file);
	return (status);
}

/**
 * save_changes - This function serves as an entry point
 * to functions that apply replacements to each
 * search node and write these changes to the file.
 * @head: Pointer to pointer to head of search node doubly linked list.
 * @search: Searched string.
 * @fp: File pointer to original file.
 * Return: 1 to indicate successful execution else 0
 */

int save_changes(s_node **head, char *search, FILE *fp)
{
	int update_status = 0, file_save_s = 0;

	update_status = update_all_replacements(head, search);
	if (!update_status)
	{
		printf("Replacements could not be completed \n");
		return (0);
	}
	file_save_s = save_change_to_file(head, fp);
	if (!file_save_s)
	{
		printf("Changes could not be written to file. \n");
		return (0);
	}

	return (1);
}
