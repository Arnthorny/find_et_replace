#include "main.h"

/**
 * delegate_fn - This function selects the function to execute
 * based on the user provided command.
 * @h: Pointer to pointer of dll head.
 * @curr_node: Pointer to pointer of current search node.
 * @lptr: This string/line holds the command to be executed
 * @nchars: Number of chars read by getline.
 * @srch: Searched text.
 * @fp: FIle pointer to original file.
 * Return: Flag to indicate end(0) or continuation(1) of program.
 */
int delegate_fn(s_node **h, s_node **curr_node,
		char *lptr, ssize_t nchars, char *srch, FILE *fp)
{
	char *f_word = lptr[0] == '\n' ? lptr : extract_word(lptr);
	char f_char = f_word && strlen(f_word) == 1 ? f_word[0] : '\0';
	int r_status = 0, s_status = 0;

	switch (f_char)
	{
		case '\n':
			return (1);
		case 'p':
			*curr_node = (*curr_node)->prev;
			print_search_list(curr_node, srch, 1);
			break;
		case 'n':
			*curr_node = (*curr_node)->next;
			print_search_list(curr_node, srch, 1);
			break;
		case 'a':
			print_search_list(h, srch, 0);
			break;
		case 'r':
			r_status = handle_replace(lptr, f_word, curr_node, nchars, 1);
			printf("The replacer is now: %s\n", (*curr_node)->replace);
			if (r_status)
				delegate_fn(h, curr_node, "n", nchars, srch, fp);
			break;
		case 'x':
			r_status = handle_replace(lptr, f_word, curr_node, nchars, 0);
			if (r_status)
				delegate_fn(h, curr_node, "n", nchars, srch, fp);
			break;
		case 'h':
			printf("%s\n", help_str(2));
			break;
		case 's':
			s_status = save_changes(h, srch, fp);
			if (s_status)
				printf("All changes successfully applied!\n");
			return (0);
		case 'q':
			printf("Quitting...\n");
			return (0);
		default:
			printf("Undefined command: '%s'.  Try 'h'.\n", lptr);
	}
	return (1);
}

/**
  * handle_input - This function loops to take in user input
  * @lptr: This holds the string(line) of input.
  * @h: Pointer to pointer of dll head.
  * @fp: File pointer to original file.
  * @srch: Searched text.
  * Descripion: TODO - Implement input functionality using readline next.
  */

void handle_input(char **lptr, s_node **h, char *srch, FILE *fp)
{
	ssize_t nchars = 0;
	char *prompt = "~ ", *prev_cmd = strdup("\n"), *tmp_s = NULL;
	size_t n = 0;
	int exec_status = 0;
	s_node *curr_node = *h;

	if (!prev_cmd)
	{
		perror("handle_input");
		return;
	}
	while (1)
	{
		printf("%s", prompt);
		nchars = getline(lptr, &n, stdin);
		if (nchars == -1)
		{
			perror("handle_input");
			break;
		}
		if ((*lptr)[0] == '\n')
		{
			tmp_s = strdup(prev_cmd);
			if (!tmp_s)
			{
				perror("handle_input");
				break;
			}
			printf("The previous command was %s\n", tmp_s);
			exec_status = delegate_fn(h, &curr_node, tmp_s, strlen(tmp_s), srch, fp);
			free(tmp_s);
		}
		else
		{
			free(prev_cmd);
			prev_cmd = strdup(*lptr);
			if (!prev_cmd)
			{
				perror("handle_input");
				break;
			}
			exec_status = delegate_fn(h, &curr_node, *lptr, nchars, srch, fp);
		}
		if (exec_status == 0)
			break;
	}
	free(prev_cmd);
}
