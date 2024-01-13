#include "main.h"

/**
 * backup_file - A function that backups a file content
 * into a `filename`.bak file
 * @filename: The name of the file to be backed up.
 * @fp_from: File pointer to file for backup.
 * Return: 0 if function runs successfully else 1.
 */

int backup_file(FILE *fp_from, char *filename)
{
	char buf[2048] = {0}, *b_file_name = NULL, *b_file_sfx = ".bak";
	size_t r = 0, w = 0, len_bfname = 0;
	FILE *b_file = NULL;

	len_bfname = strlen(filename) + strlen(b_file_sfx) + 1;
	b_file_name = calloc(len_bfname, sizeof(*b_file_name));
	if (!b_file_name)
		return (1);
	strcat(b_file_name, filename);
	strcat(b_file_name, b_file_sfx);

	b_file = fopen(b_file_name, "w");
	free(b_file_name);
	if (!b_file)
		return (1);
	do {
		r = fread(buf, sizeof(*buf), sizeof(buf), fp_from);
		if (ferror(fp_from))
		{
			close_fp(fp_from, 0);
			close_fp(b_file, 0);
			err_prnt(98, filename);
		}
		w = fwrite(buf, sizeof(*buf), r, b_file);
		if (ferror(b_file) || w != r)
		{
			close_fp(fp_from, 0);
			close_fp(b_file, 0);
			err_prnt(101, filename);
		}
		if (feof(fp_from))
			break;

	} while (r > 0);
	close_fp(b_file, 1);
	return (0);
}

/**
 * scan_entire_line - This function scans a given line to check/insert multiple
 * occurences of the searched string in the line.
 * @head: Pointer to pointer of dll head.
 * @line_dup: String containing a duplicate of the current line.
 * @srch: Searched text.
 * @lnum: The current line number.
 * Return: Pointer to node containing last occurence of
 * `srch` in given `line_dup`.
 */
s_node *scan_entire_line(s_node **head, char *line_dup, char *srch, int lnum)
{
	s_node *tmp = NULL;
	char *fnd_str = NULL, *srch_line = line_dup;
	char **ptr_line_dup = NULL;
	int srch_str_len = strlen(srch);

	ptr_line_dup = malloc(sizeof(*ptr_line_dup) * 2);
	if (!ptr_line_dup)
		return (NULL);
	ptr_line_dup[0] = line_dup;
	ptr_line_dup[1] = NULL;

	fnd_str = strstr(srch_line, srch);
	do {
		tmp = insert_node(head, ptr_line_dup, lnum, fnd_str);
		if (!tmp)
			return (NULL);
		srch_line = fnd_str + srch_str_len;
		fnd_str = strstr(srch_line, srch);
	} while (fnd_str);

	return (tmp);
}

/**
 * insert_srch_nodes - A function that inserts the searched node
 * into a circular dll.
 * @fp: File pointer to file to be searched.
 * @search_str: Searched text.
 * @head: Pointer to pointer of dll head.
 * Return: 0 if function runs successfully else 1.
 */
int insert_srch_nodes(FILE *fp, char *search_str, s_node **head)
{
	char *lineptr = NULL, *data = NULL, *tmp_fnd_str = NULL;
	size_t n = 0;
	s_node *tmp = NULL;
	int line_num = 0;
	ssize_t line_size = 0;

	rewind(fp);
	errno = 0;
	line_size = getline(&lineptr, &n, fp);
	while (line_size != -1)
	{
		line_num++;
		tmp_fnd_str = strstr(lineptr, search_str);
		if (tmp_fnd_str)
		{
			data = strdup(lineptr);
			tmp = scan_entire_line(head, data, search_str, line_num);
			if (!tmp)
			{
				free(lineptr);
				return (99);
			}
		}
		errno = 0;
		line_size = getline(&lineptr, &n, fp);
	}
	free(lineptr);
	if (errno != 0)
		return (102);
	return (0);
}
