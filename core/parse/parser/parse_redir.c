/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gude-and <gude-and@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 21:32:11 by gude-and          #+#    #+#             */
/*   Updated: 2026/01/01 14:01:25 by gude-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>

t_redir	*redir_create(t_redir_type type, char *file, bool quoted)
{
	t_redir	*redir;

	if (!file)
		return (NULL);
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->file = ft_strdup(file);
	if (!redir->file)
	{
		free(redir);
		return (NULL);
	}
	redir->quoted = quoted;
	redir->heredoc_content = NULL;
	redir->next = NULL;
	return (redir);
}

bool	redir_add(t_cmd *cmd, t_redir *redir)
{
	t_redir	*current;

	if (!cmd || !redir)
		return (false);
	if (!cmd->redirs)
	{
		cmd->redirs = redir;
		return (true);
	}
	current = cmd->redirs;
	while (current->next)
		current = current->next;
	current->next = redir;
	return (true);
}

void	redir_free(t_redir *redir)
{
	t_redir	*current;
	t_redir	*next;

	current = redir;
	while (current)
	{
		next = current->next;
		if (current->file)
			free(current->file);
		if (current->heredoc_content)
			free(current->heredoc_content);
		free(current);
		current = next;
	}
}

t_redir_type	token_to_redir_type(t_token_type type)
{
	if (type == TOKEN_REDIR_IN)
		return (REDIR_IN);
	if (type == TOKEN_REDIR_OUT)
		return (REDIR_OUT);
	if (type == TOKEN_APPEND)
		return (REDIR_APPEND);
	return (REDIR_HEREDOC);
}

bool	parse_redirections(t_parser *p, t_cmd *cmd)
{
	while (p->current && (p->current->type == TOKEN_REDIR_IN
			|| p->current->type == TOKEN_REDIR_OUT
			|| p->current->type == TOKEN_HEREDOC
			|| p->current->type == TOKEN_APPEND))
	{
		if (!parse_redir_one(p, cmd))
			return (false);
	}
	return (true);
}
