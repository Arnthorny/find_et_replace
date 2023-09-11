#ifndef _MAIN_H_
#define _MAIN_H_

#define _GNU_SOURCE
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define UNUSED __attribute__((unused))

/**
 * struct cdll_s - circular doubly linked list
 * @data: Pointer to array of two strings. The first
 * containing the matching line, the second containing it's
 * replacement.
 * @start: Pointer to start of searched string in data[0].
 * @replace: Malloc'd string containing search replacement.
 * @line: line number
 * @prev: pointer to the previous node
 * @next: pointer to the next node
 *
 * Description: Circular doubly linked list Search node structure
 * Double pointer were used for the `data` member to account for lines
 * where the searched string occurs more than once.
 * This double pointer is then shared across search nodes
 * with the same line (string pointed to by data[0])
 * and same replacement (data[1]).
 *
 */
typedef struct cdll_s
{
	char **data;
	char *start;
	char *replace;
	int line;
	struct cdll_s *prev;
	struct cdll_s *next;
} s_node;

void print_search_list_rev(s_node **);
int cdlist_len(s_node **);
s_node *insert_node(s_node **, char **, int, char *);
void free_search_list(s_node **);
void print_search_list(s_node **, char *, int);
void print_search_list_rev(s_node **);
int len_search_list(s_node **);
char *color_str(s_node *, char *);
void handle_input(char **lptr, s_node **h, char *srch, FILE *fp);
int backup_file(FILE *fp_from, char *filename);
int insert_srch_nodes(FILE *fp, char *search_str, s_node **head);
void err_prnt(int err_code, __attribute__((unused))void *ptr);
void close_fp(FILE *fp, int end);
char *help_str(int type);
char *ret_argv(char **argv, int idx);
char *extract_word(char *s);
char *validate_quotes(char *s);
int handle_replace(char *lptr, char *f_word, s_node **head,
		ssize_t nchars, int count);
int save_changes(s_node **head, char *search, FILE *fp);
int update_replace_line(s_node *node, char *search);
void undo_replace(s_node *node);

#endif /*_MAIN_H_*/
