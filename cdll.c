#include "main.h"

/**
 * insert_node - Function to insert node to end of a circular
 * doubly linked list.
 * @head: Pointer to pointer of dll head.
 * @data: Pointer to string to be inserted into list.
 * @start: Pointer to start of searched string in data.
 * @line: Line number of string.
 *
 * Return: Pointer to newly inserted node.
 */
s_node *insert_node(s_node **head, char **data, int line, char *start)
{
	s_node *node = NULL, *tmp = NULL;

	if (!head || !*data)
		return (NULL);

	node = malloc(sizeof(*node));
	if (!node)
		return (NULL);

	node->data = data;
	node->line = line;
	node->start = start;
	node->replace = NULL;

	if (!*head)
	{
		node->prev = node;
		node->next = node;
		*head = node;
	}
	else
	{
		tmp = (*head)->prev;
		node->next = *head;
		node->prev = tmp;
		tmp->next = node;
		(*head)->prev = node;
	}
	return (node);
}

/**
 * print_search_list - Function to print search nodes of circular
 * doubly linked list.
 * @head: Pointer to pointer to head/node of circular dll.
 * @search: Searched text.
 * @flag: Flag to indicate if single node(1) or entire list(0) is printed.
 */
void print_search_list(s_node **head, char *search, int flag)
{
	s_node *curr_node = NULL;
	char *tmp_str = NULL;

	if (!head || !*head)
		return;

	curr_node = *head;

	do {
		tmp_str = color_str(curr_node, search);
		if (tmp_str)
		{
			if (curr_node->replace)
				printf("Line %d [r]: %s", curr_node->line, tmp_str);
			else
				printf("Line %d: %s", curr_node->line, tmp_str);
		}
		else
		{
			if (curr_node->replace)
				printf("Line %d [r]: %s", curr_node->line, curr_node->data[0]);
			else
				printf("Line %d: %s", curr_node->line, curr_node->data[0]);
		}
		free(tmp_str);
		if (flag == 1)
			break;
		curr_node = curr_node->next;
	} while (curr_node != *head);
}

/**
 * free_search_list - Function to free all nodes of a circular
 * doubly linked list.
 * @head: Pointer to pointer to head of circular dll.
 */
void free_search_list(s_node **head)
{
	s_node *curr_node = NULL, *tmp = NULL;

	if (!head || !*head)
		return;

	curr_node = (*head);
	do {
		tmp = curr_node->next;
		/* Only free the data pointer of a node if it's the last/only one in list*/
		/* Or it belongs to the head node.*/
		if (tmp == *head || (curr_node->line != tmp->line))
		{
			free(curr_node->data[0]);
			free(curr_node->data[1]);
			free(curr_node->data);
		}
		free(curr_node->replace);
		free(curr_node);
		curr_node = tmp;
	} while (curr_node != *head);
}

/**
 * len_search_list- Function to measure the length of a circular dll.
 * @head: Pointer to pointer to head of circular dll.
 * Return: Length of DLl.
 */
int len_search_list(s_node **head)
{
	int length = 0;
	s_node *curr_node = NULL;

	if (!head || !*head)
		return (0);

	curr_node = *head;

	do {
		length++;
		curr_node = curr_node->next;
	} while (curr_node != *head);

	return (length);
}

/**
 * delete_cdnode - Function to delete a node from a circular
 * doubly linked list.
 * @head: Pointer to pointer to head of circular dll.
 * @node: Pointer to node to be deleted.
 */
void delete_cdnode(s_node **head, s_node *node)
{
	s_node *curr_node = NULL, *tmp = NULL;
	int node_found = 0;

	if (!head || !*head)
		return;

	curr_node = (*head);
	do {
		if (curr_node == node)
		{
			node_found = 1;
			break;
		}
		curr_node = curr_node->next;
	} while (curr_node != *head && !node_found);
	if (!node_found)
		return;
	if (curr_node == *head && curr_node->next == *head)
	{
		free_search_list(&curr_node);
		*head = NULL;
	}
	else
	{
		tmp = curr_node->next;
		tmp->prev = curr_node->prev;
		curr_node->prev->next = tmp;
		if (curr_node == *head)
			*head = tmp;
		curr_node->next = curr_node;
		free_search_list(&curr_node);
	}
}
