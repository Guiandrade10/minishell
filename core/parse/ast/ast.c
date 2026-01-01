/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biphuyal <biphuyal@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 22:36:32 by gude-and          #+#    #+#             */
/*   Updated: 2025/12/21 20:45:39 by biphuyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

t_ast_node	*ast_new_cmd(t_cmd *cmd)
{
	t_ast_node	*node;

	if (!cmd)
		return (NULL);
	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = NODE_CMD;
	node->cmd = cmd;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_ast_node	*ast_new_pipe(t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*node;

	if (!left || !right)
		return (NULL);
	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = NODE_PIPE;
	node->cmd = NULL;
	node->left = left;
	node->right = right;
	return (node);
}

void	ast_free(t_ast_node *node)
{
	if (!node)
		return ;
	if (node->type == NODE_CMD && node->cmd)
		cmd_free(node->cmd);
	else if (node->type == NODE_PIPE)
	{
		ast_free(node->left);
		ast_free(node->right);
	}
	free(node);
}
