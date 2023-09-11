#include "main.h"

/**
 * undo_replace - This function undoes a pending replacement
 * to a search node.
 * @node: Node to reverted.
 */
void undo_replace(s_node *node)
{
	free(node->replace);
	node->replace = NULL;
}
