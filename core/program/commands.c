/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 12:39:05 by biphuyal          #+#    #+#             */
/*   Updated: 2026/01/01 14:03:13 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	push_cmd_back(t_command **head, t_command *new)
{
	t_command	*temp;

	new->next = NULL;
	if (!head || !new)
		return ;
	if (!*head)
	{
		*head = new;
		return ;
	}
	temp = *head;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}

void	save_redir(t_token *token, t_command **curr)
{
	if (token->type == TOKEN_REDIR_IN)
	{
		(*curr)->identity = IN;
		return ;
	}
	else if (token->type == TOKEN_REDIR_OUT)
	{
		(*curr)->identity = OUT;
		return ;
	}
	else if (token->type == TOKEN_APPEND)
	{
		(*curr)->identity = APPEND;
		return ;
	}
	else if (token->type == TOKEN_HEREDOC)
	{
		(*curr)->identity = HEREDOC;
		return ;
	}
}

void	handel_operators(t_token *token, t_command **curr)
{
	if (token->type == TOKEN_PIPE)
	{
		*curr = (*curr)->next;
		return ;
	}
	if (token->type == TOKEN_REDIR_IN || token->type == TOKEN_REDIR_OUT ||
		token->type == TOKEN_APPEND || token->type == TOKEN_HEREDOC)
	{
		save_redir(token, curr);
		return ;
	}
}

t_command	*command_line(t_token *token)
{
	t_command	*curr;
	t_command	*new;

	curr = NULL;
	while (token)
	{
		new = ft_calloc(1, sizeof(t_command));
		if (!new)
			return (NULL);
		new->cmd = token->value;
		if (token->type == TOKEN_WORD)
			push_cmd_back(&curr, new);
		handel_operators(token, &curr);
		token = token->next;
	}
	return (curr);
}
