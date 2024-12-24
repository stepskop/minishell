#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "minishell.h"
// Define spacing for drawing tree structure
#define INDENT_STEP 4

void	print_branches(int depth, char branch_type)
{
	for (int i = 0; i < depth * INDENT_STEP; i++)
		printf(" ");
	printf("%c-- ", branch_type);
}

void	draw_ast_recursive(t_ast *node, int depth, char branch_type)
{
	if (!node)
		return ;
	print_branches(depth, branch_type);
	printf("[%p][res: %d, value: %s, type: %d]\n",
		node, node->res, node->value ? node->value : "NULL", node->type);
	if (node->left)
		draw_ast_recursive(node->left, depth + 1, 'L');
	if (node->right)
		draw_ast_recursive(node->right, depth + 1, 'R');
}

void	draw_ast(t_ast *ast)
{
	if (!ast)
	{
		printf("Empty AST\n");
		return ;
	}
	printf("AST Structure:\n");
	draw_ast_recursive(ast, 0, ' ');
}
