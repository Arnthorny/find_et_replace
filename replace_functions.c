#include "main.h"

int replace_node(s_node *node, char *replace);
int update_replace_line(s_node *node, char *search);
int det_r_text(char *lptr, char *f_word, ssize_t nchars, char **replace);

/**
 * handle_replace - Function to determine replacement string and handle
 * replacement for search node(s).
 * @lptr: This string/line holds the command to be executed
 * @f_word: Substring of `lptr` containing command and
 * quoted replacement(if any).
 * @head: Double pointer to node(s) to be manipulated
 * @nchars: Number of chars read by getline.
 * @flag: Flag to determine if one node(1) or all nodes(0) are manipulated.
 * Return: 1 for success else 0.
 */

int handle_replace(char *lptr, char *f_word, s_node **head,
		ssize_t nchars, int flag)
{

	char *replacer = NULL;
	int det_status = 0, repl_status;
	s_node *curr_node = NULL;

	det_status = det_r_text(lptr, f_word, nchars, &replacer);
	if (!det_status)
		return (0);

	curr_node = *head;
	do {
		repl_status = replace_node(curr_node, replacer);
		if (!repl_status)
		{
			free(replacer);
			printf("Replacement couldn't be completed\n");
			return (0);
		}
		if (flag == 1)
			break;
		curr_node = curr_node->next;
	} while (curr_node != *head);

	free(replacer);
	return (1);
}

/**
 * replace_node - This function stores the replacement text for a given
 * search node.
 * @node: Node to store replacement string.
 * @replace_str: String to be used for replacement
 * Return: Status code. 1 to indicate success else 0.
 */

int replace_node(s_node *node, char *replace_str)
{
	char *tmp_str = NULL;

	if (replace_str == NULL)
		tmp_str = strdup("");
	else
		tmp_str = strdup(replace_str);
	if (!tmp_str)
		return (0);

	free(node->replace);
	node->replace = tmp_str;

	return (1);
}

/**
 * det_r_text - This function determines the replacement string
 * for search node(s).
 * @lptr: This string/line holds the command to be executed
 * @f_word: Substring of `lptr` containing command and
 * quoted replacement(if any).
 * @nchars: Number of chars read by getline.
 * @replace: Double pointer to store replacement string
 * Return: 1 if valid replacement was found else 0.
 */

int det_r_text(char *lptr, char *f_word, ssize_t nchars, char **replace)
{
	char *replace_text = NULL, *tmp_word = NULL;

	/*Check if given line(`lptr`) contains a replacement string after `f_word`*/
	if ((lptr + nchars) > (f_word + strlen(f_word)))
	{
		tmp_word = extract_word((f_word + strlen(f_word) + 1));
		if (tmp_word)
		{
			replace_text = validate_quotes(tmp_word);
			if (!replace_text)
			{
				printf("Invalid replacement provided\n");
				return (0);
			}
		}
	}
	/*If tmp_word is NULL, it means no replacemnt string was found in given line*/
	/*Check if any was given prior to execution (argv)*/
	if (!tmp_word)
	{
		tmp_word = ret_argv(NULL, 3);
		if (tmp_word)
		{
			replace_text = strdup(tmp_word);
			if (!replace_text)
			{
				perror("handl_replace: ");
				return (0);
			}
		}
		else
			replace_text = NULL;
	}
	*replace = replace_text;
	return (1);
}

/**
 * update_replace_line - This function updates the string stored in `data[1]`
 * pointer of the struct to reflect the replacement line to be used.
 * @node: The node whose line is to be updated.
 * @search: Searched string.
 * Return: Status code. 1 to indicate success else 0.
 */

int update_replace_line(s_node *node, char *search)
{
	char *new_line = NULL;
	int initial_index = 0, final_index = 0,
	    len_new_line = 0, len_search = strlen(search),
	    len_repl = strlen(node->replace),
	    len_old_line = node->data[1] ? strlen(node->data[1]) :
		    strlen(node->data[0]);

	if (node->data[1] == NULL)
	{
		final_index = initial_index = node->start - node->data[0];
		len_new_line = len_old_line - len_search + len_repl + 1;
		new_line = calloc(len_new_line, sizeof(*new_line));
		if (!new_line)
			return (0);
		strncat(new_line, node->data[0], initial_index);
		strcat(new_line, node->replace);
		strcat(new_line, node->start + len_search);
		node->data[1] = new_line;
	}
	else
	{
		initial_index = node->start - node->data[0];
		final_index = initial_index + (len_old_line - strlen(node->data[0]));
		len_new_line = len_old_line - len_search + len_repl + 1;
		new_line = calloc(len_new_line, sizeof(*new_line));
		if (!new_line)
			return (0);
		strncat(new_line, node->data[1], final_index);
		strcat(new_line, node->replace);
		strcat(new_line, node->data[1] + final_index + len_search);
		free(node->data[1]);
		node->data[1] = new_line;
	}
		return (1);
}
